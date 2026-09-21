*This project has been created as part of the 42 curriculum by azdursun, mumidill.*

# push_swap

Sort a stack of integers with a second stack and a tiny set of operations, using as few operations as possible.

## Description

`push_swap` reads a list of integers (stack **a**, the first argument being the top) and prints, one per line on the standard output, a sequence of Push_swap operations that leaves **a** sorted in ascending order (smallest number on top) and **b** empty.

The cost of a solution is the **number of operations printed**. That is the "time" the complexity classes in this document refer to, not CPU time.

| Operation | Effect |
|---|---|
| `sa` `sb` `ss` | swap the first two elements of a, of b, or of both |
| `pa` `pb` | push the top of b onto a, or the top of a onto b |
| `ra` `rb` `rr` | rotate a, b, or both: the top element becomes the bottom one |
| `rra` `rrb` `rrr` | reverse rotate a, b, or both: the bottom element becomes the top one |

### Overview

- Four sorting strategies embedded in one binary and selectable at run time: **simple** O(n²), **medium** O(n√n), **complex** O(n log n) and **adaptive** (the default), which picks one of the three from the measured *disorder* of the input.
- A **disorder metric** between 0 (sorted) and 1 (reversed), computed before any move.
- An optional **benchmark mode** (`--bench`) that reports on stderr the disorder, the strategy used with its complexity class, the total number of operations and the count of each operation.
- Strict input validation: integers only, `int` range, no duplicates, exact option names. Every error prints `Error` on stderr.
- No global variable, no memory leak (everything allocated is freed on every path), only `write`, `malloc` and `free` from the C library, Norm compliant.

## Instructions

### Requirements

A Linux machine with `cc` and `make`. `norminette` and `valgrind` are only needed to run the checks listed below.

### Build

```sh
make          # builds ./push_swap  (cc -Wall -Wextra -Werror, no relink)
make clean    # removes the object files
make fclean   # removes the object files and ./push_swap
make re       # fclean, then all
```

### Run

```sh
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <integers ...>
```

- **Integers** are given as separate arguments or as space-separated numbers inside one quoted argument (`./push_swap "3 2 1"`). A leading `+` or `-` and leading zeros are accepted. Each number must fit in an `int` and no value may appear twice.
- **Selector**: at most one of `--simple`, `--medium`, `--complex`, `--adaptive`. Without any selector `--adaptive` is used. Every selector works for every input size and disorder.
- `--bench` prints the metrics on **stderr**; the operations stay alone on stdout.
- The options may appear anywhere in the argument list.
- **Output**: one operation per line on stdout. An already sorted stack, a single number or no argument at all prints nothing.
- **Errors**: a non-integer argument, a value outside the `int` range, a duplicate, an unknown or repeated option, or options without any number print `Error` on stderr and exit with status 1.

### Examples

```console
$ ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
15

$ ./push_swap --bench --adaptive 4 67 3 87 23 > /dev/null
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops:  15
[bench] sa:  0  sb:  0  ss:  0  pa:  5  pb:  5
[bench] ra:  2  rb:  2  rr:  0  rra:  0  rrb:  1  rrr:  0

$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
$ ./push_swap 2147483648
Error
```

### Checking the result

```sh
# the checker provided with the subject prints OK when the operations sort the stack
ARG="4 67 3 87 23"; ./push_swap --bench $ARG 2> bench.txt | ./checker_linux $ARG

norminette *.c *.h                                         # Norm
valgrind --leak-check=full ./push_swap --bench $ARG        # memory errors and leaks
```

## Algorithms

### Model and preprocessing

