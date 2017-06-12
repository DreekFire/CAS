#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class node;

class token {
	public:
		token(std::string input);
		token();
		~token();
		void determineType();
		std::string tokenString;
		int tokenType = 0;
		enum type {
			Constant,
			Operator,
			LeftParen,
			RightParen,
			Variable,
			Expression,
            Function,
            Series
		};
		enum assoc {
			Left,
			Right,
		};

        static std::unordered_map<std::string, int> arity;
        static std::vector<node> functionList;
		bool compare(token t);
};