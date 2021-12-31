// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/31
// File: SLR.c
// Description: Convert token in SLR to index
// ******************************************

#include <string.h>

int ConvertTokenToIndex(char* token) {
    if (strncmp(token, "$", 1) == 0) {
        return 0;
    }
    if (strncmp(token, "id", 2) == 0) {
        return 1;
    }
    if (strncmp(token, "text", 4) == 0) {
        return 2;
    }
    if (strncmp(token, "sig", 3) == 0) {
        return 3;
    }
    if (strncmp(token, "join", 4) == 0) {
        return 4;
    }
    if (strncmp(token, "or", 2) == 0) {
        return 5;
    }
    if (strncmp(token, "(", 1) == 0) {
        return 6;
    }
    if (strncmp(token, ")", 1) == 0) {
        return 7;
    }
    if (strncmp(token, "_", 1) == 0) {
        return 8;
    }
    if (strncmp(token, "<", 1) == 0) {
        return 9;
    }
}
