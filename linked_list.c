//
// Created by matt on 7/13/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

unsigned int size = 0;

Node* add_first(Node *HEAD, int value);
Node* add(Node *HEAD, int value, int pos);
Node* add_last(Node *HEAD, int value);

Node* delete_first(Node *HEAD);
Node* delete_last(Node *HEAD);
Node* delete(Node *HEAD, int pos);

void free_list(Node *HEAD);

//
Node* add_first(Node *HEAD, const int value) {
    Node *temp = malloc(sizeof(struct Node));
    temp->data = value;
    temp->next = HEAD;

    size++;
    return temp;
}

Node* add(Node *HEAD, const int value, const int pos) {
    if (pos < 0) {
        printf("Position must be >= 0.\n");
        return HEAD;
    }

    if (pos > size) {
        printf("Cannot insert at position %d. Current size is %d.\n", pos, size);
        return HEAD;
    }

    //
    if (pos == 0) {
        return add_first(HEAD, value);
    }

    if (pos == size) {
        return add_last(HEAD, value);
    }

    Node *walker = HEAD;
    for (int i = 0; i < pos - 1; i++) {
        walker = walker->next;
    }

    // store the next node;
    Node *temp = walker->next;

    // create new node
    Node *new_node = malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = temp;

    // assign current to new node
    walker->next = new_node;

    size++;
    return HEAD;
}

Node* add_last(Node *HEAD, const int value) {
    if (HEAD == NULL) {
        return add_first(HEAD, value);
    }

    Node *temp = HEAD;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    Node *new_node = malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;

    temp->next = new_node;

    size++;
    return HEAD;
}

Node* delete_first(Node *HEAD) {
    if (HEAD == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node *temp = HEAD;
    HEAD = HEAD->next;

    free(temp);
    size--;

    return HEAD;
}

Node* delete_last(Node *HEAD) {
    if (HEAD == NULL || size == 0) {
        printf("The list is empty.\n");
        return NULL;
    }

    if (HEAD->next == NULL) {
        return delete_first(HEAD);
    }

    Node *walker = HEAD;
    while (walker->next->next != NULL) {
        walker = walker->next;
    }

    free(walker->next);
    walker->next = NULL;

    size--;
    return HEAD;
}

Node* delete(Node *HEAD, const int pos) {
    if (pos < 0) {
        printf("Position must be >= 0.\n");
        return HEAD;
    }

    if (pos > size) {
        printf("Cannot insert at position %d. Current size is %d.\n", pos, size);
        return HEAD;
    }

    if (HEAD == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    // 1 -> 2 -> 3
    if (pos == 0) {
        return delete_first(HEAD);
    }

    if (pos == size - 1) {
        return delete_last(HEAD);
    }

    Node *walker = HEAD;
    for (int i = 0; i < pos - 1; i++) {
        walker = walker->next;
    }



    size--;

    return HEAD;
}

void print_linked_list(const Node *HEAD) {
    const Node *WALKER = HEAD;

    while (WALKER != NULL) {
        printf("%d -> ", WALKER->data);

        WALKER = WALKER->next;
    }

    printf("NULL\n");
}

void free_list(Node *HEAD) {
    Node *current = HEAD;

    while (current != NULL) {
        Node *next_node = current->next;

        free(current);

        current = next_node;
    }

    size = 0;
}

int main(void) {
    Node *head = NULL;

    head = add_first(head, 3);
    head = add_first(head, 2);
    head = add_first(head, 1);
    //
    // head = add(head, 100, 1);
    // head = add(head, 200, 0);
    // head = add(head, 300, 5);
    // head = add_last(head, 400);

    // head = delete_first(head);

    head = delete_last(head);
    print_linked_list(head);
    printf("size: %d", size);

    free_list(head);

    return 0;
}