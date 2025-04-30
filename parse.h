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
  TOKEN_PLUS,

  // Other..
  TOKEN_EOF 
} TokenType;

typedef struct {
    TokenType type;
    int value;  // For ints.
    char character; // For chars.
} Token;



Token getToken(const char c) {
    Token token;
      
    if (isdigit(c)) {
          token.type = TOKEN_INT;
          token.value = c - '0'; 
          return token;
    } else if (isalpha(c)) {
      token.type = TOKEN_CHAR;
      token.character = c;
      return token;
    } else if (c == '+') {
          token.type = TOKEN_PLUS;
          return token;
    }
    

    token.type = TOKEN_EOF;
    return token;
}


int lexer(const char* filename) {
  char* input;
  
  if (!filename) {
    error(2, "No file given to lexer.");
  }

  FILE* ifile = fopen(filename, "r");
  
  if (ifile == NULL) {
    error(1, "error opening file: %s", filename);
  }

  while ((c = fgetc(ifile)) != EOF) {
    getToken(c);
  }
  
}


#endif
