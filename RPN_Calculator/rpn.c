#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *data;
    int top, capacity;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
    s->capacity = 0;
    s->data = NULL;
}

void push(Stack *s, char c) {
    if (s->top == s->capacity - 1) {
        s->capacity = (s->capacity == 0) ? 1 : s->capacity * 2;
        s->data = realloc(s->data, s->capacity * sizeof(char));
    }
    s->data[++s->top] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        fprintf(stderr, "Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int is_operator(char c) {
    return strchr("+-*/%()", c) != NULL;
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char *infix_to_prefix(const char *infix) {
    Stack op_stack, res_stack;
    init_stack(&op_stack);
    init_stack(&res_stack);

    char *reversed = strdup(infix);
    reverse_string(reversed);

    for (int i = 0; reversed[i]; i++) {
        if (isalnum(reversed[i])) {
            push(&res_stack, reversed[i]);
        } else if (reversed[i] == ')') {
            push(&op_stack, reversed[i]);
        } else if (reversed[i] == '(') {
            while (op_stack.data[op_stack.top] != ')') {
                push(&res_stack, pop(&op_stack));
            }
            pop(&op_stack);
        } else if (is_operator(reversed[i])) {
            while (op_stack.top != -1 && precedence(reversed[i]) <= precedence(op_stack.data[op_stack.top])) {
                push(&res_stack, pop(&op_stack));
            }
            push(&op_stack, reversed[i]);
        }
    }

    while (op_stack.top != -1) {
        push(&res_stack, pop(&op_stack));
    }

    reverse_string(res_stack.data);
    res_stack.data[res_stack.top + 1] = '\0';

    free(reversed);
    return res_stack.data;
}

int main() {
    char infix[100];
    char *prefix;

    do {
        printf("Enter infix expression: ");
        if (fgets(infix, sizeof(infix), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }

        prefix = infix_to_prefix(infix);
        if (prefix != NULL) {
            printf("Prefix expression: %s\n", prefix);
            free(prefix);
            break;
        } else {
            printf("Invalid expression. Please try again.\n");
        }
    } while (1);

    return 0;
}