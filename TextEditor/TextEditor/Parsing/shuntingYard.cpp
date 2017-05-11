#include "shuntingYard.h"

std::map<std::string, int> precedence = { { std::string("+"), 0 },{ std::string("-"), 0 },{ std::string("*"), 1 },{ std::string("/"), 1 },{ std::string("^"), 2 } };

std::map<std::string, int> associativity = { { std::string("+"), 0 },{ std::string("-"), 0 },{ std::string("*"), 0 },{ std::string("/"), 0 },{ std::string("^"), 1 } };

std::vector<token> shuntingYardAlg(std::vector<token> tokenList) {
	int length = tokenList.size();
	std::queue<token> outputQueue;
	std::vector<token> operatorStack;
	for (int i = 0; i < length; i++)
	{
		token tkn = tokenList.at(i);
		if (tkn.tokenType == token::Number || tkn.tokenType == token::Variable || tkn.tokenType == token::Expression) {
			outputQueue.push(tkn);
		}
		else if (tkn.tokenType == token::Operator) {
			operatorStack.push_back(tkn);
		}
		else {
			if (tkn.tokenType == token::LeftParen || tkn.tokenType == token::RightParen) {
				while (!operatorStack.empty() && precedence[tkn.tokenString] + associativity[tkn.tokenString] <= precedence[operatorStack.back().tokenString]) {
					outputQueue.push(operatorStack.back());
					operatorStack.pop_back();
				}
				operatorStack.push_back(tkn);
			}
			else {
				if (tkn.tokenType == token::LeftParen) {
					operatorStack.push_back(tkn);
				}
				else if (tkn.tokenType == token::RightParen) {
					while (operatorStack.back().tokenType != token::LeftParen) {
						if (operatorStack.empty()) {
							//mismatched parens
							throw;
						}
						outputQueue.push(operatorStack.back());
						operatorStack.pop_back();
					}
					operatorStack.pop_back();
				}
			}
		}
	}
	if (!operatorStack.empty() && (operatorStack.back().tokenString == "(" || operatorStack.back().tokenString == ")")) {
		//mismatched parentheses
	}
	while (!operatorStack.empty()) {
		outputQueue.push(operatorStack.back());
		operatorStack.pop_back();
	}

	std::vector<token> result;

	while (!outputQueue.empty()) {
		result.push_back(outputQueue.front());
		outputQueue.pop();
	}

	return result;
}