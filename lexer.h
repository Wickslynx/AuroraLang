#ifndef LEXER_H
#define LEXER_H

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
    union {
      int value;  // For ints.
      char character; // For chars.
    }
} Token;

typdef struct {
  const char* input;
  size_t pos;
  char cchar;
} Lexer;



Token getToken(const char c);


int lexer(Lexer* lexer, const char* filename);


#endif //LEXER_H
