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
                std::cerr << "Error: Binary operator requires integer operands. \n Ex: 1 - 2" << std::endl;
                std::exit(EXIT_FAILURE);
            }
            node->type = AST_INT;
            break;
        default:
            std::cerr << "Error: Unknown AST node type.... Please report this to our issue tracker at github.com/Wickslynx/AuroraLang/issues" << std::endl;
            std::exit(EXIT_FAILURE);
    }
}
