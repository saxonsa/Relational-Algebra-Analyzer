// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/10/28
// File: Analyzer.c
// Description: Used to run main function
// ******************************************

#define _CRT_SECURE_NO_WARNINGS // lazy to use "_s" for every function -_-

#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "SLR.h"

#define MAXSIZE 1024 // max size for one line

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

    // processing the lexical analysis
    while (!feof(in)) {
        int error = 0;

        // read one line from "in.txt"
        fgets(buf, MAXSIZE, in);

        // init a pointer points the first unprocessed symbol of current line
        // initially, points to the first symbol of current line
        char* p = buf;

        char result[MAXSIZE] = { "" };

        while (*p != '\n' && *p != '\0') { // stop when meet line ends or file ends
            char* token = next_token(&p);
            if (strcmp(token, ERROR_FLAG) != 0) {
                if (strlen(result) == 0) {
                    strcpy_s(result, strlen(token) + 1, token);
                }
                else {
                    // if not the first token, add an extra space before the next read token
                    strcat_s(result, strlen(result) + 1 + strlen(" "), " ");

                    // concat the token name into the whole transformed result
                    strcat_s(result, strlen(result) + 1 + strlen(token), token);
                }

            }
            else {
                // error
                error = 1;
                break;
            }
        }

        if (!error) {
            // output the transformed token name for the whole expression to "out.txt"
            fputs(result, out);
        }
        else {
            // if meet lexical error, just output the lexical error for the whole expression
            fputs(ERROR_FLAG, out);
        }

        // output a '\n' to out.txt after each line except the last line
        if (*p != '\0') {
            fputs("\n", out);
        }
    }

    // close "in.txt" and "out.txt"
    fclose(in);
    fclose(out);
    return 0;
}