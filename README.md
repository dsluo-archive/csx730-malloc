# csx730-malloc

> The fibers of all things have their tension and are strained like the strings of an instrument.
> __--Henry David Thoreau__

**DUE FRI 2019-04-01 (Apr 01) @ 11:55 PM**

This repository contains the skeleton code for the `csx730-malloc` project
assigned to the students in the Spring 2019 CSCI 4730/6730 class
at the University of Georgia.

## Table of Contents

1. [Academic Honesty]()
1. [Memory Allocation]()
   1. [The User API]()
   1. [The Developer API]()
   1. [How to Manage your Heap]()
   1. [Block Metadata]()
   1. [Examples]()
1. [How to Get the Skeleton Code]()
1. [Project Requirements]()
   1. [Functional Requirements]()
   1. [6730 Requirements]()
   1. [Non-Functional Requirements]()
1. [Submission Instructions]()

## Academic Honesty

You agree to the Academic Honesty policy as outlined in the course syllabus. 
In accordance with this notice, I must caution you **not** to fork this repository
on GitHub if you have an account. Doing so will more than likely make your copy of
the project publicly visible. Please follow the instructions contained in the 
[How to Get the Skeleton Code](#how-to-get-the-skeleton-code) section below in
order to do your development on Nike. Furthermore, you must adhere to the copyright
notice and licensing information at the bottom of this document.

## Memory Allocation

The heap or free store is the memory area of a process reserved by dynamic allocation.
In most C programs, this area is managed by `malloc(3)` and `free(3)`. 
In this project, you are tasked with implementing the `malloc(3)` family of functions
in C using a non-crpytographic block chain! Essentially, your code will be in charge
of managing the process's heap. Mixing your implementation with GLIBC's `malloc(3)`
and `free(3)` is undefined. Some starter code is provided. 
Other project details are provided below.

### The User API

The primary User API provides two functions:

* __`void * csx730_malloc(size_t size);`__<br>
  Allocates `size` bytes and returns a pointer to the allocated memory. The memory is not cleared.
  If `size` is `0`, then `csx730_malloc` returns either `NULL`, or a unique pointer value that 
  can later be successfully passed to the `csx730_free` function. On failure, returns a `NULL` 
  pointer. **NOTE:** Unlike `malloc(3)`, the underlying memory block is _not required_ to be 
  suitably aligned for any object type with 
  [fundamental alignment](https://en.cppreference.com/w/c/language/object#Alignment). 
  
* __`void csx730_free(void * ptr);`__<br>
  Frees the memory space pointed to by `ptr`, which must have been returned by a previous call to
  the `csx730_malloc`, `csx730_calloc`, or `csx730_realloc` function. If `ptr` is `NULL`, then
  no operation is performed. If `csx730_free(ptr)` has already been called, then the behavior is
  undefined.

### The Developer API

The Developer API provides three functions:

* __`void csx730_pheapstats(void);`__<br>
  TODO write.

* __`void csx730_pheapmap(void);`__<br>
  TODO write.
  Examples are [provided below](#examples).
  
### How to Manage your Heap 

### Block Metadata  

### Examples

```
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 program break
```

```
csx730_malloc(32) = 0x19e0018 [append]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (32 bytes)
  0x00000000019e0038 end
  ------------------
  0x00000000019e0038 free block
  0x00000000019e0050 start (4016 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 program break
```

```
csx730_malloc(4048) = 0x19e1018 [append]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (32 bytes)
  0x00000000019e0038 end
  ------------------
  0x00000000019e0038 free block
  0x00000000019e0050 start (4016 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 program break
```

```
csx730_malloc(16384) = 0x19e2018 [append]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (32 bytes)
  0x00000000019e0038 end
  ------------------
  0x00000000019e0038 free block
  0x00000000019e0050 start (4016 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 used block
  0x00000000019e2018 start (16384 bytes)
P 0x00000000019e3000 
P 0x00000000019e4000 
P 0x00000000019e5000 
P 0x00000000019e6000 
  0x00000000019e6018 end
  ------------------
  0x00000000019e6018 free block
  0x00000000019e6030 start (4048 bytes)
P 0x00000000019e7000 end
  ------------------
P 0x00000000019e7000 program break
```

```
csx730_free(0x19e0018)
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 free block
  0x00000000019e0018 start (4072 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 used block
  0x00000000019e2018 start (16384 bytes)
P 0x00000000019e3000 
P 0x00000000019e4000 
P 0x00000000019e5000 
P 0x00000000019e6000 
  0x00000000019e6018 end
  ------------------
  0x00000000019e6018 free block
  0x00000000019e6030 start (4048 bytes)
P 0x00000000019e7000 end
  ------------------
P 0x00000000019e7000 program break
```

```
csx730_free(0x19e2018)
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 free block
  0x00000000019e0018 start (4072 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 program break
```

```
csx730_malloc(100) = 0x19e0018 [emplace]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (100 bytes)
  0x00000000019e007c end
  ------------------
  0x00000000019e007c free block
  0x00000000019e0094 start (3948 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 program break
```

```
csx730_malloc(100) = 0x19e0094 [emplace]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (100 bytes)
  0x00000000019e007c end
  ------------------
  0x00000000019e007c used block
  0x00000000019e0094 start (100 bytes)
  0x00000000019e00f8 end
  ------------------
  0x00000000019e00f8 free block
  0x00000000019e0110 start (3824 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 program break
```

```
csx730_malloc(1025) = 0x19e0110 [emplace]
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 used block
  0x00000000019e0018 start (100 bytes)
  0x00000000019e007c end
  ------------------
  0x00000000019e007c used block
  0x00000000019e0094 start (100 bytes)
  0x00000000019e00f8 end
  ------------------
  0x00000000019e00f8 used block
  0x00000000019e0110 start (1025 bytes)
  0x00000000019e0511 end
  ------------------
  0x00000000019e0511 free block
  0x00000000019e0529 start (2775 bytes)
P 0x00000000019e1000 end
  ------------------
P 0x00000000019e1000 used block
  0x00000000019e1018 start (4048 bytes)
  0x00000000019e1fe8 end
  ------------------
  0x00000000019e1fe8 free block
P 0x00000000019e2000 start (0 bytes)
P 0x00000000019e2000 end
  ------------------
P 0x00000000019e2000 program break
```

```
csx730_free(0x19e1018)
csx730_free(0x19e0018)
csx730_free(0x19e0094)
csx730_free(0x19e0110)
csx730_pheap()
  ------------------
P 0x00000000019e0000 original program break
  ------------------
P 0x00000000019e0000 program break
```

## How to Get the Skeleton Code

On Nike, execute the following terminal command in order to download the project
files into a subdirectory within your present working directory:

```
$ git clone https://github.com/cs1730/csx730-malloc.git
```

This should create a directory called `csx730-malloc` in your present working directory that
contains the project files. For this project, the only files that are included with the project
download are listed near the top of the page [here](https://github.com/cs1730/csx730-malloc).

Here is a table that briely outlines each file in the skeleton code:

| File                      | Description                                                      |
|---------------------------|------------------------------------------------------------------|
| `Doxyfile`                | Configuration file for `doxygen`.                                |
| `Makefile`                | Configuration file for `make`.                                   |
| `README.md`               | This project description.                                        |
| `SUBMISSION.md`           | Student submission information.                                  |
| `csx730_malloc.c`         | Where you will put most of your implementation.                  |
| `csx730_malloc.h`         | Thread structures, function prototypes, and macros.              |

If any updates to the project files are announced by your instructor, then you can
merge those changes into your copy by changing into your project directory
on Nike and issuing the following terminal command:

```
$ git pull
```

If you have any problems with any of these procedures, then please contact
your instructor via Piazza. 

## Project Requirements

This assignment is worth 100 points. The lowest possible grade is 0, and the 
highest possible grade is 120 (if you are enrolled in CSCI 4730).

### Functional Requirements

A functional requirement is *added* to your point total if satisfied.
There will be no partial credit for any of the requirements that simply 
require the presence of a function related a particular functionality. 
The actual functionality is tested using test cases.

1. __(50 points) Project Compiles.__ Your submission compiles and can successfully
   link with object files expecting the symbols defined in `csx730_malloc.h`. 
   Please be aware that the __Build Compliance__ non-functional requirement still
   applies.

1. __(50 points) Implement `csx730_malloc.h` functions in `csx730_malloc.c`.__
   Each of the functions whose prototype appears in the header and does not require
   the `_CS6760_SOURCE` feature test macro must be implemented correctly in the
   corresponding `.c` file. Here is a list of the functions forming the public API:

   * __(10 points)__ `void * csx730_malloc(size_t size);`
   * __(10 points)__ `void csx730_free(void * ptr);`

   Here is a list of functions forming the (private) developer API:
   
   * __(30 points)__ `void csx730_pheap(void);`

   The documentation for each function is provided directly in
   the header. You may generate an HTML version of the corresponding
   documentation using the `doc` target provided by the project's `Makefile`.
   Students should not modify the prototypes for these functions in any way--doing
   so will cause the tester used by the grader to fail.

   You are free,  _actively encouraged_, and will likely need to write other functions, as needed,
   to support the required set of functions. It is recommended that you give private function
   names a `_csx730_` prefix. 

### 6730 Requirements

For the purposes of grading, a 6730 requirement is treated as a non-functional requirement
for students enrolled in CSCI 6730 and a functional requirement for students enrolled in
CSCI 4730. This effectively provides an extra credit opportunity to the undergraduate
students and a non-compliance penalty for the graduate students.

1. __(20 points) [PRIORITY] Implement `_CS6730_SOURCE` features__
   The `_CS6730_SOURCE` feature test macro should enable the following addtional 
   functions to the public API:

   * __(10 points)__ `void * csx730_calloc(size_t nmemb, size_t size);`
   * __(10 points)__ `void * csx730_realloc(void * ptr, size_t size);`

### Non-Functional Requirements

A non-functional requirement is *subtracted* from your point total if not satisfied. In order to
emphasize the importance of these requirements, non-compliance results in the full point amount
being subtracted from your point total. That is, they are all or nothing.

1. __(100 points) Build Compliance:__ Your project must compile on Nike
   using the provided `Makefile` and `gcc` (GCC) 8.2.0. Your code must compile,
   assemble, and link with no errors or warnings. The required compiler
   flags for this project are already included in the provided `Makefile`.

   The grader will compile and test your code using the `all` and `test` targets in
   the provided `Makefile`. The `test` target will not work until the test driver
   is provided during grading. If your code compiles, assembles, and links
   with no errors or warnings usign the `all` target, then it will very likely
   do the same with the `test` target.

1. __(100 points) Libraries:__ You are allowed to use any of the C standard library
   functions, unless they are explicitly forbidden below. A general reference for
   the C standard library is provided [here](https://en.cppreference.com/w/c).
   No other libraries are permitted. You are also **NOT**
   allowed to use any of the following: 
   * `malloc(3)`, 
   * `free(3)`,
   * `mmap(2)`, 
   * `calloc(3)`, and 
   * `realloc(3)`.

1. __(100 points) `SUBMISSION.md`:__ Your project must include a properly formatted 
   `SUBMISSION.md` file that includes, at a minimum, the following information:

   * __Author Information:__ You need to include your full name, UGA email, and
     which course you are enrolled in (e.g., CSCI 4730 or CSCI 6730).

   * __Implementation Overview:__ You need to include a few sentences that provide an overview
     of your implementation.
     
   * __6730 Requirements:__ You need to include a list of the 6730 requirements that you
     would like the grader to check. These requirements will only be checked if you
     include them in this list. 
     
   * __Reflecton:__ You need to provide answers to the following questions:

     1. What do you think was the motivation behind assigning this project in this class?
     1. What is the most important thing you learned in this project?
     1. What do you wish you had spent more time on or done differently?
     1. What part of the project did you do your best work on?
     1. What was the most enjoyable part of this project?
     1. What was the least enjoyable part of this project?
     1. How could your instructor change this project to make it better next time?

   A properly formatted sample `SUBMISSION.md` file is provided that may be modified to
   help fulfill this non-functional requirement.

1. __(25 points) Memory Leaks:__ Your submission should not result in any memory leaks.
   The grader will check this using `valgrind(1)`.

1. __(25 points) Code Documentation:__ Any new functions or macros must be properly documented
   using Javadoc-style comments. An example of such comments can be seen in the souce code
   provided with the project. Please also use inline documentation, as needed, to explain
   ambiguous or tricky parts of your code.

## Submission Instructions

You will still be submitting your project via Nike. Make sure your project files
are on `nike.cs.uga.edu`. Change into the parent directory of your
project directory. If you've followed the instructions provided in earlier in this
document, then the name of your project directory is likely `csx730-uthread`.
While in your project parent directory, execute the following command: 

```
$ submit csx730-uthread csx730
```

If you have any problems submitting your project then please make a private Piazza
post to "Instructors" as soon as possible. 

<hr/>

[![License: CC BY-NC-ND 4.0](https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg)](http://creativecommons.org/licenses/by-nc-nd/4.0/)

<small>
Copyright &copy; Michael E. Cotterell and the University of Georgia.
This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a> to students and the public.
The content and opinions expressed on this page do not necessarily reflect the views of nor are they endorsed by the University of Georgia or the University System of Georgia.
</small>

