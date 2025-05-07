#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "parse.h"

extern std::vector<std::string> instructions;


void generate(AstNode* node);
void emit(std::string out);

#endif
