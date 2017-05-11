#include "token.h"

token::token() {
	tokenString = "";
}

void token::determineType() {
	if (tokenString.at(0) == '$') {
		tokenType = Expression;
	}
	else if (tokenString.find('[') != std::string::npos) {
		tokenType = Number;
	}
	else if (tokenString == "(") {
		tokenType = LeftParen;
	}
	else if (tokenString == ")") {
		tokenType = RightParen;
	}
	else if (tokenString.find_first_of("+-*/^") != std::string::npos) {
		tokenType = Operator;
	}
	else if (bool isNumber = [](std::string in) {
		try { stod(in); }
		catch (...) {
			return false;
		}
		return true;
	} (tokenString)) {
		tokenType = Number;
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