//
// Created by matt on 7/27/26.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// PROTOTYPES
typedef struct Deque {
    // DATA
    int *array;
    int front;
    int rear;
    int maxSize;

    // FUNCTIONS
    void (*addFirst)(struct Deque* self, int value);
    void (*addLast)(struct Deque* self, int value);
    int (*peekFirst)(struct Deque* self);
    int (*peekLast)(struct Deque* self);
    int (*removeFirst)(struct Deque* self);
    int (*removeLast)(struct Deque* self);
    bool (*isFull)(struct Deque* self);
    bool (*isEmpty)(struct Deque* self);
    int (*getSize)(struct Deque* self);
    void (*Print)(struct Deque* self);
    void (*clear)(struct Deque* self);
    void (*destroy)(struct Deque* self);
    bool (*contains)(struct Deque* self, int target);
    void (*resize)(struct Deque* self);
} Deque;

void add_first(Deque *self, int value);
void add_last(Deque *self, int value);
int peek_first(Deque *self);
int peek_last(Deque *self);
int remove_first(Deque *self);
int remove_last(Deque *self);
bool is_full(Deque *self);
bool is_empty(Deque *self);
int get_size(Deque *self);
void print_deque(Deque *self);
void destroy_deque(Deque *self);
bool contains_value(Deque *self, int target);
void clear_deque(Deque *self);
void resize_deque(Deque *self);
Deque* new_Deque();

// FUNCTIONS
Deque* new_Deque() {
    Deque* deque = malloc(sizeof(Deque));

    // initialize data
    deque->front = -1;
    deque->rear = -1;
    deque->maxSize = MAX_SIZE;
    deque->array = malloc(deque->maxSize * sizeof(int));

    deque->addFirst = add_first;
    deque->addLast = add_last;
    deque->peekFirst = peek_first;
    deque->peekLast = peek_last;
    deque->removeFirst = remove_first;
    deque->removeLast = remove_last;
    deque->isFull = is_full;
    deque->isEmpty = is_empty;
    deque->getSize = get_size;
    deque->Print = print_deque;
    deque->destroy = destroy_deque;
    deque->contains = contains_value;
    deque->clear = clear_deque;
    deque->resize = resize_deque;

    return deque;
}

void add_first(Deque *self, const int value) {
    //  0    1    2
    // 100  200  300
    // (i - 1 + maxsize) % maxsize

    if (self->isFull(self)) {
        resize_deque(self);
    }

    if (self->isEmpty(self)) {
        self->rear = 0;
        self->front = 0;
        self->array[self->rear] = value;
    } else {
        self->front = (self->front - 1 + self->maxSize) % self->maxSize;
        self->array[self->front] = value;
    }
}

void add_last(Deque *self, const int value) {
    if (self->isFull(self)) {
        resize_deque(self);
    }

    if (self->isEmpty(self)) {
        self->rear = 0;
        self->front = 0;
        self->array[self->rear] = value;
    } else {
        // self->rear++;
        self->rear = (self->rear + 1) % self->maxSize;
        self->array[self->rear] = value;
    }
}

int peek_first(Deque *self) {
    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return -1;
    }

    return self->array[self->front];
}

int peek_last(Deque *self) {
    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return -1;
    }

    return self->array[self->rear];
}

int remove_first(Deque *self) {
    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return -1;
    }

    // if empty
    if (self->rear == self->front) {
        int value_removed = self->array[self->front];
        self->rear = -1;
        self->front = -1;
        return value_removed;
    }

    const int value_removed = self->array[self->front];
    self->front = (self->front + 1) % self->maxSize;
    return value_removed;
}

int remove_last(Deque *self) {
    //  0    1    2
    // 100  200  300
    // (i - 1 + maxsize) % maxsize

    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return -1;
    }

    // if empty
    if (self->rear == self->front) {
        int value_removed = self->array[self->front];
        self->rear = -1;
        self->front = -1;
        return value_removed;
    }

    int value_removed = self->array[self->rear];
    self->rear = (self->rear - 1 + self->maxSize) % self->maxSize; // move the rear
    return value_removed;
}

bool is_full(Deque *self) {
    // return self->maxSize == self->rear + 1;
    return self->front == (self->rear + 1) % self->maxSize;
}

bool is_empty(Deque *self) {
    return self->rear == -1 && self->front == -1;
}

int get_size(Deque *self) {
    if (self->isEmpty(self)) {
        return 0;
    }

    // ((REAR - FRONT + MAX_SIZE) % MAX_SIZE) + 1

    return ((self->rear - self->front + self->maxSize) % self->maxSize) + 1;
}

void print_deque(Deque *self) {
    if (self == NULL) {
        return;
    }

    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return;
    }

    int i = self->front;

    while (i != self->rear) {
        printf("%d\n", self->array[i]);
        i = (i + 1) % self->maxSize;
    }

    printf("%d", self->array[i]);
}

void destroy_deque(Deque *self) {
    if (self == NULL) {
        return;
    }

    free(self->array);
    free(self);
}

bool contains_value(Deque *self, const int target) {
    if (self->isEmpty(self)) {
        printf("The Deque is empty!\n");
        return false;
    }

    int curr = self->front;

    while (curr != self->rear) {
        if (self->array[curr] == target) {
            return true;
        }

        curr = (curr + 1) % self->maxSize;
    }

    return self->array[curr] == target;
}

void clear_deque(Deque *self) {
    self->front = -1;
    self->rear = -1;
}

void resize_deque(Deque *self) {
    // resize the deque by doubling the MAX_SIZE

    // [100, 200, 0, 400, 300] MAX_SIZE 5
    // [0, 0, 0, 0, 0, 0, 0, 0, 0, 0] MAX_SIZE 10

    int new_size = self->maxSize * 2;
    int* new_array = malloc(new_size * sizeof(int));

    int curr = self->front, i = 0;
    while (curr != self->rear) {
        new_array[i] = self->array[curr];

        // update pointers
        curr = (curr + 1) % self->maxSize;
        i++;
    }

    // update last value
    new_array[i] = self->array[curr];

    // update data
    self->front = 0;
    self->rear = i;
    self->maxSize = new_size;
    free(self->array);
    self->array = new_array;
}

// int main(void) {
//     Deque* deque = new_Deque();
//
//     deque->addLast(deque, 100);
//     deque->addLast(deque, 200);
//     deque->addLast(deque, 300);
//     deque->addLast(deque, 400);
//     deque->addFirst(deque, 500);
//     deque->addFirst(deque, 600);
//
//     for (int i = 0; i < deque->maxSize; i++) {
//         printf("%d\n", deque->array[i]);
//     }
//
//     // [100, 200, 0, 400, 300]
//
//     // clean up memory
//     deque->destroy(deque);
//
//     return 0;
// }

