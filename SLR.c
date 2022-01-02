// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/31
// File: SLR.c
// Description: Convert token in SLR to index
// ******************************************

#include <string.h>
#include <stdlib.h>

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

int ConvertNonterminalToIndex(char NonTerminal) {
    switch (NonTerminal) {
        case 'E': {
            return 0;
        }
        case 'T': {
            return 1;
        }
        case 'P': {
            return 2;
        }
        case 'Q': {
            return 3;
        }
        case 'R': {
            return 4;
        }
        case 'N': {
            return 5;
        }
        default: {
            // never come here
            return -1;
        }
    }
}

int GetStateFromActionString(char* action) {
    char state[3] = {0};

    // check how many digits in action
    strcpy_s(state, 3, action + 1);

    return atoi(state);
}
