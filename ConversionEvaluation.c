#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure for the stack
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to initialize the stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack *s, char item) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack is full. Cannot push %c\n", item);
    } else {
        s->items[++s->top] = item;
    }
}

// Function to pop an item from the stack
char pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty. Cannot pop.\n");
        return '\0';
    } else {
        return s->items[s->top--];
    }
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix() {
    struct Stack stack;
    initialize(&stack);

    char infix[MAX_SIZE], postfix[MAX_SIZE];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    int i, j = 0;
    for (i = 0; infix[i]; i++) {
        char token = infix[i];
        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&stack, token);
        } else if (token == ')') {
            while (!isEmpty(&stack) && stack.items[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && stack.items[stack.top] != '(') {
                printf("Invalid expression\n");
                return;
            } else {
                pop(&stack);
            }
        } else {
            while (!isEmpty(&stack) && precedence(token) <= precedence(stack.items[stack.top])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

// Function to convert infix expression to prefix expression
void infixToPrefix() {
    // To be implemented
    printf("Function not implemented yet.\n");
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack stack;
    initialize(&stack);
    int i;

    for (i = 0; postfix[i]; i++) {
        char token = postfix[i];
        if (isdigit(token)) {
            push(&stack, token - '0');
        } else {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (token) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(&stack);
}

// Function to evaluate a prefix expression
int evaluatePrefix(char* prefix) {
    // To be implemented
    printf("Function not implemented yet.\n");
    return 0;
}

int main() {
    int choice;
    char expression[MAX_SIZE];

    while (1) {
        printf("\n23MCA0078 || PRASATH VS\n\n");
		printf("Menu:\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Convert Infix to Prefix\n");
        printf("3. Evaluate Postfix Expression\n");
        printf("4. Evaluate Prefix Expression\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                infixToPostfix();
                break;
            case 2:
                infixToPrefix();
                break;
            case 3:
                printf("Enter the postfix expression: ");
                scanf("%s", expression);
                printf("Result: %d\n", evaluatePostfix(expression));
                break;
            case 4:
                printf("Enter the prefix expression: ");
                scanf("%s", expression);
                printf("Result: %d\n", evaluatePrefix(expression));
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

