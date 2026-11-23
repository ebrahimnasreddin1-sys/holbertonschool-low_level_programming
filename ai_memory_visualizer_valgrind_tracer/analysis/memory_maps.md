# Memory Maps — Task 0

## 1. Stack Example — Recursion and Stack Frames

### Purpose

This program shows how stack frames are created during recursive calls and cleaned up when functions return, using local variables, arrays, and pointers.

### Execution Flow

Starting from `walk_stack(0, 3)`, each call increments the depth until it hits `3`. Once it reaches depth `3`, the recursion stops and the calls return in reverse order:

- Enter depth 0
- Enter depth 1
- Enter depth 2
- Enter depth 3
- Exit depth 3
- Exit depth 2
- Exit depth 1
- Exit depth 0

### Stack Variables & Memory Map (at Depth 3)

Every call to `walk_stack` gets its own stack frame and its own `marker` variable. At the deepest point (depth 3), all four frames are active on the stack:

| Function Call | Depth | `marker` Value |
| --- | --- | --- |
| `walk_stack(0, 3)` | 0 | 0 |
| `walk_stack(1, 3)` | 1 | 10 |
| `walk_stack(2, 3)` | 2 | 20 |
| `walk_stack(3, 3)` | 3 | 30 |

Each `dump_frame` call also creates a temporary stack frame with three local variables:

- `local_int`: an integer initialized to `100 + depth`
- `local_buf`: a 16-byte local `char` array
- `p_local`: a pointer to that call's `local_int`

Since `p_local` points to `local_int` within the same call, both print the exact same address. Once `dump_frame` returns, its frame is removed from the stack.

### Lifetime & Heap

- **Stack Lifetime:** Local variables only exist while their function call is active. As the recursive calls return (from depth 3 back to 0), their frames and variables are destroyed.
- **Heap:** No heap memory is explicitly allocated in this program (no `malloc`, `calloc`, or `realloc`).

### Observed Behavior

Running the program prints a different memory address for `local_int` at each depth, confirming that recursive calls get separate local variable instances. In every call, `p_local` matches the address of its own `local_int`.

### AI Analysis Review

Checked against the source code and actual program output. The recursive calls use separate stack frames, and `p_local` points to the corresponding `local_int`. Because printing addresses alone doesn't prove the exact size or physical layout of each frame, no frame-size claims are made.

## 2. Heap Example — Allocations and Memory Leak

### Purpose

This program shows how dynamic memory is allocated with `malloc`, cleaned up with `free`, and what happens when a memory leak is introduced intentionally.

### Memory Allocation

For each person, `person_new()` makes two separate heap allocations:

- A `Person` struct storing a `name` pointer and `age`.
- A separate block for the name string, including the null terminator (`\0`).

Both Alice and Bob get their own `Person` struct and their own name buffer.

### Memory Map

| Person | Allocation | Contents |
| --- | --- | --- |
| Alice | `Person` struct | `name` pointer, `age = 30` |
| Alice | Name buffer | `"Alice\0"` (6 bytes) |
| Bob | `Person` struct | `name` pointer, `age = 41` |
| Bob | Name buffer | `"Bob\0"` (4 bytes) |

### Memory Cleanup

- **Bob:** Properly cleaned up — both `bob->name` and `bob` are freed.
- **Alice:** `person_free_partial(alice)` frees the `Person` struct without freeing `alice->name` first, leaving the name buffer unreachable and leaked.

### Valgrind Results

Running the program under `valgrind` confirms the leak:

- **Definitely lost:** 6 bytes in 1 block (Alice's name: 5 characters + `\0`)
- **Total heap usage:** 5 allocations, 4 frees, 1,066 bytes allocated
- **Leak source:** Traced to `person_new()` at `heap_example.c:21`

### AI Analysis Review

Verified against both the source code and the actual `valgrind` report. Freeing the `Person` struct alone does not release the separately allocated name string, and `valgrind` confirms the exact 6-byte leak along with its allocation site.

## 3. Aliasing Example — Use-After-Free

### Purpose

This program shows pointer aliasing and what happens when memory is accessed after it has already been freed.

### Memory Allocation & Map

`make_numbers()` allocates a 5-integer array on the heap, initializing each element to `i * 11` (`0, 11, 22, 33, 44`). The pointer `a` stores this address, and `b = a` copies it so both pointers alias the exact same block:

| Pointer | Address | Points To |
| --- | --- | --- |
| `a` | Same address | Heap array of 5 integers |
| `b` | Same address | Same heap array (alias) |

### Execution & Lifetime

- Before `free(a)`, both `a` and `b` access the same valid array.
- Calling `free(a)` releases the heap block, leaving `b` with the old address as a dangling pointer.
- Any access through `b` afterward — reading `b[2]`, writing `b[3]`, and reading `b[3]` — is an invalid memory operation.

### Valgrind Results

`valgrind` reported **3 errors in 3 contexts** on the freed 20-byte block (5 integers), which was allocated in `make_numbers()` at line 12 and freed in `main()` at line 38:

- **Invalid read:** `b[2]` (line 42)
- **Invalid write:** `b[3] = 1234` (line 44)
- **Invalid read:** `b[3]` (line 45)

No memory leaks were reported (2 allocations, 2 frees).

### AI Analysis Review

The initial analysis correctly caught that `a` and `b` alias the same block and that using `b` after `free(a)` is invalid. In a normal run, the values printed after freeing are unpredictable and unreliable — `valgrind` flagged every invalid access even when the program appeared to print valid-looking numbers, showing that normal output alone does not prove memory safety.

## 4. Crash Example — NULL Pointer Dereference

### Purpose

This program shows what happens when a function returns `NULL` and the caller tries to dereference that pointer.

### Execution Flow

`main()` sets `n = 0` and calls `allocate_numbers(0)`. Since `n <= 0`, the function returns `NULL` right away without allocating any memory, leaving `nums` as `NULL`. The program then tries to write `42` to `nums[0]`, dereferencing `NULL` and triggering a segmentation fault.

### Memory Map

| Variable | Location | Value |
| --- | --- | --- |
| `n` | Stack (`main`) | `0` |
| `nums` | Stack (`main`) | `NULL` (`0x0`) |
| Heap allocation | Heap | None from `allocate_numbers()` |

### Valgrind Results

- **Error:** Invalid write of size 4 at `crash_example.c:32` (attempted write to inaccessible address `0x0`)
- **Termination:** Process killed by signal 11 (`SIGSEGV`)
- **Heap:** No allocation occurred in `allocate_numbers()` because it returned early when `n` was `0`

### AI Analysis Review

Checked against the source code, normal execution, and `valgrind` output. All three confirm that the crash comes directly from dereferencing a `NULL` `nums` pointer — not from a failed heap allocation or accessing freed memory.