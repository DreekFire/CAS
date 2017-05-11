#pragma once
#include <iostream>
#include <map>
#include <string>

//multiple include error
//extern std::map<std::string, std::string> variableMap;
//extern std::map<std::string, std::string> functionMap;

class token {
	public:
		token(std::string input);
		token();
		~token();
		void determineType();
		std::string tokenString;
		int tokenType = 0;
		enum type {
			Number,
			Operator,
			LeftParen,
			RightParen,
			Variable,
			Expression,
		};
		enum associativity {
			Left,
			Right,
		};
		/*enum arity {

		};*/
		bool compare(token t);
};