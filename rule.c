// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/12/26
// File: rule.c
// ******************************************

#include <string.h>
#include <stdlib.h>
#include "rule.h"

Rule *InitProductionRule() {
    Rule *rule;
    rule = (Rule*)malloc(sizeof(Rule) * 12);

    // rule 1: E -> sig_PT
    rule[0].left = 'E';
    strcpy_s(rule[0].right[0], strlen("sig") + 1, "sig");
    strcpy_s(rule[0].right[1], strlen("_") + 1, "_");
    strcpy_s(rule[0].right[2], strlen("P") + 1, "P");
    strcpy_s(rule[0].right[3], strlen("T") + 1, "T");
    rule[0].length = 4;

    // rule 2: E -> E join T
    rule[1].left = 'E';
    strcpy_s(rule[1].right[0], strlen("E") + 1, "E");
    strcpy_s(rule[1].right[1], strlen("join") + 1, "join");
    strcpy_s(rule[1].right[2], strlen("T") + 1, "T");
    rule[1].length = 3;

    // rule 3: E -> T
    rule[2].left ='E';
    strcpy_s(rule[2].right[0], strlen("T") + 1, "T");
    rule[2].length = 1;

    // rule 4: T -> id
    rule[3].left = 'T';
    strcpy_s(rule[3].right[0], strlen("id") + 1, "id");
    rule[3].length = 1;

    // rule 5: T -> (E)
    rule[4].left = 'T';
    strcpy_s(rule[4].right[0], strlen("(") + 1, "(");
    strcpy_s(rule[4].right[1], strlen("E") + 1, "E");
    strcpy_s(rule[4].right[2], strlen(")") + 1, ")");
    rule[4].length = 3;

    // rule 6: P -> P or Q
    rule[5].left = 'P';
    strcpy_s(rule[5].right[0], strlen("P") + 1, "P");
    strcpy_s(rule[5].right[1], strlen("or") + 1, "or");
    strcpy_s(rule[5].right[2], strlen("Q") + 1, "Q");
    rule[5].length = 3;

    // rule 7: P -> Q
    rule[6].left = 'P';
    strcpy_s(rule[6].right[0], strlen("Q") + 1, "Q");
    rule[6].length = 1;

    // rule 8: Q -> R
    rule[7].left = 'Q';
    strcpy_s(rule[7].right[0], strlen("R") + 1, "R");
    rule[7].length = 1;

    // rule 9: Q -> (P)
    rule[8].left = 'Q';
    strcpy_s(rule[8].right[0], strlen("(") + 1, "(");
    strcpy_s(rule[8].right[1], strlen("P") + 1, "P");
    strcpy_s(rule[8].right[2], strlen(")") + 1, ")");
    rule[8].length = 3;

    // rule 10: R -> N<N
    rule[9].left = 'R';
    strcpy_s(rule[9].right[0], strlen("N") + 1, "N");
    strcpy_s(rule[9].right[1], strlen("<") + 1, "<");
    strcpy_s(rule[9].right[2], strlen("N") + 1, "N");
    rule[9].length = 3;

    // rule 11: N -> id
    rule[10].left = 'N';
    strcpy_s(rule[10].right[0], strlen("id") + 1, "id");
    rule[10].length = 1;

    // rule 12: N -> text
    rule[11].left = 'N';
    strcpy_s(rule[11].right[0], strlen("text") + 1, "text");
    rule[11].length = 1;

    return rule;
}
