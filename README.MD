# Compiler create for LOX language , Guided by crafting interpreters Book


# Language Grammer
- Program -> statement* EOF;
- declatration -> varDeclaration | statement;
- varDeclaration -> "var" IDENTIFIER "=" expression ";" ;
- statement -> expressionStatement | PrintStatement ;
- expressionStatement -> Expression ":" ;
- PrintStatement -> "print" expression ";" ;
- Expression -> Assignment ;
- Assignment -> IDENTIFIER "=" assignment | equality ;
- Ternary -> Equality ( "?" Equality ":" Equality )* ;
- Equality -> Comparison (("!=" | "==" ) Comparison)* ;
- Comparison -> Term ( (">=" | ">" | "<" | "<=" ) Term)* ;
- Term -> Factor ( ("+" | "-") Factor)* ;
- Factor -> Unary ( ("*" | "/") Unary)* ;
- Unary -> ("!" | "-") Unary | Primary ;
- Primary -> NUMBER | STRING | "true" | "false" | "nil"| "(" Expression ")" | IDENTIFIER

# Supported Features
  ## operators and keywords
  - "?:" (ternary operator)
  - "=="
  - "!="
  - "="
  - "/"
  - "*"
  - "+"
  - "-"
  - "!"
  - ">="
  - "<="
  - "<"
  - ">"
  - "."
  - and
  - Or
  - class
  - true
  - false
  - fun
  - for
  - while
  - if
  - else
  - nil
  - print
  - return
  - super
  - this
  - var

  ## comments
  - single line comments //
  - multi line comments /* */


  ## behaviour
  - concatinating strings using + => if either of the operands is a string
  - no declration of variables without initilization


# Code Rules
  * No Raw pointers for ownership Representation , use Unique pointers instead to define owner ship
  * Passing pointers could be Indicated by Raw Pointers or pass unique pointer by const&
  * Moving ownership of smart pointers should be indicated by a method / function that accepts Rvalues Refs ONLY (not const lvalue &) to detect methods that move owenership
