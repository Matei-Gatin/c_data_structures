#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

extern unsigned int size;

Node *add_first(Node *HEAD, int value);

Node *add(Node *HEAD, int value, int pos);

Node *add_last(Node *HEAD, int value);

Node *delete_first(Node *HEAD);

Node *delete_last(Node *HEAD);

Node *delete(Node *HEAD, int pos);

Node *reverse_list(Node *HEAD);

Node *reverse_list_recursive(Node *HEAD);

int search(Node *HEAD, int target);

int find_middle(Node *HEAD);

void print_linked_list(const Node *HEAD);

void print_linked_list_recursive(const Node *HEAD);

void print_linked_list_recursive_reversed(const Node *HEAD);

void free_list(Node *HEAD);

#endif
