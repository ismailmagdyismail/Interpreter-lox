# Compiler create for LOX language , Guided by crafting interpreters Book








# Code Rules
  * No Returning Null , use optionals instead to avoid null pointers exceptions
  * No Exceptions , use Error as values instead
  * No Raw pointers for ownership Representation , use Unique pointers instead to define owner ship
  * Passing pointers could be Indicated by Raw Pointers or pass unique pointer by const&
  * Moving ownership of smart pointers should be indicated by a method / function that accepts Rvalues Refs ONLY (not const lvalue &) to detect methods that move owenership
