#include "parse.h"
#include "lexer.h"
#include <iostream>


std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_INT:
            return "int";
        case TOKEN_CHAR:
            return "char";
        case TOKEN_PLUS:
            return "+";
        case TOKEN_MINUS:
            return "-";
        case TOKEN_DIVIDE:
            return "/";
        case TOKEN_EOF:
            return "TOKEN_EOF";
        default:
            return "UNKNOWN_TOKEN";
    }
}


void semanticAnalysis(AstNode* node) {
    if (!node)
        return;
    
    switch (node->type) {
        case AST_INT:
            // Ints are always valid, pretty easy.
            break;
        case AST_CHAR:
            // rn idc about it but what if a int
            break;
        case AST_BINARY_OP:
            semanticAnalysis(node->left);
            semanticAnalysis(node->right);
            
            
            
            if (node->left->type != AST_INT || node->right->type != AST_INT) {  // Analyse the nodes on the side, are they valid? Both has to be int for now, floats aint implemented.
                std::cerr << "Error: Operator '" << tokenTypeToString(node->toktype)<< "' requires integer operands. Received: " << node->left->type << " and " << node->right->type << std::endl;

                std::exit(EXIT_FAILURE);
            }
            node->type = AST_INT;
            break;
        default:
            std::cerr << "Error: Unknown AST node type.... Please report this to our issue tracker at github.com/Wickslynx/AuroraLang/issues" << std::endl;
            std::exit(EXIT_FAILURE);
    }
}
