//
// Created by matt on 7/18/26.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack_array.h"

//

// GLOBAL VARIABLES
void **stack;
int top = -1;
int max_size = 10;

// PROTOTYPES
void resize();

// FUNCTIONS
void init_stack() {
    stack = malloc(max_size * sizeof(void *));

    if (stack == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

void free_stack() {
    free(stack);
    stack = NULL;
    top = -1;
    max_size = 10;
}

void resize() {
    max_size *= 2;

    void **temp = realloc(stack, max_size * sizeof(void *));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    stack = temp;
}

void push(void *value) {
    if (top + 1 == max_size) {
        resize();
    }

    top++;
    stack[top] = value;
}

void *pop() {
    if (top == -1) {
        printf("Stack Underflow! The stack is empty.\n");
        exit(1);
    }

    void *value = stack[top];
    top--;
    return value;
}

void *top_item() {
    if (top == -1) {
        printf("The stack is empty.\n");
        exit(1);
    }

    return stack[top];
}

int is_empty() {
    return top == -1;
}

int size() {
    return top + 1;
}