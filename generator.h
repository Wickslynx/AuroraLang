#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include "parse.h"

std::vector<std::string> instructions;


void generate(AstNode* node);
void emit(std::string out);

#endif
