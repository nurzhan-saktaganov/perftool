#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef list stack;

stack *stack_create();
void stack_destroy(stack *s_p, void (*destroy_data)(void *));
void stack_push(stack *s_p, void *data);
void *stack_pop(stack *s_p);
void *stack_peek(stack *s_p);
int stack_size(stack *s_p);

#endif
