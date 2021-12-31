// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/31
// File: state.h
// Description: Used to define state stack
// ******************************************

#include <stdlib.h>
#include <string.h>
#include "state.h"

int CreateStack(StateStack* stack, int size) {
    if (size <= 0) { // zero or negative size is invalid
        // fail to create stack
        return 0;
    }
    stack->pairs = (Pair*)malloc(sizeof(Pair) * size);
    stack->size = size - 1;
    stack->top = -1;
    return 1;
}

int IsEmpty(StateStack *stack) {
    if (stack->top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int IsFull(StateStack *stack) {
    if (stack->top == stack->size) {
        return 1; // full
    }
    else {
        return 0; // not full
    }
}

int Push(StateStack *stack, char* token, int state) {
    if (IsFull(stack)) {
        return 0;
    }
    Pair pair;
    strcpy_s(pair.token, strlen(token) + 1, token);
    pair.state = state;
    stack->pairs[++(stack->top)] = pair;
    return 1;
}

int Pop(StateStack *stack, Pair *pair) {
    if (IsEmpty(stack)) {
        return 0;
    }
    *pair = stack->pairs[stack->top];
    (stack->top)--;
    return 1;
}
