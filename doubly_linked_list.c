//
// Created by matt on 7/17/26.
//

#include <stdio.h>
#include <stdlib.h>

// TYPES
typedef struct Node {
    struct Node* prev;
    int data;
    struct Node* next;
} Node;

unsigned int size = 0;

// PROTOTYPES
Node* insert_at_head(Node* HEAD, int value);
Node* insert_at_tail(Node* HEAD, int value);
void print_list(Node* HEAD);
void reverse_print_list(Node* HEAD);

// FUNCTIONS
Node* insert_at_head(Node* HEAD, const int value) {
    Node *new_node = malloc(sizeof(struct Node));

    new_node->prev = NULL;
    new_node->data = value;
    new_node->next = HEAD;

    if (HEAD != NULL) {
        HEAD->prev = new_node;
    }

    size++;

    return new_node;
}

Node* insert_at_tail(Node* HEAD, const int value) {
    if (HEAD == NULL) {
        return insert_at_head(HEAD, value);
    }

    Node *last_node = HEAD;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }

    Node *new_node = malloc(sizeof(struct Node));

    new_node->prev = last_node;
    new_node->data = value;
    new_node->next = NULL;

    last_node->next = new_node;

    size++;

    return HEAD;
}

void free_list(Node *HEAD) {
    if (HEAD == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node *current = HEAD;

    while (current != NULL) {
        Node *next_node = current->next;

        free(current);

        current = next_node;
    }

    size = 0;
}

void print_list(Node *HEAD) {
    if (HEAD == NULL) {
        printf("The list is empty.\n");
        return;
    }

    const Node *walker = HEAD;
    while (walker != NULL) {
        printf("%d -> ", walker->data);

        walker = walker->next;
    }

    printf("NULL\n");
}

void reverse_print_list(Node *HEAD) {
    if (HEAD == NULL) return;

    Node *temp = HEAD;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("Reversed: ");

    while (temp != NULL) {
        printf("%d -> ", temp->data);

        temp = temp->prev;
    }

    printf("NULL\n");
}

//
int main(void) {
    Node *head = NULL;

    head = insert_at_head(head, 300);
    head = insert_at_head(head, 200);
    head = insert_at_head(head, 100);

    // print_list(head);
    reverse_print_list(head);

    //
    free_list(head);
    return 0;
}
