# Compiler create for LOX language , Guided by crafting interpreters Book


# Language Grammer
- Program -> Declaration* EOF;
- Declaration -> VarDeclaration | Statement;
- VarDeclaration -> "var" IDENTIFIER "=" expression ";" ;
- Statement -> ExpressionStatement | PrintStatement | BlockStatement | IfStatement | WhileStatement | ForStatement;
- ExpressionStatement -> Expression ":" ;
- PrintStatement -> "print" expression ";" ;
- BlockStatement -> "{" Declaration* "}" ;
- IfStatement -> "if" "(" expression  ")" "{" BlockStatement "}" ("else" "{" statement "}") ? ;
- WhileStatement -> "while" "(" expression ")" "{" BlockStatement "}" ;
- ForStatement -> "for" "(" (VarDeclaration | ExpressionStatement | ";" )?  expression? ";" expression? ")" "{" BlockStatement "}" ;
- Expression -> Assignment ;
- Assignment -> IDENTIFIER "=" assignment | Ternary ;
- Ternary -> Logic_or ( "?" Logic_or ":" Logic_or )* ;
- Logic_or -> Logic_and ( "or" Logic_and )* ;
- Logic_and -> Equality ( "and" Equality )* ;
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
  - no declration of variables without initilization (mandatory initilization)


# Code Rules
  * No Raw pointers for ownership Representation , use Unique pointers instead to define owner ship
  * Passing pointers could be Indicated by Raw Pointers or pass unique pointer by const&
  * Moving ownership of smart pointers should be indicated by a method / function that accepts Rvalues Refs ONLY (not const lvalue &) to detect methods that move owenership
