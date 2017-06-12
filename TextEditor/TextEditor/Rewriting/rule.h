#pragma once
#include "Parsing/node.h"
#include "Parsing/tokenize.h"
#include "Parsing/shuntingYard.h"

class node;

class rule {
	public:
		rule(std::string str_a, std::string str_b);
		rule(node match, node express);
		~rule();
		node from;
		node replace;
		static node apply(node express, rule app);
};

class ruleSet {
	public:
		ruleSet();
		ruleSet(std::vector<rule> ruleList);
		~ruleSet();
		std::vector<rule> rules;
		void reduce(node& express);
		void addRule(rule newRule);
};