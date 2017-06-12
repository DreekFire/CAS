#pragma once
#include "node.h"
#include <algorithm>

std::vector<token> tokenize(std::string input);
void print(std::vector<token> tokenList);