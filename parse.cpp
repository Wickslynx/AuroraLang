#include "parse.h"

Token getToken(const char c) {
    Token token;
    switch (c) {
        case '0' ... '9':
            token.type=TOKEN_INT;
            token.value = c - '0';
            break;
        case 'a' .... 'z':
            token.type = TOKEN_CHAR;
            token.character = c;
            break;
        case '+':
            token.type = TOKEN_PLUS;
            break;
        case '-':
            token.type = TOKEN_MINUS;
            break;
        case '/':
            token.type = TOKEN_DIVIDE;
            break;
        
        default:
            token.type = TOKEN_EOF;
            break;
    }
    

    return token;
}


int lexer(const char* filename) {
  if (!filename) {
    error(2, "No file given to lexer.");
  }

  FILE* ifile = fopen(filename, "r");
  
  if (ifile == NULL) {
    error(1, "error opening file...";
  }
    
  char c;
    
  while ((c = fgetc(ifile)) != EOF) {
    getToken(c);
  }

  fclose(ifile);
}
