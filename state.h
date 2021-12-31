// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/31
// File: state.h
// Description: Used to define state stack
// ******************************************

#ifndef STATE_H
#define STATE_H

typedef struct {
    char *token;
    int state;
} Pair;

typedef struct {
    Pair *pairs;
    int top;
    int size;
} StateStack;

int CreateStack(StateStack* stack, int size);
int Push(StateStack *stack, char* token, int state);
int Pop(StateStack *stack, Pair *pair);

#endif
