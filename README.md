# Paper Folding: Reverse Simulation Algorithm

## Overview
This repository contains an optimized C++ solution for a complex geometric algorithmic problem ("Paper Folding"). 
**Acceptance Rate:** 11% (High difficulty due to edge cases in polygon boundary tracking).

## The Challenge
A rectangular piece of paper is folded up to $F$ times ($F \le 8$) vertically or horizontally. After all folds, a single hole is punched through the folded stack. The objective is to calculate the total number of holes visible when the paper is completely unfolded.

Forward simulation of overlapping polygons leads to immense geometric complexity and edge-case failures.

## Algorithmic Approach: Reverse Unfolding Simulation
Instead of simulating the folding process forward, this solution employs a **Reverse Simulation** approach:
1. **Boundary Tracking (Forward Pass):** First, we calculate and store the valid physical boundaries (min/max coordinates) of the paper at each folding step.
2. **Reverse Reflection (Backward Pass):** Starting from the final punched hole, we "unfold" the paper backward. 
3. **Strict Filtering:** A reflected hole is only recorded if its mirrored coordinates fall strictly within the historically valid boundaries of the paper at that specific state. 

This eliminates the need for complex polygon intersection math and reduces the problem to elegant coordinate reflection and boundary validation. Overlapping holes are handled natively using `std::set`.

## Complexity
- **Time Complexity:** $O(F \cdot 2^F)$ — where $F$ is the number of folds. With $F \le 8$, the maximum number of operations is extremely small ($8 \cdot 256$), resulting in an execution time of ~4ms.
- **Space Complexity:** $O(2^F)$ — to store the unique coordinates of the holes at the maximum unfolded state.

## Project 2: Tournament Graph Construction (Diameter ≤ 2)

### Overview
An optimized C++ solution for a highly constrained Graph Theory problem. 
**Acceptance Rate:** 4% (Extreme difficulty due to mathematical edge cases and strict diameter constraints).

### The Challenge
Construct a directed tournament graph (no self-loops, exactly one directed edge between any pair of distinct vertices) with $N$ vertices ($3 \le N \le 1000$). The maximum shortest path (diameter) between ANY two vertices must be $\le 2$. The algorithm must run within 1 second.

### Algorithmic Architecture
Brute-force or backtracking approaches fail immediately due to $O(N!)$ complexity. This solution implements a deterministic mathematical construction in strict $O(N^2)$ time:
1. **Mathematical Impossibility Handling:** The algorithm natively detects and rejects $N = 4$, which is mathematically proven to have no valid tournament graph with a diameter $\le 2$.
2. **Odd $N$ (Circulant Graph):** Constructs a perfectly balanced circulant tournament where each vertex $i$ directs edges to the next $(N-1)/2$ vertices modulo $N$.
3. **Even $N$ (Dominating Set Extension):** Constructs the valid base for $N-1$ (which is odd) and mathematically integrates the final $N$-th vertex by precisely splitting its incoming and outgoing edges to maintain the $\le 2$ distance constraint across the entire network.

### Complexity
- **Time Complexity:** $O(N^2)$ — Directly constructs the adjacency matrix without search space exploration. Execution time is ~1ms for $N=1000$.
- **Space Complexity:** $O(N^2)$ — Memory allocation strictly for the $N \times N$ adjacency matrix.

## Project 3: Dynamic Graph Connectivity via Randomized XOR Hashing

### Overview
An extremely optimized C++ solution for maintaining graph connectivity under dynamic small edge deletions.
**Acceptance Rate:** 2% (Extreme difficulty due to strict time limits and complex dynamic graph properties).

### The Challenge
Given a connected undirected graph ($N \le 10^4, M \le 10^5$), process $10^5$ queries. Each query tests if the graph remains connected after temporarily deleting up to 4 specific edges. A naive approach (running BFS/DFS per query) yields $O(Q \cdot (N+M))$ and critically fails the 2.0s time limit.

### Algorithmic Architecture
Implemented a cutting-edge **Randomized XOR Hashing** technique to reduce query time to $O(1)$:
1. **Spanning Tree & Randomization:** Extracted a spanning tree. Assigned a random 64-bit integer to every non-tree edge using `mt19937_64`.
2. **Cycle Accumulation:** The weight of each tree edge is precomputed via DFS as the XOR sum of all non-tree edges covering it (fundamental cycles).
3. **Subset Evaluation (Linear Independence):** A subset of edges forms a valid disconnecting cut if and only if their XOR sum is exactly 0.
4. **O(1) Queries:** Since at most 4 edges are removed, the algorithm simply evaluates the $2^C - 1$ subsets of the queried edges. If any subset XORs to 0, the graph is disconnected.

### Complexity
- **Time Complexity:** $O(N + M)$ for preprocessing, and $O(2^C)$ per query. Total time: $O(N + M + Q \cdot 2^C)$. Execution takes fractions of a second, completely bypassing the TLE bottleneck.
- **Space Complexity:** $O(N + M)$ for adjacency lists and edge hash storage.
