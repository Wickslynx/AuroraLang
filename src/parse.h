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
  std::string varName; 
  std::string condition;
  std::string body;
  
  TokenType toktype;
  
  AstNode* left;
  AstNode* right;
};

extern Lexer globalLexer;

// parse smth.
AstNode* parseExpression(Lexer* lexer);

// free all memory used.
void freeAst(AstNode* node);

#endif // PARSE_H