- **Cost model.** Only the operations that are printed are counted. Everything computed to *decide* what to print (disorder, ranks, duplicate detection) costs no operation.
- **Disorder** (`compute_disorder`, `string_utils.c`). Over all pairs `(i, j)` with `i < j` of the initial stack, a pair is a *mistake* when `a[i] > a[j]`; `disorder = mistakes / total_pairs`. It is 0 for a sorted stack and 1 for a reversed one (it is the normalised inversion count). It is measured once, before any move.
- **Ranks** (`ft_index`, `main.c`). Each node stores `index`, the number of elements smaller than its value: a permutation of `0 .. n-1` because duplicates are rejected during parsing. The medium and complex strategies work on ranks, so they do not depend on the magnitude or the sign of the values.
- **Sorted guard.** If the stack is already sorted nothing is printed, whatever the strategy.
- **Bookkeeping.** Every operation function returns 1 when it really moved something and 0 when it was a no-op (for instance rotating a stack of fewer than two elements). The counters are incremented with that return value, so the numbers printed by `--bench` are always equal to the number of lines written on stdout.

### Simple: selection sort, O(n²) (`simple.c`)

Repeat until `a` is empty: find the position of the smallest value of `a`, bring it to the top by the shorter direction (`ra` when it lies in the upper half of the stack, `rra` otherwise; a tie goes to `ra`), then `pb` it. The minima reach `b` in ascending order, so `b` finally holds the largest value on top; then `pa` everything back, which reverses the order and leaves `a` ascending. For `./push_swap --simple 5 4 3 2 1` this prints exactly the 14 operations shown in the subject.

- **Time.** Selecting from a stack of `m` elements costs at most `⌊m/2⌋` rotations (the shorter direction) and one `pb`. Since the sum of `⌊m/2⌋` for `m = 1 .. n` is `⌊n²/4⌋`, and each element is pushed once and pulled back once, the total is at most **⌊n²/4⌋ + 2n = O(n²)** operations. For `n = 100` the bound is 2700 and 1452 is measured on average; for `n = 500` it is 63500 against 32163.
- **Space.** O(1) auxiliary memory.
- **Why.** It is the simplest correct strategy and the baseline of the O(n²) class. Its cost is `2n` plus the distance of each successive minimum from the nearest end of the stack, so it is cheap on nearly sorted input and on a reversed stack (where the minimum is always at the bottom) and expensive in between.

### Medium: chunk sort, O(n√n) (`medium.c`)

Let `c = ceil(sqrt(n))` (computed by an integer loop, `math.h` is not allowed) and cut the ranks into chunks of `c` consecutive values: `[0, c)`, `[c, 2c)`, ...

1. **Distribution.** For each chunk, from the smallest ranks to the largest: sweep `a` from the top. An element of the current chunk is pushed with `pb`; if it belongs to the *lower half* of the chunk it is also rotated to the bottom of `b` with `rb`. Any other element is skipped with `ra`. The sweep stops as soon as the whole chunk has left `a`. Because the earlier chunks are already gone, "rank below the chunk's upper bound" selects exactly the current chunk.
2. **Collection.** While `b` is not empty: find the largest rank in `b`, rotate `b` towards it by the shorter direction (`rb` or `rrb`), and `pa`. Values come back in descending order, so `a` ends ascending.

- **Time.** There are at most `ceil(n/c) <= c` chunks. Each sweep performs at most one operation per element of `a`, so the distribution costs at most `c·n` (`pb`/`ra`) plus at most `n` (`rb`, one per element). During the collection, the remaining elements of the chunk being emptied always form a prefix and a suffix of `b` (the `rb` step puts the lower half at the bottom, the upper half stays on top, and rotating only ever moves elements of that same chunk). The largest element is therefore at most `c` positions from one end and the shorter direction costs at most `c` rotations, plus one `pa`. Total: **at most 2n(c+1) = O(n√n)**. For `n = 100` the bound is 2200 and 785 is measured on average; for `n = 500` it is 24000 against 7378.
- **Why √n chunks.** With `k` chunks the distribution costs about `k·n` (one sweep per chunk) and the collection about `n·(n/k)` (each extraction rotates inside a chunk of `n/k` elements). `k·n + n²/k` is smallest for `k = √n`, which gives Θ(n√n).
- **Why the `rb` step.** It splits each chunk between the two ends of `b`, so the shorter rotation direction is on average about half as long. It is a constant-factor optimisation and does not change the bound. On prototypes it lowered the average from 808 to 788 operations (n = 100) and from 8048 to 7368 (n = 500).
- **Space.** O(1) auxiliary memory.

