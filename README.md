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
