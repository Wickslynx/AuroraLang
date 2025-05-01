#include "parse.h"
#include <iostream>
#include <cstdlib>



void ctoken(TokenType expected) {
    if (currentToken.type == expected) {
        currentToken = getNextToken();
    } else {
        error("Unexpected token.");
    }
}

// handles the basic of the language, ints, chars....
AstNode* parsePrimary() {
    AstNode* node = new AstNode();
    node->left = nullptr;
    node->right = nullptr;

    if (currentToken.type == TOKEN_INT) {
        node->type     = AST_INT;
        node->value    = currentToken.value;
        node->toktype  = currentToken.type;
        ctoken(TOKEN_INT);
    } else if (currentToken.type == TOKEN_CHAR) {
        node->type      = AST_CHAR;
        node->character = currentToken.character;
        node->toktype   = currentToken.type;
        ctoken(TOKEN_CHAR);
    } else {
        aurerror(1, "Expected an integer or character literal.");
    }
    return node;
}

// check for binary experssions.
AstNode* parseExpression() {
    // so copilot said i was supposed to start with the primary.
    AstNode* left = parsePrimary();

    // is the next token a operator that we support?
    while (currentToken.type == TOKEN_PLUS ||
           currentToken.type == TOKEN_MINUS ||
           currentToken.type == TOKEN_DIVIDE) {

        AstNode* node = new AstNode();
        node->type = AST_BINARY_OP;
        node->left = left;
        node->right = nullptr;

        node->toktype = currentToken.type;

        
        ctoken(currentToken.type);

        // same as the one before.
        node->right = parsePrimary();

        // whole thing becomes the left side.
        left = node;
    }
    return left;
}

// free all mem.
void freeAst(AstNode* node) {
    if (!node)
        return;
    freeAst(node->left);
    freeAst(node->right);
    delete node;
}
