#include "token.h"

std::unordered_map<std::string, int> token::arity = { { "+", 2 }, { "-", 2 }, { "*", 2 }, { "/", 2 }, { "^", 2 } };

token::token() {
	tokenString = "";
}

void token::determineType() {
    if (tokenString == "sum" || tokenString == "product") {
        tokenType = Series;
    }
	else if (tokenString.at(0) == '$') {
		tokenType = Expression;
	}
	else if (tokenString == "(") {
		tokenType = LeftParen;
	}
	else if (tokenString == ")") {
		tokenType = RightParen;
	}
	else if (tokenString.find_first_of("+-*/^") != std::string::npos && (int)tokenString.size() == 1) {
		tokenType = Operator;
	}
	else if (bool isConstant = [](std::string in) {
		try { stod(in); }
		catch (...) {
			return false;
	    }
	    return true;
	} (tokenString)) {
		tokenType = Constant;
	}
	else if (tokenString.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos)
	{
		tokenType = Variable;
	}
}

token::token(std::string input) {
	tokenString = input;
	determineType();
}

token::~token() {

}

bool token::compare(token t) {
	if (tokenString == t.tokenString) {
		return true;
	}
	return false;
}