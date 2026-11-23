# Valgrind Analysis — Task 1

All four programs in `programs/` were tested using `valgrind` with the command `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./<program>`.

Each finding below is verified against the source code, the `valgrind` output, and the memory maps documented in `analysis/memory_maps.md`.

## 1. Stack Example — No Memory Errors

### Valgrind Results

`valgrind` reported a clean run with no memory errors for `stack_example`:

- **Memory leaks:** None (`in use at exit: 0 bytes in 0 blocks`)
- **Heap usage:** `1 allocs, 1 frees, 1,024 bytes allocated`
- **Invalid reads:** None
- **Invalid writes:** None
- **Use of uninitialized memory:** None
- **Error summary:** `0 errors from 0 contexts`

### Memory Behavior & Relation to Memory Map

Matching `analysis/memory_maps.md`, the program stores its variables (`marker`, `local_int`, `local_buf`, and `p_local`) in stack frames created during recursive calls to `walk_stack()` and temporary calls to `dump_frame()`. Inside each `dump_frame()` call, `p_local` points to that call's own `local_int`. Every local variable is accessed only while its stack frame is active, and all frames unwind in reverse order from depth `3` back to `0`. The program makes no explicit heap allocations, and all heap memory used during execution is freed before exit.

### AI Analysis Review

Verified against the source code, normal program output, the Task 1 memory map, and the `valgrind` report. All sources confirm zero memory errors and no heap memory remaining in use at exit.

## 2. Heap Example — Memory Leak Due to Lost Ownership

### Valgrind Results

`valgrind` reported one `definitely lost` memory leak during execution of `heap_example`:

- **Error type:** `definitely lost` (memory leak due to lost ownership)
- **Leaked memory:** `6 bytes in 1 blocks` (`loss record 1 of 1`)
- **Allocation site:** `malloc` in `person_new()` at `heap_example.c:21`, called from `main()` at `heap_example.c:51`
- **Heap summary:** `in use at exit: 6 bytes in 1 blocks` (`5 allocs, 4 frees, 1,066 bytes allocated`)
- **Other memory errors:** No invalid reads, invalid writes, or uses of uninitialized memory reported

### Memory Object, Cause & Relation to Memory Map

As shown in `analysis/memory_maps.md`, `person_new()` allocates two separate heap blocks for each person: one for the `Person` struct and another for the name string.

- **Affected memory object:** Alice's dynamically allocated name buffer, `"Alice\0"` (5 characters plus the null terminator `\0`, totaling `6 bytes`).
- **What happened:** For Bob, both `bob->name` and `bob` are freed in the proper order. For Alice, `person_free_partial(alice)` frees only the `Person` struct without freeing `alice->name` first.
- **Why it is invalid (ownership violation):** Freeing the `Person` struct destroys the only pointer referencing Alice's name buffer. Ownership of that 6-byte block is lost while it is still allocated on the heap, making it unreachable for the remainder of the program's lifetime.

### AI Analysis Review

Verified against the source code, `analysis/memory_maps.md`, and `valgrind`'s allocation stack trace (`heap_example.c:21` and `heap_example.c:51`). The `6 bytes` size matches `"Alice\0"`, confirming that the leak is lost ownership of a separately allocated heap object rather than a leak of the entire `Person` struct.

## 3. Aliasing Example — Use-After-Free

### Valgrind Results

`valgrind` reported `3 errors from 3 contexts` on a single freed 20-byte heap block (5 integers), allocated by `make_numbers()` at `aliasing_example.c:12` (called from `main()` at `aliasing_example.c:30`) and freed via `free(a)` at `aliasing_example.c:38`:

| Line | Operation | Classification | Address & Offset |
| --- | --- | --- | --- |
| `aliasing_example.c:42` | Reading `b[2]` | `Invalid read of size 4` | `0x4a91488` (8 bytes inside freed 20-byte block) |
| `aliasing_example.c:44` | Writing `b[3] = 1234` | `Invalid write of size 4` | `0x4a9148c` (12 bytes inside freed 20-byte block) |
| `aliasing_example.c:45` | Reading `b[3]` | `Invalid read of size 4` | `0x4a9148c` (12 bytes inside freed 20-byte block) |

- **Heap summary:** `in use at exit: 0 bytes in 0 blocks` (`2 allocs, 2 frees, 1,044 bytes allocated`)
- **Memory leaks:** None reported
- **Use of uninitialized memory:** None reported

### Memory Object, Cause & Relation to Memory Map

From `analysis/memory_maps.md`, `make_numbers()` allocates a 5-integer heap array (`0, 11, 22, 33, 44`). Pointer `a` receives the block's address (`0x4a91480`), and `b = a` copies it so both pointers alias the same heap allocation.

