# Submission.md

## Author Information

Author: David Luo  
UGA Email: davidluo@uga.edu  
Course: CSCI 4730

## Implementation Overview

This project recreates the `malloc` and `free` functionalities found in C by moving the program break through `sbrk`. Allocated blocks are aligned to pages.

## 6730 Requirements

* `csx730_calloc`

## Reflection

1. What do you think was the motivation behind assigning this project in this class?
    * To provide an understanding on how memory management is done in practice.
1. What is the most important thing you learned in this project?
    * Memory is allocated by moving the program break and managed using metadata associated with the allocated memory.
1. What do you wish you had spent more time on or done differently?
    * Nothing in particular?
1. What part of the project did you do your best work on?
    * `csx730_malloc` was pretty good.
1. What was the most enjoyable part of this project?
    * The pointer arithemtic was neat.
1. What was the least enjoyable part of this project?
    * Figuring out what to do in the edge cases.
1. How could your instructor change this project to make it better next time?
    * Provide more examples for more edge cases.