#pragma once
#include "Parsing/tree.h"
#include "Parsing/tokenize.h"
#include "Parsing/shuntingYard.h"

class rule {
	public:
		rule(std::string str_a, std::string str_b);
		rule(tree match, tree express);
		~rule();
		tree from;
		tree replace;
		node apply(tree express);
};

class ruleSet {
	public:
		ruleSet();
		ruleSet(std::vector<rule> ruleList);
		~ruleSet();
		std::vector<rule> rules;
		void reduce(tree& express);
		void addRule(rule newRule);
};