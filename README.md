# The Classics – Slot Machine Simulator

## Project Description

This project is an implementation of **Homework 1 – The Classics (CS Open CourseWare)**.
The goal is to simulate a simplified slot machine game in which symbols are
arranged in a 2D matrix. A fixed 3 × M window (cadran) defines the active area
where winning combinations can appear. The program computes the score based on
rotations, symbol alignments, and specific rules.

The assignment practices:
* Proper use of functions and memory management (dynamic allocation & deallocation).
* Traversing and manipulating 2D arrays.
* Implementing algorithms for pattern detection and score calculation.

## Tasks Overview

### Task 1 – Spin the Pixels (10p)

Rotate a given column by a specified number of positions. Elements wrap around naturally.

### Task 2 – Winning Combinations (30p)

Detect all winning patterns inside the 3 × M window:
* Rows: longest sequence of ≥3 identical symbols (value = length).
* Diagonals: sequence of 3 identical symbols (value = 7).
* “X” pattern (two diagonals crossing in the middle): value = 21.
Bonuses:
* If symbol = 7, value is doubled.
* If ≤4 distinct symbols → +15.
* If ≤2 distinct symbols → +100 (not cumulative with the previous bonus).

### Task 3 – All in (15p)

Apply a series of rotations and compute the cumulative score after each intermediate configuration.

### Task 4 – So close! (15p)

Replace one symbol in the matrix (chosen optimally) to maximize the total score. Output the maximum possible score.

### Task 5 – What if? (20p)

Perform two optimal rotations (any columns, any number of steps) to maximize the score. Output the maximum possible score.

### Task 6 – Bonus: 99% Quit Before They Win (20p)

A new game inside the 3 × M window:
Find the minimum-cost path from the top-left to the bottom-right cell.
* Cost = sum of absolute differences between each visited symbol and the starting symbol.
* Allowed moves: up, down, left, right (cannot leave the window).

## Input Format

* First line: task number (1–5, 6 for bonus).
* Second line: two integers N M → number of rows and columns.
* Next N lines: the matrix values (digits 0–9).
* Task-specific extra input:
    * Task 1: two numbers → column index c and number of rotations r.
    * Task 3: one number T (number of operations), followed by T pairs (c, r).

## Output Format

* Task 1: final matrix after rotation.
* Task 2: two numbers → number of winning combinations, total score.
* Task 3: single number → sum of scores after all operations.
* Task 4: maximum possible score after one replacement.
* Task 5: maximum possible score after two optimal rotations.
* Task 6: minimum path cost.

## Constraints

* 1 ≤ N ≤ 1000
* 1 ≤ M ≤ 500
* 1 ≤ T ≤ 1000
* 0 ≤ matrix[i][j] ≤ 9
* 0 ≤ r ≤ 2^31 - 1
* Dynamic memory allocation (malloc/calloc) is mandatory. Memory must be freed after usage.

## Checker usage

Run `./checker.sh` or directy use `checker.py`
