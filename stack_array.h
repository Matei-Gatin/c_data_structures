#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

void init_stack();

void free_stack();

void push(void *value);

void *pop();

void *top_item();

int is_empty();

int size();

#endif
