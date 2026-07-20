//
// Created by matt on 7/20/26.
//


//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL VARIABLES
char *stack;
int top = -1;
int max_size = 255;

// PROTOTYPES
void push(char value);
char pop();
void reverse_string_with_stack(char *str);

// FUNCTIONS
void push(const char value) {
    if (top + 1 == max_size) {
        printf("Stack is full!\n");
        return;
    }

    top++;
    stack[top] = value;
}

char pop() {
    if (top == -1) {
        printf("Stack is empty!\n");
        exit(1);
    }

    const char char_to_return = stack[top];

    top--;

    return char_to_return;
}

void reverse_string_with_stack(char *str) {
    const size_t size_str = strlen(str);

    for (int i = 0; i < size_str; i++) {
        push(str[i]);
    }

    for (int i = 0; i < size_str; i++) {
        str[i] = pop();
    }
}

int main(void) {
    stack = malloc(max_size * sizeof(char));

    if (stack == NULL) {
        printf("Memory allocation failed!");
        return 1;
    }

    char my_message[] = "Hello Citadel!";

    printf("Original: %s\n", my_message);

    reverse_string_with_stack(my_message);

    printf("Reversed: %s\n", my_message);

    free(stack);

    return 0;
}