// ******************************************
// Author: UIC COMP3173 - Group 11
// Created Date: 2021/10/28
// File: lexer.h
// ******************************************

#ifndef RAA_LEXER_H
#define RAA_LEXER_H

/*
 * @Function: Reads the input string of relational expression and
 * returns the first token (token name) in the input or an error if meets
 *
 * @Input: string of relational expression
 * @return: first token name or error
 * */

char* next_token(char** p);

#endif //RAA_LEXER_H
