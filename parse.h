#ifndef PARSE_H
#define PARSE_H

#include "lexer.h"

enum AstType {
  AST_INT,
  AST_CHAR,
  AST_BINARY_OP
};

struct AstNode {
  AstType type;
  int value;
  char character;
  
  TokenType toktype;
  
  AstNode* left;
  AstNode* right;
};

// parse smth.
AstNode* parseExpression();

// free all memory used.
void freeAst(AstNode* node);

#endif // PARSE_H
