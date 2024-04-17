PS: This program is heavily supported by AI, stackoverflow.com and W3schools.com. 

**How the code works; step by step:**

1. The program starts by including the necessary header files: `stdio.h`, `stdlib.h`, `string.h`, and `ctype.h`.
2. A `Stack` structure is defined to represent a stack data structure. It contains three members: `data` (a dynamically allocated array to store the stack elements), `top` (the index of the topmost element in the stack)
   and `capacity` (the current capacity of the `data` array).
4. The `init_stack` function initializes a `Stack` instance by setting `top` to -1 (indicating an empty stack), `capacity` to 0, and `data` to `NULL`.
5. The `push` function adds a new element `c` to the top of the stack. If the `data` array is full, it doubles the capacity by reallocating memory using `realloc`. Then, it increments `top` and stores `c` at the new top position.
6. The `pop` function removes and returns the topmost element from the stack. If the stack is empty, it prints an "Stack Underflow" error message and exits the program.
7. The `is_operator` function checks if a given character `c` is an operator (+, -, *, /, %) by searching for it in the string "+-*/%" using `strchr`.
8. The `precedence` function returns the precedence level of an operator character `c`. It uses a `switch` statement to assign a higher precedence (2) to `*`, `/`, and `%`, and a lower precedence (1) to `+` and `-`.
   If the character is not an operator, it returns -1.
10. The `reverse_string` function reverses the order of characters in a given string `str` using a simple in-place swapping algorithm.
11. The `infix_to_prefix` function is the core of the program. It takes an infix expression as input and returns the corresponding prefix expression as a dynamically allocated string. Here's how it works:
   - It creates two stacks: `op_stack` for operators and `res_stack` for the result.
   - It makes a copy of the input infix expression (`reversed`) and reverses it using `reverse_string`.
   - It iterates through the `reversed` string:
     - If the current character is an operand (alphanumeric), it pushes it onto `res_stack`.
     - If the current character is an opening parenthesis `(`, it pushes it onto `op_stack`.
     - If the current character is a closing parenthesis `)`, it repeatedly pops from `op_stack` and pushes onto `res_stack` until an opening parenthesis `(` is encountered, then discards the `(`.
     - If the current character is an operator, it repeatedly pops from `op_stack` and pushes onto `res_stack` until it encounters an operator with lower precedence or the stack is empty, then pushes the current operator onto `op_stack`.
     - If the current character is invalid, it prints an error message and returns `NULL`.
   - After processing the entire expression, it pops any remaining operators from `op_stack` and pushes them onto `res_stack`.
   - It reverses the contents of `res_stack` to get the final prefix expression and adds a null terminator.
   - It frees the `reversed` string and returns the dynamically allocated prefix expression string.

11. In the `main` function, a loop is used to prompt the user for an infix expression repeatedly until a valid expression is entered.
    - It declares a character array `infix` to store the user input and a pointer `prefix` to store the resulting prefix expression.
    - Inside the `do-while` loop:
      - It prompts the user to enter an infix expression using `printf` and reads the input using `fgets`.
      - If `fgets` fails (returns `NULL`), it prints an error message and exits the program.
      - It calls `infix_to_prefix` with the user input and stores the result in `prefix`.
      - If `prefix` is not `NULL` (i.e., the input expression is valid), it prints the prefix expression using `printf`, frees the allocated memory using `free`, and breaks out of the loop.
      - If `prefix` is `NULL` (i.e., the input expression is invalid), it prints an error message and continues the loop to prompt the user again.

The program continues to run until the user enters a valid infix expression, at which point it prints the corresponding prefix expression and exits.
