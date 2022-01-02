// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/10/28
// File: Analyzer.c
// Description: Used to run main function
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
        fputs("---------------\n", out);

        int error = 0; // mark whether we meet error (both lexical and syntax) or not

        fgets(buf, MAXSIZE, in); // read one line from "in.txt"

        // add an artificial $ before line break (aka. '\n')
        buf[strlen(buf) - 1] = '$';
        buf[strlen(buf)] = '\n';

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
        printf("initial\n");
        printf("<%d %s >\n", currentState, buf);

        while (*p != '\n' && *p != '\0') { // stop when meet line break or file ends
            char* token = "";
            if (*p == '$' && *(p + 1) == '\n') { // valid artificial $
                token = "$";
                p++;
            }
            else {
                token = next_token(&p);
            }

            if (strcmp(token, ERROR_FLAG) == 0) {
                error = LEXICAL_ERROR;
                break;
            }
6
            // get the index for looking up SLR action table
            currentState = stack.pairs[stack.top].state;
            int index = ConvertTokenToIndex(token);

            // look up SLR action table and assign the operation into act variable
            char* act = (char*)malloc(sizeof(char) * 4);
            strcpy_s(act, strlen(ACTION[currentState][index]) + 1, ACTION[currentState][index]);

            if (strncmp(act, "s", 1) == 0) { // shift
                // push pair (token, state) to StateStack
                Push(&stack, token, GetStateFromActionString(act));
                continue;
            }
            else if (strncmp(act, "r", 1) == 0) { // reduce

                while (strncmp(act, "r", 1) == 0) { // continue to reduce if we meet 'r' again
                    // stack.pop "rule.length" times
                    Rule rule = rules[GetStateFromActionString(act) - 1];
                    for (int i = 0; i < rule.length; i++) {
                        Pop(&stack, NULL);
                    }

                    // currentState = GOTO[stack.top->state, convertNonterminalToindex(rule.left)]
                    currentState = GOTO[stack.pairs[stack.top].state][ConvertNonterminalToIndex(rule.left)];

                    // push pair(rule.left, currentState])
                    char left[2] = { 0 };
                    left[0] = rule.left;
                    Push(&stack, left, currentState);

                    strcpy_s(act, strlen(ACTION[currentState][index]) + 1, ACTION[currentState][index]);
                }

                if (strncmp(act, "s", 1) == 0) { // shift
                    Push(&stack, token, GetStateFromActionString(act));
                }

                else { // accept

                }
            }
            else {
                // acc: never come here
            }

            free(act);

            //
            //            if (strcmp(token, ERROR_FLAG) != 0) {
            //                if (strlen(result) == 0) {
            //                    strcpy_s(result, strlen(token) + 1, token);
            //                }
            //                else {
            //                    // if not the first token, add an extra space before the next read token
            //                    strcat_s(result, strlen(result) + 1 + strlen(" "), " ");
            //
            //                    // concat the token name into the whole transformed result
            //                    strcat_s(result, strlen(result) + 1 + strlen(token), token);
            //                }
            //            }
            //            else {
            //                // error
            //                error = 1;
            //                break;
            //            }
        }

        //        if (!error) {
        //            // output the transformed token name for the whole expression to "out.txt"
        //            fputs(result, out);
        //        }
        //        else {
        //            // if meet lexical error, just output the lexical error for the whole expression
        //            fputs(ERROR_FLAG, out);
        //        }

        // output "------------" to out.txt after finishing each line except the last line
        if (*p != '\0') {
            fputs("---------------\n", out);
        }
    }

    // close "in.txt" and "out.txt"
    fclose(in);
    fclose(out);
    return 0;
}