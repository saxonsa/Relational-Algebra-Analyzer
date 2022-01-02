// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/10/28
// Last Modified Date: 2022/01/03
// File: Analyzer.c
// ******************************************

#define _CRT_SECURE_NO_WARNINGS // lazy to use "_s" for every function -_-

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "SLR.h"
#include "rule.h"
#include "state.h"

#define MAXSIZE 1024 // max size for one line

enum error {
    LEXICAL_ERROR = 1,
    SYNTAX_ERROR = 2
};

int main() {
    char ERROR_FLAG[] = "Lexical error.";
    FILE* in, * out;

    char buf[MAXSIZE] = { 0 };

    // read stream from "in.txt"
    errno_t err = fopen_s(&in, "../in.txt", "r");
    if (err != 0) {
        printf("error with code: %d, %s\n", err, strerror(err));
        return 0;
    }

    // init an empty file "out.ext", used to write the result
    err = fopen_s(&out, "../out.txt", "w");
    if (err != 0) {
        printf("error with code: %d, %s\n", err, strerror(err));
    }

    // initialize production rule
    Rule* rules = InitProductionRule();

    while (!feof(in)) {
        // read one line from "in.txt"
        if (fgets(buf, MAXSIZE, in) == NULL) {
            break;
        };

        fputs("---------------\n", out);

        int error = 0; // mark whether we meet error (both lexical and syntax) or not

        // add an artificial $ before line break (aka. '\n')
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '$';
        }
        else {
            buf[strlen(buf)] = '$';
        }


        // init a pointer used for lexical analysis points the first unprocessed symbol of current line
        // initially, points to the first symbol of current line
        char* p = buf;

        //        char result[MAXSIZE] = { "" };

        // initialize current state, start with 0
        int currentState = 0;

        // create a stack for state
        StateStack stack;
        CreateStack(&stack, 20);
        Push(&stack, NULL, 0);

        // print the initial case
        fputs("initial\n", out);
        fprintf(out, "\t<%d %s >\n", currentState, p);

        while (*p) { // stop when meet line break or file ends
            int a = 0;
            int* moveTimes = &a;

            char* token;
            if (*p == '$') { // valid artificial $
                token = "$";
            }
            else {
                token = next_token(&p, moveTimes);
                p = p - *moveTimes;
            }

            if (strcmp(token, ERROR_FLAG) == 0) {
                error = LEXICAL_ERROR;
                break;
            }

            // get the index for looking up SLR action table
            currentState = stack.pairs[stack.top].state;
            int index = ConvertTokenToIndex(token);

            // look up SLR action table and assign the operation into act variable
            char* act = (char*)malloc(sizeof(char) * 4);
            strcpy_s(act, strlen(ACTION[currentState][index]) + 1, ACTION[currentState][index]);
            if (!(*act)) {
                error = SYNTAX_ERROR;
                break;
            }

            if (strncmp(act, "s", 1) == 0) { // shift
                fputs("shift\n", out);
                p += *moveTimes;

                // push pair (token, state) to StateStack
                Push(&stack, token, GetStateFromActionString(act));

                // print shift result
                fputs("\t<0", out);
                for (int i = 1; i <= stack.top; i++) {
                    fprintf(out, " %s%d", stack.pairs[i].token, stack.pairs[i].state);
                }
                fprintf(out, " %s >\n", p);

                continue;
            }
            else if (strncmp(act, "r", 1) == 0) { // reduce

                while (strncmp(act, "r", 1) == 0) { // continue to reduce if we meet 'r' again


                    // stack.pop "rule.length" times
                    Rule rule = rules[GetStateFromActionString(act) - 1];

                    // print "reduce<Rule>\n"
                    fprintf(out, "reduce %c->", rule.left);
                    for (int i = 0; i < rule.length; i++) {
                        fprintf(out, "%s", rule.right[i]);
                    }
                    fputs("\n", out);

                    for (int j = 0; j < rule.length; j++) {
                        Pop(&stack, NULL);
                    }

                    // currentState = GOTO[stack.top->state, convertNonterminalToindex(rule.left)]
                    currentState = GOTO[stack.pairs[stack.top].state][ConvertNonterminalToIndex(rule.left)];
                    if (currentState == -1) {
                        fputs("syntax error\n", out);
                    }

                    // push pair(rule.left, currentState])
                    char* left = (char*)malloc(sizeof(char) * 2);
                    left[0] = rule.left;
                    left[1] = '\0';
                    Push(&stack, left, currentState);

                    // print shift result
                    fputs("\t<0", out);
                    for (int i = 1; i <= stack.top; i++) {
                        fprintf(out, " %s%d", stack.pairs[i].token, stack.pairs[i].state);
                    }
                    fprintf(out, " %s >\n", p);

                    strcpy_s(act, strlen(ACTION[currentState][index]) + 1, ACTION[currentState][index]);

                    if (!(*act)) {
                        error = SYNTAX_ERROR;
                        break;
                    }

                }

                if (strncmp(act, "s", 1) == 0) { // shift
                    fputs("shift\n", out);
                    p += *moveTimes;

                    Push(&stack, token, GetStateFromActionString(act));

                    // print shift result
                    fputs("\t<0", out);
                    for (int i = 1; i <= stack.top; i++) {
                        fprintf(out, " %s%d", stack.pairs[i].token, stack.pairs[i].state);
                    }
                    fprintf(out, " %s >\n", p);
                }

                else { // accept
                    fputs("accept\n", out);
                }
            }
            else {
                // acc: never come here
            }

            free(act);

            // when finishing print $ related stack info, global move p to the next position
            if (strncmp(token, "$", 1) == 0) {
                p++;
            }
        }

        // print error if encounter
        switch (error) {
            case LEXICAL_ERROR: {
                fputs("lexical error\n", out);
                break;
            }
            case SYNTAX_ERROR: {
                fputs("syntax error\n", out);
            }
            default: {
                // 0
            }
        }

        memset(buf, 0, sizeof(buf));
    }

    // close "in.txt" and "out.txt"
    fclose(in);
    fclose(out);
    return 0;
}