#pragma once
#include "tree.h"
#include <algorithm>

std::vector<token> tokenize(std::string input);
void print(std::vector<token> tokenList);