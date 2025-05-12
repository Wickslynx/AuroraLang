// This will be the main file.
#include <iostream>
#include <cstring>
#include "parse.h"
#include "generator.h"
#include "lexer.h"
#include "semantic.h"

/* Example command: 
aur hello.aur hello
*/


int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "--version") == 0) {
        std::cout << "(V) Aur  1.0.0 (BETA) \n  (L) MIT License  \n Build: Stable-release. \n Support: https://github.com/Wickslynx/AuroraLang/issues \n";
        return 0;
    }
    
    
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.aur> <output_file>" << std::endl;
        return 1;
    }

    char* filename = argv[1];  // First argument is always filename..
    char* outfile = argv[2];   // Second argument is always out file..

    std::cout << "Compiling " << filename << " to " << outfile << "... \n";

    // lex it.
    Lexer aurlexer;
    lex(&aurlexer, filename);

    // parse and build ast
    Token currentToken = getNextToken(&aurlexer);
    AstNode* root;

    printf("------------------------------\n");
    printf("          PARSER - DEBUG      \n");
    printf("------------------------------\n\n");

    printf("(DEBUG) 43 - aur.cpp [Before loop]\n");

    if (currentToken.type == TOKEN_EOF) {
        std::cerr << "ERROR The file is empty.\n\n";
    }

    while (true) {
        printf("(DEBUG) 45 - aur.cpp [Entered loop]\n");
        root = parseStatement(&aurlexer);
        // run semantic 
        semanticAnalysis(root);

        // generate asm code.
        generate(root);

        //Update tok.
        currentToken = getNextToken(&aurlexer);
    }
    
    
    
    emit(outfile);

    // cleanup
    freeAst(root);

    std::cout << "Compilation finished successfully.\n";

    return 0;
}

