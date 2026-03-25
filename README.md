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
