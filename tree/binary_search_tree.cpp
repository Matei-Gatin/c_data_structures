//
// Created by matt on 8/4/26.
//

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
#include <iostream>

// #include "deque.c"


typedef struct NodeBst {
    int data;
    struct NodeBst* left;
    struct NodeBst* right;
} NodeBst;

unsigned int nrOfNodes = 0;

// PROTOTYPES
NodeBst* insert(NodeBst* current_node, int data);
bool contains(const NodeBst* current_node, int data);
void print_in_order(const NodeBst* current_node);
int find_min(const NodeBst* current_node);
int find_max(const NodeBst* current_node);
void free_tree(NodeBst* current_node);
NodeBst* delete_node(NodeBst* root, int target);
int get_height(NodeBst* root);
bool is_valid_bst(NodeBst* current_node);
bool validate_helper(NodeBst* current_node, long min_boundary, long max_boundary);

// FUNCTIONS
NodeBst* insert(NodeBst* current_node, const int data) {
    // BASE CASE
    if (current_node == NULL) {
        NodeBst* new_node = (NodeBst*) malloc(sizeof(NodeBst));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        nrOfNodes++;

        return new_node;
    }

    if (data <= current_node->data) {
        current_node->left = insert(current_node->left, data);
    }

    if (data > current_node->data) {
        current_node->right = insert(current_node->right, data);
    }

    return current_node; // return parent
}

bool contains(const NodeBst* current_node, const int data) {
    if (current_node == NULL) { // we reached the end, and we didn't find the number just return false
        return false;
    }

    bool is_present = false;

    if (data == current_node->data) {
        return true;
    }

    if (data < current_node->data) {
        is_present = contains(current_node->left, data);
    } else if (data > current_node->data) {
        is_present = contains(current_node->right, data);
    }

    return is_present;
}

void print_in_order(const NodeBst* current_node) {
    if (current_node == NULL) {
        return;
    }

    print_in_order(current_node->left);

    printf("%d ", current_node->data);

    print_in_order(current_node->right);
}

int find_min(const NodeBst* current_node) {
    if (current_node == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    const NodeBst* walker = current_node;

    while (walker->left != NULL) {
        walker = walker->left;
    }

    return walker->data;
}

int find_max(const NodeBst* current_node) {
    if (current_node == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    const NodeBst* walker = current_node;

    while (walker->right != NULL) {
        walker = walker->right;
    }

    return walker->data;
}

void free_tree(NodeBst* current_node) {
    if (current_node == NULL) {
        return;
    }

    free_tree(current_node->left);

    free_tree(current_node->right);

    free(current_node);
}

NodeBst* delete_node(NodeBst* root, int target) {
    if (root == NULL) {
        return root;
    }

    // find the NODE
    if (target < root->data) {
        root->left = delete_node(root->left, target);
    } else if (target > root->data) {
        root->right = delete_node(root->right, target);
    }

    // NODE found
    else {
        if (root->left == NULL) {
            NodeBst* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NodeBst* temp = root->left;
            free(root);
            return temp;
        } else {
            const int min_val = find_min(root->right);
            root->data = min_val;
            delete_node(root->right, min_val);
        }
    }

    return root;
}

int get_height(NodeBst* root) {
    if (root == NULL) {
        return -1;
    }

    int left_height = get_height(root->left); // 1

    int right_height = get_height(root->right); // 0

    return fmax(left_height, right_height) + 1;
}


// TRAVERSALS:
void pre_order_traversal(NodeBst* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    pre_order_traversal(root->left);
    pre_order_traversal(root->right);
}

void in_order_traversal(NodeBst* root) {
    if (root == NULL) return;

    in_order_traversal(root->left);
    printf("%d ", root->data);
    in_order_traversal(root->right);
}

void post_order_traversal(NodeBst* root) {
    if (root == NULL) return;

    post_order_traversal(root->left);
    post_order_traversal(root->right);
    printf("%d ", root->data);
}

// void level_order(NodeBst* root) {
//     if (root == NULL) {
//         return;
//     }
//
//     Deque* deq = new_Deque(); // takes only ints
//     deq->addLast(deq, root->data);
//
//     while (!deq->isEmpty(deq)) {
//         int top = deq->removeFirst(deq);
//         printf("%d ", top);
//         if ()
//     }
// }

bool validate_helper(NodeBst* current_node, long min_boundary, long max_boundary) {
    if (current_node == NULL) {
        return true;
    }

    if (current_node->data <= min_boundary && current_node->data >= max_boundary) {
        return false;
    }

    bool is_valid_left = validate_helper(current_node, min_boundary, current_node->data);

    bool is_valid_right = validate_helper(current_node, current_node->data, max_boundary);

    return is_valid_left && is_valid_right;
}

bool in_order_helper(NodeBst* current_node, NodeBst* prev_node) {
    if (current_node == NULL) return true;

    if (!in_order_helper(current_node->left, prev_node)) {
        return false;
    }

    if (prev_node != NULL && current_node->data <= prev_node->data) {
        return false;
    }

    prev_node = current_node;

    return in_order_helper(current_node->right, prev_node);
}

bool is_valid_bst(NodeBst* root) {
    return validate_helper(root, LONG_MIN, LONG_MAX);
}

bool is_valid_bst_2(NodeBst* root) {
    NodeBst* prev_node = NULL;

    return in_order_helper(root, prev_node);
}

int main(void) {
    NodeBst* root = NULL;

    root = insert(root, 8); // return 200
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 12);

    // pre_order_traversal(root);

    // printf("Is valid BST: %d\n", is_valid_bst(root));

    in_order_traversal(root);

    free_tree(root);

    return 0;
}
