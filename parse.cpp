#include "parse.h"

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
    error(1, "error opening file...";
  }

  while ((c = fgetc(ifile)) != EOF) {
    getToken(c);
  }
  
}
