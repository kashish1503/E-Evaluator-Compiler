
<h1>Expression Evaluator</h1>

This project implements an Expression Evaluator for a simple language called E++, focusing on arithmetic expressions involving rational numbers with unlimited precision. It incorporates parsing, symbolic evaluation, and storage of variables using key data structures and algorithms.

<h4>Overview</h4>

The Expression Evaluator interprets and computes results from fully parenthesized infix arithmetic expressions, supports variables, and handles arbitrary-precision rational numbers. It constructs and evaluates expression trees, while managing variable assignments using a binary search tree (BST) as a symbol table.

<h4>Key Features</h4>
	•	Support for Rational Arithmetic
Evaluates expressions with arbitrary-sized integers and rational numbers using custom UnlimitedInt and UnlimitedRational classes.
	•	Expression Parsing and Tree Construction
Converts each E++ expression into a unique parse tree based on syntactic rules, ensuring structured evaluation.
	•	Expression Evaluation
Recursively evaluates expression trees, performing operations like addition, subtraction, multiplication, and division on UnlimitedRational values.
	•	Symbol Table Implementation
Maintains a symbol table using an unbalanced BST for mapping variables to their evaluated rational values.

<h4>Expression Language (E++)</h4>
	•	Fully parenthesized infix expressions with operators: +, -, *, /.
	•	Operands may be constants or previously declared variables.
	•	Each line is either a variable assignment (x := expression) or, in future extensions, a return statement.
	•	Variables must be declared before use and are immutable once assigned.

<h5>Examples of Valid Expressions</h5>
	•	((a + b))
	•	((x * y) - z)
	•	((5 + x) / (a + b))
	•	(((x + y) * (a - b)) - (c / d))

<h4>Components</h4>

*1. UnlimitedInt*

A class to represent integers of arbitrary size:
	•	Handles all basic arithmetic operations.
	•	Manages memory manually to support unlimited integer capacity.

*2. UnlimitedRational*

A class built on UnlimitedInt:
	•	Represents rational numbers as p/q where p and q are coprime.
	•	Supports arithmetic operations and rational simplification.
	•	Special handling for division by zero and undefined values (0/0).

*3. Parser*
	•	Builds expression trees from tokenized input.
	•	Ensures structure adheres to E++ grammar and rules.

*4. Symbol Table*
	•	Implemented using a binary search tree.
	•	Supports insertion, lookup, and deletion of variables.

*5. Evaluator*
	•	Orchestrates parsing and evaluation of expressions.
	•	Stores parsed trees and variable values.
	•	Ensures correct tree construction and evaluation logic.

<h4>Example Usage</h4>

x := (13 + (2 / (2 / 51)))
y := ((x * 4) - (7 / 3))

These expressions are tokenized, parsed into trees, evaluated using UnlimitedRational, and stored in the symbol table.

<h4>Notes</h4>
	•	The evaluator expects syntactically correct input (as per E++ rules).
	•	No built-in error handling for malformed expressions.
	•	Designed to handle extremely large numbers without precision loss.
