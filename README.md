# Matrix Gaussian Elimination Reductor
A simple program that applies the Gaussian elimination algorithm to matrices.
It implements fractions and simple fraction operations to minimize floating point errors.
### Usage
`cat matrix.csv | program >> out.csv`
**Important:** With the current implementation, it is **required** that the last **semicolon** in the **CSV** be replaced with a `\n`. The output of the program will be properly formatted however.
### Build
There's a simple **Makefile** that allows building the program for **release**:
`make release`
Building it for **debugging**:
`make`
And **cleaning**:
`make clean`
### Notes
The function prefix `u_` stands for *unsafe*, meaning that the function offers no error handling. Usually these functions return `void`, a structure that has no defined error element or an `int` but error handling is incomplete.
Currently