### Complex: binary LSD radix sort, O(n log n) (`complex.c`)

Let `B = ceil(log2(n))` be the number of bits of the largest rank `n - 1` (`count_bits`). For each bit from the least significant one, look at the `n` elements from the top of `a`: if the bit of the rank is 1, `ra`; otherwise `pb`. Then `pa` everything back from `b`. The pass is a *stable partition*: after it `a` holds the elements whose bit is 0, in their previous relative order, followed by those whose bit is 1, in their previous relative order. After the pass for the most significant bit `a` is sorted. The loop stops earlier when `a` becomes sorted.

- **Time.** A pass costs `n` operations (`ra` or `pb`) plus one `pa` per element sent to `b`, at most `2n`. Total **at most 2n·ceil(log2 n) = O(n log n)**. Because the ranks are a permutation of `0 .. n-1`, the cost is exactly `B·n + (number of ranks with the bit clear, summed over the bits)`: it does not depend on the order of the input, apart from the early exit when `a` becomes sorted between two passes. It is 1084 operations for `n = 100` and 6784 for `n = 500`.
- **Space.** O(1) auxiliary memory.
- **Why.** Radix sort needs no comparison between elements, only the bits of the ranks, which fits two stacks naturally: `ra` keeps the ones, `pb`/`pa` reverses and restores the zeros.

### Adaptive: choose the method from the disorder (`main.c`)

| Disorder `d` | Regime | Method | Time (operations) | Upper bound |
|---|---|---|---|---|
| `d < 0.2` | low | simple (selection sort) | O(n²) | ⌊n²/4⌋ + 2n |
| `0.2 <= d < 0.5` | medium | chunk sort | O(n√n) | 2n(⌈√n⌉+1) |
| `d >= 0.5` | high | radix sort | O(n log n) | 2n⌈log₂ n⌉ |

**Space** is O(1) auxiliary memory in every regime, beyond the two stacks themselves (n linked-list nodes, allocated once while parsing). The disorder, the ranks and the duplicate check use O(1) extra memory and O(n²) CPU time, but no operation.

**Rationale for the thresholds.** The three regimes, their boundaries (0.2 and 0.5) and the complexity target of each are fixed by the subject; they were implemented as specified and not tuned. What the measurements below add:

- **High disorder.** Radix sort's cost does not depend on the order of the input and grows as n log n. At `n = 500` it is the cheapest of our strategies on random input (6784 against 7378 for the chunk sort), and it is the only one whose cost is bounded by n log n. At `n = 100` the chunk sort is cheaper (785 against 1084): its constant factors are smaller, and the crossover lies between 100 and 500 elements.
- **Medium disorder.** The chunk sort's cost moves slowly with the disorder (520 to 825 operations for `n = 100` across the whole range) and, for `n = 100`, it is the cheapest of the three from `d = 0.10` to `d = 0.75`.
- **Low disorder.** Selection sort with nearest-direction rotation is the cheapest of the three at very low disorder (339 against 520 and 1084 operations for `n = 100` at `d = 0.02`, 496 against 616 at `d = 0.05`). Its cost grows quadratically, so the advantage shrinks with `n` (at `n = 500` it wins only at `d = 0.02`) and disappears towards the upper end of the regime; see the limitations below.

`--bench` reports `Adaptive` together with the complexity class of the regime that was actually used.

### Measured performance

All figures come from the final binary; each value is the number of operations printed on stdout.

**Random permutations** (100 permutations for `n = 100`, 20 for `n = 500`, 5 for `--simple` at `n = 500`):

