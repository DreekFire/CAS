#pragma once
#include <vector>
#include "node.h"

class rule;

class tree {
	public:
		tree(std::vector<token> build);
		tree(node rootNode);
		~tree();
		node root;
		void simplify();
		void remove(int i);
		tree copy();
};