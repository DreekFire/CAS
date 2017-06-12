#include "shuntingYard.h"

struct cmpLess {
    bool operator()(const token lhs, const token rhs) const {
        return lhs.tokenString < rhs.tokenString;
    }
};

std::map<token, int, cmpLess> precedence = { { token("+"), 0 }, { token("-"), 0 }, { token("*"), 1 }, { token("/"), 1 },{ token("^"), 2 } };

std::map<token, int, cmpLess> associativity = { { token("+"), token::Left }, { token("-"), token::Left }, { token("*"), token::Left }, { token("/"), token::Left },{ token("^"), token::Right } };

std::vector<token> shuntingYardAlg(std::vector<token> tokenList) {
	int length = (int)tokenList.size();
	std::queue<token> outputQueue;
	std::vector<token> operatorStack;
	while (!tokenList.empty())
	{
		token tkn = tokenList.back();
		if (tkn.tokenType == token::Constant || tkn.tokenType == token::Variable || tkn.tokenType == token::Expression) {
			outputQueue.push(tkn);
		}
        if (tkn.tokenType == token::Operator) {
            while (!operatorStack.empty() && (precedence[tkn] < precedence[operatorStack.back()] || (precedence[tkn] == precedence[operatorStack.back()] && associativity[tkn] == token::Left))) {
                outputQueue.push(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.push_back(tkn);
        }
		if (tkn.tokenType == token::LeftParen) {
			operatorStack.push_back(tkn);
		}
		if (tkn.tokenType == token::RightParen) {
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
        tokenList.pop_back();
	}
	if (!operatorStack.empty() && (operatorStack.back().tokenString.compare("(") == 0 || operatorStack.back().tokenString.compare(")") == 0)) {
		//mismatched parentheses
        throw;
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