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
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.aur> <output_file>" << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        std::cout << "(V) Aur  1.0.0 (BETA) \n  (L) MIT License  \n Build: Stable-release. \n Support: https://github.com/Wickslynx/AuroraLang/issues \n";
        return 0;
    }

    char* filename = argv[1];  // First argument is always filename..
    char* outfile = argv[2];   // Second argument is always out file..

    std::cout << "Compiling " << filename << " to " << outfile << "... \n";

    // Step 1: Lex it.
    Lexer aurlexer;
    lex(&aurlexer, filename);

    // Step 2: parse and build ast
    currentToken = getNextToken();
    AstNode* root = parseExpression();

    // Step 3: run semantic 
    semanticAnalysis(root);

    // Step 4: generate asm code.
    
    generate(root);
    emit(outfile);

    // Step 5: cleanup
    freeAst(root);

    std::cout << "Compilation finished successfully.\n";

    return 0;
}

