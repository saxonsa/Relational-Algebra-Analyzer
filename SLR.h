// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/26
// File: SLR.h
// Description: Denote ACTION and GOTO table
// ******************************************

#ifndef SLR_H
#define SLR_H

int ConvertTokenToIndex(char* token);
int ConvertNonterminalToIndex(char NonTerminal);
int GetStateFromActionString(char* action);

const char* ACTION[25][10] = {
        {"", "s4", "", "s2", "", "", "s5", "", "", ""},
        {"acc", "", "", "", "s6", "", "", "", "", ""},
        {"", "", "", "", "", "", "", "", "s7", ""},
        {"r3", "", "", "", "r3", "", "", "r3", "", ""},
        {"r4", "", "", "", "r4", "", "", "r4", "", ""},
        {"", "s4", "", "s2", "", "", "s5", "", "", ""},
        {"", "s4", "", "", "", "", "s5", "", "", ""},
        {"", "s15", "s16", "", "", "", "s13", "", "", ""},
        {"", "", "", "", "s6", "", "", "s17", "", ""},
        {"r2", "", "", "", "r2", "", "", "r2", "", ""},
        {"", "s4", "", "", "", "s19", "s5", "", "", ""},
        {"", "r7", "", "", "", "r7", "r7", "r7", "", ""},
        {"", "r8", "", "", "", "r8", "r8", "r8", "", ""},
        {"", "s15", "s16", "", "", "", "s13", "", "", ""},
        {"", "", "", "", "", "", "", "", "", "s21"},
        {"", "r11", "", "", "", "r11", "r11", "r11", "", "r11"},
        {"", "r12", "", "", "", "r12", "r12", "r12", "", "r12"},
        {"r5", "", "", "", "r5", "", "", "r5", "", ""},
        {"r1", "", "", "", "r1", "", "", "r1", "", ""},
        {"", "s15", "s16", "", "", "", "s13", "", "", ""},
        {"", "", "", "", "", "s19", "", "s23", "", ""},
        {"", "s15", "s16", "", "", "", "", "", "", ""},
        {"", "r6", "", "", "", "r6", "r6", "r6", "", ""},
        {"", "r9", "", "", "", "r9", "r9", "r9", "", ""},
        {"", "r10", "", "", "", "r10", "r10", "r10", "", ""}
};

const int GOTO[25][6] = {
        {1, 3, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {8, 3, -1, -1, -1, -1},
        {-1, 9, -1, -1, -1, -1},
        {-1, -1, 10, 11, 12, 14},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 18, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, 20, 11, 12, 14},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 22, 12, 14},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, 24},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1}
};

#endif SLR_H
