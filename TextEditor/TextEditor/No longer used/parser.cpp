#include "parser.h"

/*std::string parseRPN(std::vector<token> input) {
	stack<token> outputStack = stack<token>(input.size());
	for (int i = 0; i < input.size(); i++) {
		token temp = input.at(i);
		if (temp.tokenType == Number) {
			outputStack.push(input.at(i));
		}
		else if (temp.tokenString == "+") {
			token b = outputStack.pop();
			token a = outputStack.pop();
			if (variableMap.find(a.tokenString) != variableMap.end() && variableMap.find(b.tokenString) != variableMap.end()) {
				outputStack.push(token(a.value() + b.value()));
			}
			else {
				outputStack.push(token("a + b"));
			}
		}
		else if (temp == "-") {
			int b = (int)outputStack.pop() - '0';
			int a = (int)outputStack.pop() - '0';
			outputStack.push(a - b + '0');
		}
		else if (temp == '*') {
			int b = (int)outputStack.pop() - '0';
			int a = (int)outputStack.pop() - '0';
			outputStack.push(a * b + '0');
		}
		else if (temp == '/') {
			int b = (int)outputStack.pop() - '0';
			int a = (int)outputStack.pop() - '0';
			outputStack.push(a / b + '0');
		}
	}

	std::string result;

	result = outputStack.pop();

	return result;
}*/