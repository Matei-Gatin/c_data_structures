//
// Created by matt on 7/22/26.
//

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_array.h"

// === HELPER FUNCTIONS ===
bool isOperator(const char *token) {
    return strcmp(token, "+") == 0 ||
        strcmp(token, "-") == 0 ||
        strcmp(token, "*") == 0 ||
        strcmp(token, "/") == 0 ||
        strcmp(token, "^") == 0;
}

bool isOperatorChar(const char token) {
    return token == '+' || token == '-' || token == '*' || token == '/' || token == '^';
}

int floorDivision(const int x, const int y) {
    if (x * y < 0 || x % y != 0) {
        return (x / y) - 1;
    }

    return x / y;
}

int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool hasHigherOrEqualPrecedence(const char* top_op, const char current_op) {
    return getPrecedence(*top_op) >= getPrecedence(current_op);
}

// =============================================================


// === FUNCTIONS ===
int evaluatePostfix(char** arr, const int n) {
    init_stack();

    for (int i = 0; i < n; i++) {
        if (isdigit(arr[i][0]) || strlen(arr[i]) > 1 && arr[i][0] == '-') {
            int* nr_repr = malloc(sizeof(int));
            *nr_repr = atoi(arr[i]);

            push(nr_repr);
        } else if (isOperator(arr[i])) {
            int* val1 = pop();
            int* val2 = pop();

            if (strcmp(arr[i], "+") == 0) {
                int* nr_repr = malloc(sizeof(int));
                *nr_repr = *val2 + *val1;
                push(nr_repr);
            } else if (strcmp(arr[i], "-") == 0) {
                int* nr_repr = malloc(sizeof(int));
                *nr_repr = *val2 - *val1;
                push(nr_repr);
            } else if (strcmp(arr[i], "/") == 0) {
                int* nr_repr = malloc(sizeof(int));
                *nr_repr = floorDivision(*val2, *val1);
                push(nr_repr);
            } else if (strcmp(arr[i], "*") == 0) {
                int* nr_repr = malloc(sizeof(int));
                *nr_repr = *val2 * *val1;
                push(nr_repr);
            } else if (strcmp(arr[i], "^") == 0) {
                int* nr_repr = malloc(sizeof(int));
                *nr_repr = (int) pow(*val2, *val1);
                push(nr_repr);
            }


            free(val1);
            free(val2);
        }
    }

    int* final_ptr = pop();
    const int final_answer = *final_ptr;

    if (!is_empty()) {
        while (!is_empty()) {
            int* to_pop = pop();
            free(to_pop);
        }

        printf("Invalid character count in the array.\n");
        return -1;
    }

    free(final_ptr);
    free_stack();

    return final_answer;
}


char* infix_to_postfix(char* expr, int len) {
    init_stack();

    char *res = malloc((len * 2 + 1) * sizeof(char));
    int res_index = 0;

    // 3 * (2 + 2)
    // 3  2  2+
    // STACK: * ( +

    for (int i = 0; i < len; i++) {
        if (isdigit(expr[i])) {
            res[res_index] = expr[i];
            res_index++;
        } else if (expr[i] == ' ') {
            res[res_index] = ' ';
            res_index++;
        } else if (expr[i] == '(') {
            char *open_paren = malloc(sizeof(char));
            *open_paren = expr[i];
            push(open_paren);
        } else if (expr[i] == ')') {
            while (!is_empty() && *(char*) top_item() != '(') {
                res[res_index] = ' '; // add a space before the element
                res_index++;

                char *top_element = pop();

                res[res_index] = *top_element;
                res_index++;

                res[res_index] = ' ';
                res_index++;

                free(top_element);
            }

            char *open_paren = pop();
            free(open_paren);
        } else if (isOperatorChar(expr[i])) {
            while (!is_empty() && hasHigherOrEqualPrecedence(top_item(), expr[i])) {
                char *top_element = pop();

                res[res_index] = *top_element;
                res_index++;

                res[res_index] = ' ';
                res_index++;

                free(top_element);
            }

            char *operator = malloc(sizeof(char));
            *operator = expr[i];
            push(operator);
        }
    }

    while (!is_empty()) {
        res[res_index] = ' ';
        res_index++;

        char *top_element = pop();
        res[res_index] = *top_element;
        res_index++;

        free(top_element);
    }

    free_stack(); // free the stack in the end

    res[res_index] = '\0';
    return res;
}

int main(void) {
    char infix[] = "3 * (2 + 2)"; // Res: 12

    int infix_len = strlen(infix);
    char *arr = infix_to_postfix(infix, infix_len); // string

    char* token_arr[50]; // array of strings
    int n = 0;

    char *token = strtok(arr, " ");

    while (token != NULL) {
        token_arr[n] = token;
        n++;

        token = strtok(NULL, " ");
    }

    for (int i = 0; i < n; ++i) {
        printf("%c ", token_arr[i][0]);
    }

    printf("\nResult: %d\n", evaluatePostfix(token_arr, n));

    free(arr);

    return 0;
}