## Measurement Methodology

In this project, I used GCC to compile the C programs. I used the compiler flags given by the school.

In Task 0, I ran the program three times. I recorded the execution time for every run.

In Task 1, I tested two algorithms called Naive and Single-pass. I ran the program three times and recorded the results. Then I calculated the average time for each algorithm.

In Task 2, I added `clock()` to the program to measure CPU time. I measured the time for building the data, processing the data, and calculating the final value. I also measured the total time.

## Observed Performance Differences

In Task 0, I got these results:

- Run 1: 0.069524 seconds
- Run 2: 0.069418 seconds
- Run 3: 0.069191 seconds

The average time was about 0.069378 seconds.

The times were close, but they were not exactly the same.

In Task 1, I got these results:

Naive time

- Run 1 : 0.923139 seconds
- Run 2 : 0.922795 seconds
- Run 3 : 0.920314 seconds

Single-pass time 

- Run 1 : 0.000028 seconds
- Run 2 : 0.000029 seconds
- Run 3 : 0.000028 seconds

The average time for Naive was 0.922083 seconds.

The average time for Single-pass was about 0.00002833 seconds.

Naive took about 32,544 times as long as Single-pass in these tests.

I also noticed that the results were different. Naive returned 625025000, while Single-pass returned 25000. This is because Naive counts some numbers many times.

These measurements show a big difference in execution time, but the two algorithms do not do exactly the same amount of work.

## Relation Between Runtime and Energy Consumption

I learned that execution time and electricity use are connected.

A program that takes more time can keep the CPU working for longer.

But a program that finishes faster does not always use less electricity.

Electricity use also depends on the CPU, the computer, and how the program runs.

In this project, I measured time, not electricity. So I cannot say exactly how much electricity each program used.

## Limitations of the Experiment

One limitation is that the execution time can change between runs.

In Task 0, I ran the same program three times, but I got slightly different times.

This can happen because the computer may be doing other work.

Another limitation is that I tested the programs with fixed data and only a small number of runs.

Also, I did not measure electricity use in watts.

In Task 1, the two algorithms returned different values, so the comparison is mainly about their execution time.

## Practical Engineering Takeaway

This project helped me understand how to measure the performance of C programs.

I learned how to use GCC and `clock()`.

I also learned that running a program more than once is important because execution time can change.
Task 1 showed me that the way a program works can make a big difference in execution time.
I learned that I should use real measurements when comparing programs.
I also understand that a faster program does not automatically mean lower electricity use.
In the future, I will try to measure my programs before deciding which solution is more efficient.