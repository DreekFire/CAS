#include "tree.h"
#include "Rewriting/rule.h"

tree::tree(std::vector<token> build) {
	std::vector<node> nodeStack;
	for (int i = 0; i < (int) build.size(); i++) {
		if (build.at(i).tokenType == token::Constant || build.at(i).tokenType == token::Variable || build.at(i).tokenType == token::Expression) {
			nodeStack.push_back(node(build.at(i)));
		}
		else if (build.at(i).tokenType == token::type::Operator) {
			if (build.at(i).tokenString.compare("+") == 0) {
				node *b = new node(nodeStack.back());
				nodeStack.pop_back();
				node *a = new node(nodeStack.back());
				nodeStack.pop_back();
				node out(token("+"));
				out.left = a;
				out.right = b;
				nodeStack.push_back(out);
			}
			else if (build.at(i).tokenString.compare("-") == 0) {
				node *b = new node(nodeStack.back());
				nodeStack.pop_back();
				node *a = new node(nodeStack.back());
				nodeStack.pop_back();
				node out(token("-"));
				out.left = a;
				out.right = b;
				nodeStack.push_back(out);
			}
			else if (build.at(i).tokenString.compare("*") == 0) {
				node *b = new node(nodeStack.back());
				nodeStack.pop_back();
				node *a = new node(nodeStack.back());
				nodeStack.pop_back();
				node out(token("*"));
				out.left = a;
				out.right = b;
				nodeStack.push_back(out);
			}
			else if (build.at(i).tokenString.compare("/") == 0) {
				node *b = new node(nodeStack.back());
				nodeStack.pop_back();
				node *a = new node(nodeStack.back());
				nodeStack.pop_back();
				node out(token("/"));
				out.left = a;
				out.right = b;
				nodeStack.push_back(out);
			}
		}
	}
	root = nodeStack.back();
	nodeStack.pop_back();
}

tree::tree(node rootNode) {
	root = rootNode;
}

tree::~tree() {
	node::remove(root.left);
	node::remove(root.right);
	root.left = NULL;
	root.right = NULL;
}

void tree::simplify() {

}

void node::insert(int i, token data) {
	node* child = new node(data);
	if (i == 0)
		left = child;
	if (i == 1)
		right = child;
}

double tree::evaluateAt(double x) {
    tree duplicate = tree(root.copy());
    duplicate.root.replace(token("x"), token(std::to_string(x)));
    duplicate.root.evaluate();
    return stod(duplicate.root.m_data.tokenString);
}