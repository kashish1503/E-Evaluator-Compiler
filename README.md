# E++ Expression Evaluator & Compiler

A C++ implementation of **E++**, a simple expression language for evaluating fully parenthesized arithmetic expressions with variables and arbitrary-precision rational numbers.

The project brings together expression parsing, tree-based evaluation, custom numeric types, symbol-table management, and stack-machine code generation.

## Overview

The evaluator processes E++ expressions, constructs an expression tree, and evaluates arithmetic operations using custom integer and rational-number representations. Variable values are stored in a Binary Search Tree (BST)-based symbol table.

## Features

- **Expression parsing:** Parses fully parenthesized infix expressions according to the E++ syntax.
- **Expression-tree construction:** Represents expressions as trees for structured evaluation.
- **Arbitrary-precision integers:** Implements a custom `UnlimitedInt` type rather than relying on fixed-width built-in integer types.
- **Rational arithmetic:** Implements `UnlimitedRational` for arithmetic on rational values.
- **Variable management:** Stores variable names and their evaluated values in a BST-based symbol table.
- **Expression evaluation:** Evaluates expression trees recursively using the custom numeric types.
- **Stack-machine code generation:** Includes a component for generating stack-machine instructions from expressions.
- **Dynamic memory management:** Manages dynamically allocated data used by the project’s data structures and numeric representations.

## E++ Language

E++ supports fully parenthesized infix arithmetic expressions with the following operators:

| Operator | Operation |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |

Operands can be integer constants or variables that have already been declared. Variable assignments use the `:=` operator.

### Example

```text
x := (13 + (2 / (2 / 51)))
y := ((x * 4) - (7 / 3))
```

## Main Components

### 1. `UnlimitedInt`

A custom representation for integers that can exceed the range of built-in C++ integer types. It provides the integer operations needed by the evaluator.

### 2. `UnlimitedRational`

Represents rational values using integer numerator and denominator components. It builds on `UnlimitedInt` to support rational arithmetic and simplification.

### 3. Parser and Expression Trees

The parser processes E++ expressions and builds expression trees. The tree structure provides an explicit representation of the operations and operands in an expression.

### 4. Symbol Table

A Binary Search Tree (BST) maps variable names to their evaluated rational values. It supports the variable-management operations used during evaluation.

### 5. Evaluator

The evaluator traverses expression trees, applies arithmetic operations using `UnlimitedRational`, and resolves variable references through the symbol table.

### 6. Stack-Machine Code Generator

The project also includes a component for generating stack-machine instructions from parsed expressions.

## Concepts Demonstrated

- C++ and object-oriented programming
- Data structures and tree-based symbol tables
- Parsing and expression-tree construction
- Recursive evaluation
- Arbitrary-precision integer and rational arithmetic
- Stack-machine code generation
- Dynamic memory management

## Project Context

Developed as part of coursework under **Prof. Rahul Garg, CSE Department, IIT Delhi**.

The project provided hands-on experience with the implementation of language-processing components, custom numeric representations, and core data structures in C++.
