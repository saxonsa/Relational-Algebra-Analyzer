// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/10/28
// File: lexer.c
// ******************************************

#include <string.h>
#include <stdlib.h>

char ERROR_FLAG[] = "Lexical error.";

// DFA Transition table
// TRAP State: -1
const int transition_table[21][34] = {
        {10, 12, 6, 7, -1, 9, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, 20, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, 11, -1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {1, -1, -1, -1, -1, -1, 11, -1, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {-1, -1, -1, -1, -1, -1, 13, -1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
        {-1, 2, -1, -1, 14, -1, 13, -1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
        {-1, 2, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1} };


char* next_token(char** p)
{
    // save a copy version of input string for p
    const char* buf = *p;

    // Denote current state, the initial state of DFA is 0
    int current_state = 0;

    while (**p != '\n' && **p != 0 && current_state != -1 && (current_state == 0 || current_state > 9))
    {
        switch (**p)
        {
            case '\"':
            {
                current_state = transition_table[current_state][0];
                break;
            }
            case '\'':
            {
                current_state = transition_table[current_state][1];
                break;
            }
            case '(':
            {
                current_state = transition_table[current_state][2];
                break;
            }
            case ')':
            {
                current_state = transition_table[current_state][3];
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                current_state = transition_table[current_state][4];
                break;
            }
            case '<':
            {
                current_state = transition_table[current_state][5];
                break;
            }
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
            {
                current_state = transition_table[current_state][6];
                break;
            }
            case '_':
            {
                current_state = transition_table[current_state][7];
                break;
            }
            case 'a':
            {
                current_state = transition_table[current_state][8];
                break;
            }
            case 'b':
            {
                current_state = transition_table[current_state][9];
                break;
            }
            case 'c':
            {
                current_state = transition_table[current_state][10];
                break;
            }
            case 'd':
            {
                current_state = transition_table[current_state][11];
                break;
            }
            case 'e':
            {
                current_state = transition_table[current_state][12];
                break;
            }
            case 'f':
            {
                current_state = transition_table[current_state][13];
                break;
            }
            case 'g':
            {
                current_state = transition_table[current_state][14];
                break;
            }
            case 'h':
            {
                current_state = transition_table[current_state][15];
                break;
            }
            case 'i':
            {
                current_state = transition_table[current_state][16];
                break;
            }
            case 'j':
            {
                current_state = transition_table[current_state][17];
                break;
            }
            case 'k':
            {
                current_state = transition_table[current_state][18];
                break;
            }
            case 'l':
            {
                current_state = transition_table[current_state][19];
                break;
            }
            case 'm':
            {
                current_state = transition_table[current_state][20];
                break;
            }
            case 'n':
            {
                current_state = transition_table[current_state][21];
                break;
            }
            case 'o':
            {
                current_state = transition_table[current_state][22];
                break;
            }
            case 'p':
            {
                current_state = transition_table[current_state][23];
                break;
            }
            case 'q':
            {
                current_state = transition_table[current_state][24];
                break;
            }
            case 'r':
            {
                current_state = transition_table[current_state][25];
                break;
            }
            case 's':
            {
                current_state = transition_table[current_state][26];
                break;
            }
            case 't':
            {
                current_state = transition_table[current_state][27];
                break;
            }
            case 'u':
            {
                current_state = transition_table[current_state][28];
                break;
            }
            case 'v':
            {
                current_state = transition_table[current_state][29];
                break;
            }
            case 'w':
            {
                current_state = transition_table[current_state][30];
                break;
            }
            case 'x':
            {
                current_state = transition_table[current_state][31];
                break;
            }
            case 'y':
            {
                current_state = transition_table[current_state][32];
                break;
            }
            case 'z':
            {
                current_state = transition_table[current_state][33];
                break;
            }
            default:
            {
                // current input symbol does not exist in alphabet
                current_state = -1;
                break;
            }
        }
        // globally move the pointer to the next unprocessed symbol
        (*p)++;
    }

    if (current_state == -1 || current_state > 9)
    {
        return ERROR_FLAG;
    }
    else
    {
        // resolved token
        char* token = (char*)malloc(sizeof(char) * (*p - buf + 1));
        memset(token, '\0', sizeof(char) * (*p - buf + 1));
        for (int i = 0; i < (*p - buf); i++)
        {
            token[i] = buf[0 + i];
        }

        // Format returned result
        switch (current_state)
        {
            case 1:
            {
                // eliminate ""
                char* new_token = (char*)malloc(sizeof(char) * (*p - buf - 1));
                memset(new_token, '\0', sizeof(char) * (*p - buf - 1));
                for (int i = 0; i < (*p - buf - 2); i++)
                {
                    new_token[i] = token[1 + i];
                }

                // concat result identifier<token>
                char* result = (char*)calloc(strlen("identifier<>") + 1 + (*p - buf - 1), sizeof(char));
                strcpy_s(result, strlen("identifier<") + 1, "identifier<");
                strcat_s(result, strlen(new_token) + 1 + strlen(result), new_token);
                strcat_s(result, strlen(">") + 1 + strlen(result), ">");

                free(token);
                free(new_token);
                return result;
            }
            case 2:
            {
                // eliminate ''
                char* new_token = (char*)malloc(sizeof(char) * (*p - buf - 1));
                memset(new_token, '\0', sizeof(char) * (*p - buf - 1));
                for (int i = 0; i < (*p - buf - 2); i++)
                {
                    new_token[i] = token[1 + i];
                }

                // concat result text_literial<token>
                char* result = (char*)calloc(strlen("text_literial<>") + 1 + (*p - buf - 1), sizeof(char));
                strcpy_s(result, strlen("text_literial<") + 1, "text_literial<");
                strcat_s(result, strlen(new_token) + 1 + strlen(result), new_token);
                strcat_s(result, strlen(">") + 1 + strlen(result), ">");

                free(token);
                free(new_token);
                return result;
            }
            default:
            {
                return token;
            }
        }
    }
}