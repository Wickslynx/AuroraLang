// parse.cpp
#include "parse.h"
#include <iostream>
#include <cstdlib>

/* Parser for AuroraLang:
- Wicks (2025).

All rights reserved.

The lexer is defined in "lexer.h", so is the getNextToken function.
*/


Token currentToken;
extern Token getNextToken(Lexer *lexer);

void ctoken(Lexer *lexer, TokenType expected) {
    if (currentToken.type == expected) {
        currentToken = getNextToken(lexer);
    } else {
        std::cerr << "Unexpected token." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// handles the basics of the language, ints, chars....
AstNode* parsePrimary(Lexer *lexer) {
    AstNode* node = new AstNode();
    node->left = nullptr;
    node->right = nullptr;
    
    switch (currentToken.type) {
        case TOKEN_INT:
            node->type = AST_INT;
            node->value = currentToken.value;
            node->toktype = currentToken.type;
            ctoken(lexer, TOKEN_INT);
            break;
        case TOKEN_CHAR:
            node->type = AST_CHAR;
            node->character = currentToken.character;
            node->toktype = currentToken.type;
            ctoken(lexer, TOKEN_CHAR);
            break;

        case TOKEN_STRING:
            node->type = AST_STRING;
            node->strValue = currentToken.strValue;
            node->toktype = currenToken.type;
            ctoken(lexer, TOKEN_STRING);
            break;
            
        default:
            std::cerr << "Expected an integer or character literal." << std::endl;
            std::exit(EXIT_FAILURE);
            break;
    }
    
    return node;
}

// check for binary expressions.
AstNode* parseExpression(Lexer *lexer) {
    // always start with the primary expression.
    AstNode* left = parsePrimary(lexer);

    // when the current token is a supported operator, build an operation node.
    while (currentToken.type == TOKEN_PLUS ||
           currentToken.type == TOKEN_MINUS ||
           currentToken.type == TOKEN_DIVIDE) {

        AstNode* node = new AstNode();
        node->type = AST_BINARY_OP;
        node->left = left;
        node->right = nullptr;

        // save the operator in a node.
        node->toktype = currentToken.type;
        ctoken(lexer, currentToken.type);

        // parse the next right node.
        node->right = parsePrimary(lexer);

        // the node is moved to left.
        left = node;
    }
    return left;
}

AstNode* parseLocal(Lexer* lexer) {
    AstNode* node = new AstNode();
    node->type = AST_VARIABLE;

    // consume local
    ctoken(lexer, TOKEN_LOCAL);

    // need var name...
    if (currentToken.type != TOKEN_IDENTIFIER) {
        std::cerr << "Error: Expected variable name." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    node->varName = currentToken.identifier;
    ctoken(lexer, TOKEN_IDENTIFIER);

    // check for assignment (=)
    if (currentToken.type == TOKEN_ASSIGN) {
        ctoken(lexer, TOKEN_ASSIGN);
        node->expression = parseExpression(lexer);
    }

    return node;
}

AstNode* parseGlobal(Lexer* lexer) {
    AstNode* node = new AstNode();
    node->type = AST_VARIABLE;

    // consume local
    ctoken(lexer, TOKEN_GLOBAL);

    // need var name...
    if (currentToken.type != TOKEN_IDENTIFIER) {
        std::cerr << "Error: Expected variable name." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    node->varName = currentToken.identifier;
    ctoken(lexer, TOKEN_IDENTIFIER);

    // check for assignment (=)
    if (currentToken.type == TOKEN_ASSIGN) {
        ctoken(lexer, TOKEN_ASSIGN);
        node->expression = parseExpression(lexer);
    }

    return node;
}

AstNode* parseStatement(Lexer* lexer) {
    switch (currentToken.type) {
        case TOKEN_IF:
            return parseIf(lexer);
        case TOKEN_LOCAL:
            return parseLocal(lexer);
        default:
            return parseExpression(lexer);
    }
}




AstNode* parseBlock(Lexer* lexer) {
    AstNode* node = new AstNode();
    node->type = AST_BLOCK;

    ctoken(lexer, TOKEN_LBRACE); // {

    while (currentToken.type != TOKEN_RBRACE) {
        node->statements.push_back(parseStatement(lexer));
    }

    ctoken(lexer, TOKEN_RBRACE); // }

    return node;
}

std::vector<AstNode*> parseParams(Lexer *lexer) {
    std::vector<AstNode*> params;
    // Empty?
    if (currentToken.type == TOKEN_RPARAN) {
        return params;
    }

    while (true) {
        if (currentToken.type != TOKEN_IDENTIFIER) {
            std::cerr << "Error: Expected parameter name." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        AstNode* param = new AstNode();
        param->type = AST_PARAM;
        param->varName = currentToken.identifier;
        ctoken(lexer, TOKEN_IDENTIFIER);
        params.push_back(param);

        // When we reach a comma, just parse it and get the next identifier.
        if (currentToken.type == TOKEN_COMMA) {
            ctoken(lexer, TOKEN_COMMA);
        } else {
            break;
        }
    }

    return params;
}


AstNode* parseFunc(Lexer *lexer) {
    AstNode* node = new AstNode();
    node->type = AST_FUNC;

    ctoken(lexer, TOKEN_FUNC);

    if (currentToken.type != TOKEN_IDENTIFIER) {
        std::cerr << "Error: Expected function name." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    node->label = currentToken.identifier;
    ctoken(lexer, TOKEN_IDENTIFIER);

    ctoken(lexer, TOKEN_LPARAN);
    node->params = parseParams(lexer);
    ctoken(lexer, TOKEN_RPARAN);

    node->body = parseBlock(lexer);
    
}

AstNode* parseIf(Lexer* lexer) {
    AstNode* node = new AstNode();
    node->type = AST_IF;

    ctoken(lexer, TOKEN_IF);
    
    // condition expression, ex if (x == y)
    node->condition = parseExpression(lexer);
    node->body = parseBlock(lexer); // This is actually reusable, it will just parse all code that's inside {}

     if (currentToken.type == TOKEN_ELSE) { // Parse else, not really needed, standalone if statements are allowed.
        ctoken(lexer, TOKEN_ELSE);
        node->elseBody = parseBlock(lexer);
    }

    return node;
    
}

AstNode* parseFuncCall(Lexer* lexer) {
    AstNode* node = new AstNode();
    node->type = AST_FUNC_CALL;
    node->label = currentToken.identifier;

    ctoken(lexer, TOKEN_IDENTIFIER);
    ctoken(lexer, TOKEN_LPARAN); // (

    node->params = parseParams(lexer);

    ctoken(lexer, TOKEN_RPARAN);
    return node;
}

// free the AST.
void freeAst(AstNode* node) {
    if (!node)
        return;
    freeAst(node->left);
    freeAst(node->right);
    delete node;
}
