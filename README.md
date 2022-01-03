# CPL

[![Lines of code](https://img.shields.io/tokei/lines/github/christianstefaniw/cpl)

My first attempt at making a programming language! I made this language from scratch following no tutorials. I did a couple hours of research to learn about the components needed to build an interpreted language (lexer, parser, evaluator, Abstract Syntax Tree, etc) and then built each component from scratch based on articles descriptions of them. Obviously this language is very basic and not super well put togehter (whoops memory management :(, documentation, tests, etc) but as a project that I did only for learning I am quite pleased with the amount of knowledge that I gained.  
  
CPL only works on Linux *

### Language Features:
- variables
- print statements
- functions
- scope

### How CPL Code is Run:
1. Lexer
    - Turns the raw text into tokens with a type and a value to be read by the parser
2. Parser
    - Parses the given tokens into an AST (Abstract Syntax Tree) to be read by the evaluator
3. Evaluator
    - Traverses and evaluates the AST


Here is a small sample program
```
# this is a comment, it will be ignored by cpl

# below is a function declaration
my_func${
    print@"run in my_func function";
}

# below is how you call a function
my_func@;

# must include semi-colon or error thrown
# my_func@ -> this code will not run

# print statements are also built in
print@"hello, world";
print@12345;

# there are also variables (these variables are global)
# there can't be spaces between the equal sign
my_int_variable=4;
my_str_variable="stored in variable";

# you can print variables
print@my_int_variable;
print@my_str_variable;

# you can also print variables in a function
print_vars_func${
    print@my_int_variable;
    print@my_str_variable;
}

print_vars_func@;

# there are also local variables
func_with_local_vars${
    local="I'm local!";
    print@local;
}

func_with_local_vars@;

# print@local; <- this will cause an error

```

output:
```
run in my_func function
hello, world
12345
4
stored in variable
4
stored in variable
I'm local!
```
