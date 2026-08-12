//
// Created by matt on 7/18/26.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// GLOBAL
typedef struct Node {
    int data;
    struct Node *next;
} Node;

int size = 0;

// PROTOTYPES
Node *push(Node *HEAD, int value);
Node *pop(Node *HEAD);

// FUNCTIONS
Node *push(Node *HEAD, const int value) {
    Node *temp = malloc(sizeof(struct Node));
    temp->data = value;
    temp->next = HEAD;

    size++;
    return temp;
}

Node *pop(Node *HEAD) {
    if (HEAD == NULL || size == 0) {
        printf("Stack is empty!\n");
        exit(1);
    }

    Node *temp = HEAD;
    HEAD = HEAD->next;

    free(temp);
    size--;

    return HEAD;
}

void print(const Node *HEAD) {
    if (HEAD == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    const Node *walker = HEAD;
    while (walker->next != NULL) {
        printf("%d ", walker->data);

        walker = walker->next;
    }

    printf("%d\n", walker->data);
}

void free_list(Node *HEAD) {
    if (HEAD == NULL) {
        printf("Stack is empty.\n");
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

int main(void) {
    Node *HEAD = NULL;

    HEAD = push(HEAD, 1);
    HEAD = push(HEAD, 2);
    HEAD = push(HEAD, 3);

    print(HEAD);

    HEAD = pop(HEAD);
    print(HEAD);

    //
    free_list(HEAD);
    return 0;
}