| Strategy | n = 100, average (min-max) | n = 500, average (min-max) |
|---|---|---|
| `--simple` | 1452 (1236-1658) | 32163 (30930-33576) |
| `--medium` | 785 (746-817) | 7378 (7246-7550) |
| `--complex` | 1084 (1084-1084) | 6784 (6784-6784) |
| `--adaptive` (default) | 946 (748-1084) | 7075 (6784-7463) |
| *subject: pass / good / excellent* | *< 2000 / < 1500 / < 700* | *< 12000 / < 8000 / < 5500* |

The default program is in the "good" band for both sizes; the "excellent" band is not reached. `--simple` is the O(n²) baseline: it stays under the "pass" line at `n = 100` but is not meant for `n = 500`.

**Operations against disorder** (average of 5 permutations per row; each permutation was obtained by applying random adjacent swaps to the sorted sequence, or to the reversed one when `d > 0.5`, until the exact inversion count was reached):

| n | disorder | simple | medium | complex | adaptive uses |
|---|---|---|---|---|---|
| 100 | 0.02 | 339 | 520 | 1084 | simple |
| 100 | 0.05 | 496 | 616 | 1084 | simple |
| 100 | 0.10 | 691 | 662 | 1084 | simple |
| 100 | 0.15 | 874 | 718 | 1084 | simple |
| 100 | 0.25 | 1109 | 747 | 1084 | medium |
| 100 | 0.35 | 1170 | 764 | 1084 | medium |
| 100 | 0.45 | 1146 | 768 | 1084 | medium |
| 100 | 0.55 | 1065 | 718 | 1084 | complex |
| 100 | 0.75 | 1032 | 772 | 1084 | complex |
| 100 | 1.00 | 299 | 825 | 1084 | complex |
| 500 | 0.02 | 3723 | 5182 | 6784 | simple |
| 500 | 0.05 | 7214 | 6224 | 6784 | simple |
| 500 | 0.10 | 12301 | 6724 | 6784 | simple |
| 500 | 0.15 | 15979 | 6939 | 6784 | simple |
| 500 | 0.25 | 21340 | 7083 | 6784 | medium |
| 500 | 0.35 | 22811 | 7209 | 6784 | medium |
| 500 | 0.45 | 21226 | 7209 | 6784 | medium |
| 500 | 0.55 | 21678 | 6633 | 6784 | complex |
| 500 | 0.75 | 20919 | 7009 | 6784 | complex |
| 500 | 1.00 | 1499 | 7132 | 6784 | complex |

Reading the table:

- The radix sort costs the same whatever the disorder; the chunk sort grows slowly with it.
- The selection sort is the cheapest only at very low disorder (`d = 0.02` for both sizes, also `d = 0.05` at `n = 100`) and on a fully reversed stack, where the minimum is always at the bottom and one `rra` brings it up (299 operations for `n = 100`, 1499 for `n = 500`). Between the two its cost is high.
- At `n = 100` the chunk sort is the cheapest from `d = 0.10` to `d = 0.75`.
- At `n = 500` the radix sort is the cheapest at `d = 0.15`, `0.25`, `0.35`, `0.45` and `0.75`; the chunk sort is cheaper at `d = 0.05`, `0.10` and `0.55`, by 1% to 8%.

### Known limitations

- **The regime boundaries come from the subject and were not tuned.** Near the upper end of the low regime and for a large stack the O(n²) method is much more expensive than the chunk sort (15979 against 6939 operations for `n = 500` at `d = 0.15`). A fully reversed stack (`d = 1`) is sorted by selection sort in about `3n` operations, but the adaptive strategy sends it to the radix sort because the regime is decided by the disorder value alone.
- `sa`, `sb`, `ss`, `rr` and `rrr` are implemented but never used by the strategies; combining moves (for example `rr`) is not exploited.
- The "excellent" performance band of the subject is not reached.

## Technical choices

