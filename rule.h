// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/26
// File: rule.h
// Description: Used to define the structure to store production rule
// ******************************************

#ifndef rule_H
#define rule_H

typedef struct {
    char left;
    char *right[10];
} Rule;

#endif
