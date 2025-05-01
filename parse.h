#ifndef PARSE_H
#define PARSE_H

/*NOTE: This will be the only file that is handling the input file to avoid confusion. */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "error.h"

/*
Hmm... So how will this return?? 
It will return EOFS in the token struct, pretty easy actually.

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum { 

  // Types..
  TOKEN_INT,
  TOKEN_CHAR,

  //Math :sob:
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_DIVIDE,

  // Other..
  TOKEN_EOF 
} TokenType;

typedef struct {
    TokenType type;
    int value;  // For ints.
    char character; // For chars.
} Token;

typdef struct {
  Token tokens;
} Lexer;

// you want to be able to consume arbitrary characters and sometimes skip certain characters. So you probably want a Lexer struct which hold your string and consumes parts off the front of it etc


Token getToken(const char c);


int lexer(const char* filename);


#endif //PARSE_H
