//
// Created by matt on 7/17/26.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list/linked_list.h"
#include "stack/stack_array.h"

void reverse_liked_list_with_stack() {
    init_stack();

    Node *head = NULL;
    head = add_first(head, 300);
    head = add_first(head, 200);
    head = add_first(head, 100);

    printf("Original linked list:\n");
    print_linked_list(head);
    printf("\n");

    if (head == NULL || head->next == NULL) {
        return;
    }

    // push the nodes in the stack
    Node *walker = head;
    while (walker != NULL) {
        push(walker);
        walker = walker->next;
    }

    // find the new HEAD
    Node *new_head = head;
    while (new_head->next != NULL) {
        new_head = new_head->next;
    }

    // pop them off and reverse the links
    Node* prev_node = NULL;
    while (!is_empty()) {
        Node* popped_node = pop();

        if (prev_node != NULL) {
            prev_node->next = popped_node;
        }

        prev_node = popped_node;

        // printf("Popped node with data: %d\n", popped_node->data);
    }

    if (prev_node == NULL || prev_node->next == NULL) {
        return;
    }

    prev_node->next = NULL;

    // print reversed list
    print_linked_list(new_head);

    // free memory
    free_list(head);
    free_stack();
}

int valid_parentheses(const char* exp) {
    if (exp == NULL) {
        printf("Expression is empty!\n");
        return false;
    }

    init_stack();

    char open_round = '(';
    char open_square = '[';
    char open_curly = '{';

    char close_round = ')';
    char close_square = ']';
    char close_curly = '}';

    const size_t exp_len = strlen(exp);

    if (exp_len == 1) {
        return false;
    }
    // ([})
    for (int i = 0; i < exp_len; i++) {
        if (exp[i] == open_round || exp[i] == open_square || exp[i] == open_curly) {
            char* random_paren = malloc(sizeof(char));
            *random_paren = exp[i];
            push(random_paren);
        } else if (exp[i] == close_round || exp[i] == close_square || exp[i] == close_curly) {
            if (is_empty()) {
                return false;
            }

            char* popped_char_ptr = pop();
            char popped_char = *popped_char_ptr;

            if (popped_char != '(' && exp[i] == ')') {
                return false;
            }
            if (popped_char != '[' && exp[i] == ']') {
                return false;
            }
            if (popped_char != '{' && exp[i] == '}') {
                return false;
            }

            free(popped_char_ptr);
        }
    }

    int is_empty_ = is_empty();

    while (!is_empty()) {
        char *popped_char_ptr = pop();
        free(popped_char_ptr);
    }

    free_stack();

    return is_empty_;
}

int main(void) {
    // reverse_liked_list_with_stack();

    // int valid1 = valid_parentheses("(())");
    // int valid2 = valid_parentheses("([])");
    // int valid3 = valid_parentheses("(([]))");
    // int valid4 = valid_parentheses("(((");
    // int valid5 = valid_parentheses("]]]");
    // int valid6 = valid_parentheses("([})");
    //
    // printf("1: %d, 2: %d, 3: %d, 4: %d, 5: %d, 6: %d\n", valid1, valid2, valid3, valid4, valid5, valid6);

    return 0;
}