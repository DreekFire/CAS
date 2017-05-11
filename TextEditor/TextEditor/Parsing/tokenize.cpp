#include "tokenize.h"

std::vector<token> tokenize(std::string input) {
	std::vector<token> result;
	input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	std::string builder = "";
	int currentType = token(std::string(1, input.at(0))).tokenType;
	for (int i = 0; i < (int)input.size(); i++) {
		token dataToken(std::string(1, input.at(i)));
		if (input.at(i) == '$' || (node(dataToken).evaluateAble() && currentType == token::Expression)) {
			if (currentType != token::Expression) {
				token builtToken(builder);
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Expression;
			}
			else {
				builder += input.at(i);
			}
		}
		else if (dataToken.tokenType == token::Operator) {
			if (input.at(i) == '-' && currentType == token::Operator) {
				token builtToken(builder);
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Number;
			}
			else {
				token builtToken(builder);
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Operator;
			}
		}
		else if (node(dataToken).evaluateAble()) {
			if (currentType != token::Number) {
				token builtToken(builder);
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Number;
			}
			else {
				builder += input.at(i);
			}
		}
		else {
			if (currentType != token::Variable) {
				token builtToken(builder);
				result.push_back(builtToken);
				builder.clear();
				builder += input.at(i);
				currentType = token::Variable;
			}
			else {
				builder += input.at(i);
			}
		}
	}
	token builtToken(builder);
	result.push_back(builtToken);
	return result;
}

void print(std::vector<token> tokenList) {
	for (int i = 0; i < (int)tokenList.size(); i++) {
		std::cout << tokenList.at(i).tokenString << std::endl;
	}
}