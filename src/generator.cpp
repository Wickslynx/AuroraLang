#include "generator.h"
#include "parse.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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
            instructions.push_back("push rax");  //  save left

            generate(node->right);
            instructions.push_back("mov rbx, rax");  // mv right

            instructions.push_back("pop rax");  // restore left

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
            // declare var in bss
            bss_section.push_back(node->varName + " resq 1");
            instructions.push_back("mov [" + node->varName + "], rax");
            break;

        case AST_VARIABLE_VALUE:
            instructions.push_back("mov rax, [" + node->varName + "]");
            break;

        case AST_IF:
            generate(node->condition);
            instructions.push_back("cmp rax, 0");
            instructions.push_back("je ELSE_" + node->label);

            generate(node->body);
            instructions.push_back("jmp END_IF_" + node->label);

            instructions.push_back("ELSE_" + node->label + ":");
            if (node->elseBody) {
                generate(node->elseBody);
            }

            instructions.push_back("END_IF_" + node->label + ":");
            break;

        case AST_FUNC:
            instructions.push_back(node->label + ":");
            generate(node-body);
            instructions.push_back("ret"); // return  
        case AST_FUNC_CALL:
            for (auto &arg : node->params) {
                generate(arg);
                instructions.push_back("push rax"); // pass args
            }

            instructions.push_back("call" + node->label);
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

    // exit program
    file << "    mov rax, 60\n";   // syscall exit
    file << "    xor rdi, rdi\n";  // exit(0)
    file << "    syscall\n";

    file.close();

    std::string uresponse;
    
    std::ostringstream cmd; 
    cmd << "nasm -f elf64 temp-aurolang-asm.asm -o temp-aurolang.o && ld temp-aurolang.o -o " << out; 

    for (char c : out) {
        if (!isalnum(c) || c == '"' || c == '-') {
            std::cout << "Suspicious input detected... Are you sure you want to run this? If you want to override this, please type \"override\" \n Command you are about to run: " << out << "\n:";
            std::cin >> uresponse;
            if (uresponse != "override") {
                exit(0);
            }  else {
                break;
            }
        }
    }
    
    system(cmd.str().c_str());
    system("rm temp-aurolang-asm.asm temp-aurolang.o");
}
