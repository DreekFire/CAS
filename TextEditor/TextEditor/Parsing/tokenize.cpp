#include "tokenize.h"

std::vector<token> tokenize(std::string input) {
	std::vector<token> result;
	input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	std::string builder = "";
    token dataToken;
    int currentType;
	for (int i = 0; i < input.size(); i++) {
		dataToken = token(std::string(1, input.at(i)));
        currentType = dataToken.tokenType;
		if (input.at(i) == '$' || (dataToken.tokenType == token::Constant && currentType == token::Expression)) {
			if (currentType != token::Expression) {
				token builtToken(builder);
                builtToken.tokenType = currentType;
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
                builtToken.tokenType = currentType;
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Constant;
			}
			else {
				token builtToken(builder);
                builtToken.tokenType = currentType;
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Operator;
			}
		}
		else if (dataToken.tokenType == token::Constant) {
			if (currentType != token::Constant) {
				token builtToken(builder);
                builtToken.tokenType = currentType;
				result.push_back(builtToken);
				builder.clear();
				builder.append(1, input.at(i));
				currentType = token::Constant;
			}
			else {
				builder += input.at(i);
			}
		}
        else if (dataToken.tokenType == token::Variable) {
            if (currentType != token::Variable) {
                token builtToken(builder);
                builtToken.tokenType = currentType;
                result.push_back(builtToken);
                builder.clear();
                builder += input.at(i);
                currentType = token::Variable;
            }
            else {
                builder += input.at(i);
            }
        }
        else if (dataToken.tokenType == token::LeftParen) {
            if (currentType == token::LeftParen) {
                token builtToken(builder);
                builtToken.tokenType = token::LeftParen;
                result.push_back(builtToken);
                builder.clear();
                builder.append(1, input.at(i));
            }
            else if (currentType == token::Variable) {
                token builtToken(builder);
                builtToken.tokenType = token::Function;
                result.push_back(builtToken);
                builder.clear();
                builder.append(1, input.at(i));
                currentType = token::LeftParen;
            }
        }
        else if (dataToken.tokenType == token::RightParen) {
            token builtToken(builder);
            builtToken.tokenType = currentType;
            result.push_back(builtToken);
            builder.clear();
            builder.append(1, input.at(i));
        }
		else {
            std::cout << "could not tokenize: possible invalid character" << std::endl;
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