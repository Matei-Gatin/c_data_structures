//
// Created by matt on 7/18/26.
//

#include <stdio.h>
#include <stdlib.h>

//

// GLOBAL VARIABLES
int *stack;
int top = -1;
int max_size = 10;

// PROTOTYPES
int pop();
void resize();
void push(int value);
void print();
int top_item();
int is_empty();

// FUNCTIONS
void push(const int value) {
    if (top + 1 == max_size) {
        resize();
    }

    top++;
    stack[top] = value;
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow! The stack is empty.\n");
        exit(1);
    }

    const int value = stack[top];
    top--;
    return value;
}

int top_item() {
    if (top == -1) {
        printf("The stack is empty.\n");
        exit(1);
    }

    return stack[top];
}

int is_empty() {
    return top == -1;
}

void resize() {
    max_size *= 2;
    int *temp = realloc(stack, max_size * sizeof(int));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    stack = temp;
}

void print() {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    for (int i = 0; i <= top; i++) {
        if (i == top) {
            printf("%d\n", stack[i]);
            return;
        }

        printf("%d, ", stack[i]);
    }
}

int main(void) {
    stack = malloc(max_size * sizeof(int));

    if (stack == NULL) return 1;

    for (int i = 100; i <= 1200; i += 100) {
        push(i);
    }
    print();

    return 0;
}