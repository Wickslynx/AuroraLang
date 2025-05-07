#include "generator.h"
#include "parse.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> instructions;
std::vector<std::string> data_section;
std::vector<std::string> bss_section;

void generate(AstNode* node) {
    if (!node) return;

    switch (node->type) {
        case AST_INT:
            instructions.push_back("mov rax, " + std::to_string(node->value));
            break;
            
        case AST_BINARY_OP:
            generate(node->left);
            instructions.push_back("push rax");  // Save left operand

            generate(node->right);
            instructions.push_back("mov rbx, rax");  // Move right operand

            instructions.push_back("pop rax");  // Restore left operand

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

        case AST_VARIABLE:
            // Declare variable in the `.bss` section
            bss_section.push_back(node->varName + " resq 1");
            instructions.push_back("mov [" + node->varName + "], rax");
            break;

        case AST_VARIABLE_REFERENCE:
            instructions.push_back("mov rax, [" + node->varName + "]");
            break;

        case AST_IF:
            generate(node->condition);
            instructions.push_back("cmp rax, 0");
            instructions.push_back("je ELSE_" + std::to_string(node->label));

            generate(node->body);
            instructions.push_back("jmp END_IF_" + std::to_string(node->label));

            instructions.push_back("ELSE_" + std::to_string(node->label) + ":");
            if (node->elseBody) {
                generate(node->elseBody);
            }

            instructions.push_back("END_IF_" + std::to_string(node->label) + ":");
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
  
    // Section headers
    file << "section .data\n";
    for (const auto& data : data_section) {
        file << "    " << data << std::endl;
    }

    file << "section .bss\n";
    for (const auto& bss : bss_section) {
        file << "    " << bss << std::endl;
    }

    file << "section .text\n";
    file << "global _start\n";
    file << "_start:\n";

    for (const auto& instr : instructions) {
        file << "    " << instr << std::endl;
    }

    // Exit program
    file << "    mov rax, 60\n";   // syscall exit
    file << "    xor rdi, rdi\n";  // exit(0)
    file << "    syscall\n";

    file.close();

    std::ostringstream cmd; 
    cmd << "nasm -f elf64 temp-aurolang-asm.asm -o temp-aurolang.o && ld temp-aurolang.o -o " << out; 
    
    system(cmd.str().c_str());
    system("rm temp-aurolang-asm.asm temp-aurolang.o");
}
