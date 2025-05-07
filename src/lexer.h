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
  TOKEN_STRING,

  //Math :sob:
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_DIVIDE,
  TOKEN_ASSIGN,

  // Logic..
  TOKEN_EQUAL_TO,

  //Variables..
  TOKEN_GLOBAL,
  TOKEN_LOCAL,
  TOKEN_CONST,

  // Loops..
  TOKEN_WHILE,
  TOKEN_RETURN,

  // Comparison..
  TOKEN_IF, 
  TOKEN_ELSE,
  TOKEN_ELIF,
  // Symbols..
  TOKEN_RBRACE,
  TOKEN_LBRACE,
  
  // Other..
  TOKEN_SPACE,
  TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    union {
      int value;  // For ints.
      char character; // For chars.
      const char* strValue; // For strings.
    };
} Token;

typedef struct {
  FILE* ifile;
  size_t pos;
  char cchar;
} Lexer;



Token getToken(Lexer *lexer, const char c);
Token getNextToken(Lexer *lexer);
void lforwards(Lexer *lexer);
int lex(Lexer* lexer, const char* filename);



#endif //LEXER_H