- **Stacks** are singly linked lists (`t_list`: `content`, `index`, `next`). `t_main` groups both stacks, the options, the disorder and the operation counters (`t_counter`).
- **Parsing pipeline.** `flag_finder` splits every argument on spaces (`ft_split`); `flag_control` walks the tokens. A token starting with `--` must be exactly one of the five options (`ft_strcmp`, no prefix matching); any other token must be an optionally signed decimal integer. `is_valid_number_token` accumulates the value in a `long` and stops as soon as it leaves the `int` range, so arbitrarily long digit strings cannot overflow. Duplicates are detected after parsing (`ft_has_duplicates`).
- **Memory.** All allocations (argument tokens, stack nodes, options, counters) are released by `free_all` on the success path and on every error path. This was checked with `valgrind --leak-check=full` over success and error scenarios, and by making each `malloc` of a run fail in turn: the program then prints `Error`, exits with status 1 and frees everything.
- **Allowed functions.** Only `write`, `malloc` and `free` are imported from the C library (`nm -D --undefined-only push_swap`); `ft_calloc`, `ft_split`, `ft_atoi`, `ft_strcmp` and the output helpers are reimplemented.
- **Norm.** All sources and the header pass `norminette`. Files are kept at five functions or fewer, which is why the output helpers, the strategy labels and the memory release live in small dedicated files.

## Project structure

| File | Role |
|---|---|
| `main.c` | entry point, rank computation (`ft_index`), strategy selection and dispatch (`ft_set_algorithm`, `ft_adaptive`, `ft_run_algorithm`) |
| `argument_flags.c` | argument splitting (`flag_finder`), validation and stack construction (`flag_control`), option handling |
| `input_numbers.c` | `ft_atoi`, list nodes, `int`-range check of a token |
| `split_utils.c` | `ft_split`, `ft_strlcpy` |
| `string_utils.c` | `ft_strcmp`, `ft_isdigit`, disorder metric, duplicate detection, `ft_calloc` |
| `stack_utils.c` | `ft_is_sorted` |
| `swap_moves.c` `push_moves.c` `rotate_moves.c` `reverse_moves.c` | the eleven operations (each prints its name and returns 1 when it moved something) |
| `simple.c` `medium.c` `complex.c` | the three sorting strategies |
| `bench.c` | the `--bench` report |
| `put_utils.c` | output helpers on a file descriptor (`ft_putstr_fd`, `ft_putnbr_fd`) |
| `strategy_utils.c` | strategy name and complexity class shown by `--bench` |
| `free_utils.c` | `free_stack`, `free_args`, `free_all` |
| `error.c` | prints `Error` |
| `push_swap.h`, `Makefile` | declarations and build rules |

## Resources

### References

- The *push_swap* subject of the 42 curriculum (version 1.1), which defines the operations, the strategies, the disorder metric and the performance targets.
- The 42 Norm (version 4.1) and `norminette`.
- T. H. Cormen, C. E. Leiserson, R. L. Rivest, C. Stein, *Introduction to Algorithms*, chapter 8.3 "Radix sort".
- D. E. Knuth, *The Art of Computer Programming*, volume 3 "Sorting and Searching", section 5.2.5 "Sorting by distribution".
- Wikipedia: [Radix sort](https://en.wikipedia.org/wiki/Radix_sort), [Selection sort](https://en.wikipedia.org/wiki/Selection_sort), [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)).
- The `valgrind` documentation, used to check memory errors and leaks.

### Use of AI

Claude Code (Anthropic's Claude) was used as a programming assistant during the final phase of the project. What it was used for, by part of the project:

- **Norm compliance**: refactorings to satisfy `norminette`, notably splitting the benchmark code into `bench.c`, `put_utils.c` and `strategy_utils.c`, and reformatting `main.c`, `argument_flags.c` and `push_swap.h`.

- **This README**, drafted from the code and the subject; its figures were measured on the final binary.

