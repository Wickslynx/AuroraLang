#ifndef PARSE_H
#define PARSE_H

#include "lexer.h"
#include <string>
#include <vector>

enum AstType {
  AST_INT,
  AST_CHAR,
  AST_BLOCK,
  AST_IF,
  AST_VARIABLE,
  AST_VARIABLE_VALUE,
  AST_BINARY_OP
};

struct AstNode {
  AstType type;
  int value;
  char character;
  std::string varName;
  std::string label;
  AstNode* condition;;
  AstNode* body;
  AstNode* elseBody;
  AstNode* expression;
  std::vector<AstNode*> statements;
  
  TokenType toktype;
  
  AstNode* left;
  AstNode* right;
};


// parse smth.
AstNode* parseExpression(Lexer* lexer);

// All underlying methods..
AstNode* parseIf(Lexer* lexer);
AstNode* parseBlock(Lexer* lexer);
AstNode* parseStatement(Lexer* lexer);
AstNode* parseLocal(Lexer* lexer);

// free all memory used.
void freeAst(AstNode* node);

#endif // PARSE_H
