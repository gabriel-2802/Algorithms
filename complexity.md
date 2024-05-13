## Complexity Classes

- This document aims to associate algorithms / classes of algorithms with specific complexities.
For example, starting from the `time limit` stated in a problem, one can deduce the `optimal complexity` based on the given variables, and from the complexity, one can infer a few possible algorithms to solve the problem.

- For a modern processor, in **C/C++**, the number of instructions executed in 1 second is in the range $[10^6, 10^7]$.
- For **Java**, usually, the execution time is at least double (especially in problems involving very large input or output).
- For **Python**, the execution time is at least 10 times slower than C++ 

|Magnitude Order|Complexity|
|-|-|
|$\left[10^{12}, 10^{18}\right]$|$O(\log{n})$|
|$\left[10^{7}, 10^{12}\right]$|$O(\sqrt{n})$|
|$\left[10^{6}, 10^{7}\right]$|$O(n)$|
|$10^{5}$|$O(n \log{n})$|
|$10^{4}$|$O(n \sqrt{n})$|
|$10^{3}$|$O(n^2)$|
|$10^{2}$ |$O(n^3)$|
|$10$|$O(2^n)/O(3^n)$|
|$15$|$O(n!)/O(2^n)$|
|$30 - 40$ (even)|$O(\frac{n}{2}!)/(2 ^ {\frac{n}{2}})$ (Meet in the middle) |


Conclusion: **Ideally**, we aim for an $O(1)$ solution.
If not possible, we look for $O(\log{n})$, then $O(\sqrt{n})$, and so on up the table.

# Algorithms Studied in Algorithm Design and Analysis

|Complexity Class| Algorithms |
|-|-|
|$O(1)$| - direct answers (even, odd, etc.)<br> - simple formulas (e.g., sum of numbers from 1 to n using Gauss's formula)|
|$O(\log{n})$ | - D&C algorithms: binary search (normal, lower bound, upper bound), logarithmic exponentiation, matrix exponentiation (DP optimization) <br> - GCD, LCM |
|$O(\sqrt{n})$| - number factorization<br>- primality testing |
|$O(n)$ = linear| - array traversal<br>- linear DP recurrences: MSS, counting<br>- greedy algorithms (e.g., on arrays) |
|$O(n \log{n})$| - sorts<br>- n binary searches on a sorted array<br>- n = traversing a sequence of n elements, log n = applying log n operations per element (e.g., push/pop heap, compute power) |
|$O(n ^ 2)$ <br>$O(n m)$| - more complex DP recurrences (e.g., LIS)<br>- operations on matrices<br>- BFS on grids |
|$O(n ^ 3)$| - DP recurrences like PODM |
|||
|**Backtracking**||
|$O(2 ^ n)$|- subsets of a set with n elements <br>- combinations in problems of the type "one can always go left or right, what is the total number of possibilities?" |
|$O(C(n, k))$<br>$O(n!)$*| - problems that reduce to generating combinations|
|$O(A(n, k))$<br>$O(n!)$*|- problems that reduce to generating arrangements|
|$O(P(n))$<br>$O(n!)$|- problems that reduce to generating permutations|
||* = a relaxed limit (for example: the number of arrangements is less than n!)|
|||
|**Graphs**|
|$O(n + m)$ = linear| - DFS/BFS<br>- any algorithm based on one or few traversals: cycle in graph, TopSort, CC, SCC, BCC / CV / CE, distances on particular graphs (tree, DAG, equal/no costs)
|$O(m \log{n})$ |- Dijkstra |
|$O(m \log{m})$| - Kruskal / Prim |
|$O(n \log{n} + m)$| - sorting nodes by a criterion, then a graph traversal|
|$O(m \log{m} + n)$ | - sorting edges by a criterion, then a graph traversal|
|$O(n m)$<br>$O(n ^ 2)$| - Bellman-Ford <br> - n traversals on a graph $n * O(BFS/DFS)$|
|$O(n ^ 3)$|- Floyd-Warshall (dense graphs)|
|$O(n m \log{n})$| - Johnson (sparse graphs)|
|$O(n m^2)$| - Edmonds-Karp|
|$O(b ^ d)$|- A* <br>- Minimax|