#ifndef PARSE_H
#define PARSE_H

#include "lexer.h"
#include <string>

enum AstType {
  AST_INT,
  AST_CHAR,
  AST_BLOCK,
  AST_IF,
  AST_VARIABLE,
  AST_BINARY_OP
};

struct AstNode {
  AstType type;
  int value;
  char character;
  std::string varName; 
  AstNode* condition;;
  AstNode* body;
  AstNode* elseBody;
  AstNode* expression;
  AstNode* statements;
  
  TokenType toktype;
  
  AstNode* left;
  AstNode* right;
};


// parse smth.
AstNode* parseExpression(Lexer* lexer);

// free all memory used.
void freeAst(AstNode* node);

#endif // PARSE_H
