#include "generator.h"
#include "parse.h"



void generate(AstNode* node) {
    if (!node) return;

    switch (node->type) {
        case AST_INT:
            instructions.push_back("mov rax, " + std::to_string(node->value));
            break;
            
        case AST_BINARY_OP:
            generate(node->left);
            generate(node->right);
                
            switch (node->toktype) {
                case TOKEN_PLUS:
                    instructions.push_back("add rax, rbx");
                    break;
                case TOKEN_MINUS:
                    instructions.push_back("sub rax, rbx");
                    break;
                case TOKEN_DIVIDE:
                    instructions.push_back("div rbx");
                    break;
            }
            break;
            
        default:
            std::cerr << "Error: Unsupported AST node type." << std::endl;
            std::exit(EXIT_FAILURE);
    }
}

void emit(std::string out) { 
    std::ofstream file("temp-aurolang-asm.asm");
    if (!file.is_open()) {
      std::cerr << "Error: Could not create file." << std::endl;
      return;
    }
  
    for (const auto& instr : instructions) {
         file << instr << std::endl;
    }

    std::ostringstream cmd = "nasm -f elf-64 temp-aurolang-asm.asm -o  {}" << out; 
    
    system(cmd.c_str());
    system("rm temp-aurolang-asm.asm");
    
    file.close();
}


