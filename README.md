# Simplex Solver

A C++ implementation of the Simplex algorithm for solving linear programming (LP) problems in standard equality form.  
This project demonstrates proficiency in numerical methods, algorithm design, and systems-level programming.

---

## 📌 Features

- Implements the primal Simplex method from scratch
- Supports LP problems in standard equality form
- Error handling for infeasible and unbounded problems
- Command-line interface for inputting LP problems

---

## 🚀 Getting Started

### Prerequisites

- C++11 or higher

### Compilation

```bash
g++ -std=c++11 main.cpp solver.cpp tableau.cpp -o simplex_solver
```
## 🧪 Usage
Given the below LP (in **_Standard Inequality Form_**), we would first need to convert it to **_Standard Equality Form_**!
```plaintext
Maximize Z = 3x + 5y
Subject to:
2x + 3y <= 8
x + y <= 4
x, y >= 0
```
The LP in **_Standard Equality Form_** would be:
```plaintext
Maximize Z = 3x + 5y
Subject to:
2x + 3y + s1 = 8
x + y + s2 = 4
x, y, s1, s2 >= 0
```
The input for the program would be:
```plaintext
4
2
3 5 0 0 
2 3 1 8
1 1 1 4
```
where 
-  The first line represents the _number of variables_ in the LP
-  The second line represents the _number of constraints_ in the LP
-  The third line represents the _coefficients_ of the _objective function_ of the LP
-  The remaining lines represent the _coefficients_ of the _constraints_ of the LP

> **_NOTE:_**  We do **NOT** need to add the positive constraint for the LP variables, as it is captured by the formulation of the LP in **_Standard Equality Form_**.