- **What happened:** Before `free(a)`, both `a` and `b` access the valid array. Calling `free(a)` at line `38` releases the 20-byte block, but `b` still holds the old address (`0x4a91480`) and becomes a *dangling pointer*.
- **Why it is invalid (lifetime violation):** The array's lifetime ends when `free(a)` executes, invalidating every alias pointing to it. Reading `b[2]`, writing `b[3]`, and reading `b[3]` after line `38` access memory whose lifetime has already ended, which is a `use-after-free` error caused by pointer aliasing.

### AI Analysis Review

Verified against the source code, `analysis/memory_maps.md`, and the `valgrind` output. Even though the program kept running without crashing and printed `b[2]=22` and `b[3]=1234`, those printed values are unreliable and do not prove the memory is valid. `valgrind` also shows that having zero memory leaks does not mean a program is free of memory errors.

## 4. Crash Example — NULL Pointer Dereference

### Valgrind Results

`valgrind` reported a fatal invalid write caused by dereferencing `NULL` in `crash_example`:

- **Error type:** `Invalid write of size 4` (`NULL pointer dereference`) at `main()` (`crash_example.c:32`)
- **Invalid address:** `0x0` (`Address 0x0 is not stack'd, malloc'd or (recently) free'd`)
- **Termination:** Signal 11 (`SIGSEGV`) — `Access not within mapped region at address 0x0` at `crash_example.c:32`
- **Heap summary:** `in use at exit: 1,024 bytes in 1 blocks` (`1 allocs, 0 frees, 1,024 bytes allocated`)
- **Leak summary:** `definitely lost: 0 bytes`, `indirectly lost: 0 bytes`, `possibly lost: 0 bytes`, `still reachable: 1,024 bytes in 1 blocks`
- **Error summary:** `1 errors from 1 contexts`
- **Use of uninitialized memory:** None reported

### Memory Object, Cause & Relation to Memory Map

Consistent with `analysis/memory_maps.md`, `main()` sets `n = 0` and calls `allocate_numbers(0)`. Because `n <= 0`, `allocate_numbers()` returns `NULL` immediately without allocating heap memory, leaving `nums` equal to `NULL` (`0x0`).

- **What happened:** At `crash_example.c:32`, the statement `nums[0] = 42` attempts to write a 4-byte integer through `nums`.
- **Why it is invalid:** Address `0x0` is not mapped to any valid memory object. Attempting to write there is a `NULL pointer dereference`, producing an `Invalid write` and an immediate `SIGSEGV` crash.

### Still Reachable Block (`1,024 bytes`)

`valgrind` traces the `1,024 bytes` `still reachable` block through:

`malloc` -> `_IO_file_doallocate` -> `_IO_doallocbuf` -> `_IO_file_overflow` -> `_IO_new_file_xsputn` -> `_IO_file_xsputn` -> `puts` -> `main (crash_example.c:27)`

This block is the C standard library's `stdout` output buffer initialized by `puts()` before the crash. It is not an allocation from `allocate_numbers()`, and it is classified as `still reachable` rather than `definitely lost`.

### AI Analysis Review — Incorrect AI Explanation & Correction

- **Initial AI mistake:** An initial AI interpretation described the `1,024 bytes` `still reachable` block as an internal allocation belonging to `valgrind` itself or its runtime context.
- **Why it was incorrect:** That explanation relied on a generic guess from the `still reachable` label without inspecting the actual `valgrind` stack trace.
- **Correction:** Reviewing the stack trace directly (`_IO_file_doallocate`, `_IO_doallocbuf`, and `puts` called from `crash_example.c:27`) proves the allocation comes from the C standard library's `stdout` buffering path, not from `valgrind` and not from `allocate_numbers()`. Because the program terminated abnormally with `SIGSEGV`, that buffer remained `still reachable` at exit rather than `definitely lost`.

## Summary — Linking Memory Maps to Valgrind Results

| Example | Memory Behavior (`memory_maps.md`) | Valgrind Result | Classification |
| --- | --- | --- | --- |
| `stack_example` | Recursive stack frames and local variables within valid lifetime | `0 errors`, no leaks | Clean run |
| `heap_example` | Separate `Person` struct and name buffer; struct freed without freeing `alice->name` | `6 bytes` lost (`heap_example.c:21`) | `definitely lost` (`leak due to lost ownership`) |
| `aliasing_example` | `a` and `b` alias the same 20-byte array; `b` used after `free(a)` | 2 invalid reads, 1 invalid write (lines `42`, `44`, `45`) | `use-after-free` (`dangling pointer`) |
| `crash_example` | `allocate_numbers(0)` returns `NULL`; write attempted via `nums[0] = 42` | `Invalid write` at `0x0` (line `32`), `SIGSEGV` | `NULL pointer dereference` |