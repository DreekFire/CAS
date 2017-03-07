#include "node.h"

void node::buildList(node proto, std::vector<node> &currentList) {
	if (match(proto)) {
		if (proto.m_data.tokenType == token::Expression) {
			int position = std::stoi(proto.m_data.tokenString.substr(1, std::string::npos)) - 1;
			if (currentList.empty() || !currentList.at(position).compare(*this)) {
				currentList.insert(currentList.begin() + position, this);
			}
		}
		if (left && proto.left) {
			left->buildList(proto.left, currentList);
		}
		if (right && proto.right) {
			left->buildList(proto.right, currentList);
		}
	}
}

bool node::match(node target) {
	if (target.m_data.tokenType == token::Expression) {
		return true;
	}
	if ((!!left != !!target.left) || (!!right != !!target.right) || (!!left && !left->match(*target.left)) || (!!right && !right->match(*target.right))) {
		return false;
	}
	return true;
}

void node::fillProto(node &proto, std::vector<node> expressList) {
	if (proto.left) {
		fillProto(*proto.left, expressList);
	}
	if (proto.right) {
		fillProto(*proto.right, expressList);
	}
	if (proto.m_data.tokenType == token::Expression) {
		proto = expressList.at(std::stoi(proto.m_data.tokenString.substr(1, std::string::npos)) - 1);
	}
}

bool node::compare(node targetRoot) {
	if ((!!left != !!targetRoot.left) || (!!right != !!targetRoot.right)) {
		return false;
	}
	bool leftEquals = true, rightEquals = true;
	if (left) {
		leftEquals = left->compare(targetRoot.left);
	}
	if (right) {
		rightEquals = right->compare(targetRoot.right);
	}
	bool nodeEquals = m_data.tokenString.compare(targetRoot.m_data.tokenString) == 0;
	return leftEquals && rightEquals && nodeEquals;
}

void node::print() {
	if (isLeaf()) {
		std::cout << m_data.tokenString;
	}
	else {
		std::cout << "(";
		left->print();
		std::cout << m_data.tokenString;
		right->print();
		std::cout << ")";
	}
}

node::node() {
	m_data = token();
	left = NULL;
	right = NULL;
}

node::node(token data) {
	m_data = data;
	left = NULL;
	right = NULL;
}

node::node(node *source) {
	m_data = source->m_data;
	left = source->left;
	right = source->right;
}

node::~node() {
	left = NULL;
	right = NULL;
}

bool node::evaluateAble() {
	try {
		std::stod(m_data.tokenString);
		return true;
	}
	catch (std::invalid_argument e) {
		return false;
	}
}

void node::remove(node* &rootNode) {
	if (rootNode) {
		if (rootNode->left) {
			remove(rootNode->left);
		}
		rootNode->left = NULL;
		if (rootNode->right) {
			remove(rootNode->right);
		}
		rootNode->right = NULL;
		delete rootNode;
		rootNode = NULL;
	}
}

node node::add(node a, node b) {
	std::string res = "+";
	node output;
	if (a.evaluateAble() && b.evaluateAble()) {
		res = std::to_string(std::stod(a.m_data.tokenString) + std::stod(b.m_data.tokenString));
		token data(res);
		output = node(data);
	}
	else {
		token data(res);
		output = node(data);
		output.left = &a;
		output.right = &b;
	}
	return output;
}

node node::subtract(node a, node b) {
	std::string res = "-";
	node output;
	if (a.evaluateAble() && b.evaluateAble()) {
		res = std::to_string(std::stod(a.m_data.tokenString) - std::stod(b.m_data.tokenString));
		token data(res);
		output = node(data);
	}
	else {
		token data(res);
		output = node(data);
		output.left = &a;
		output.right = &b;
	}
	return output;
}

node node::multiply(node a, node b) {
	std::string res = "*";
	node output;
	if (a.evaluateAble() && b.evaluateAble()) {
		res = std::to_string(std::stod(a.m_data.tokenString) * std::stod(b.m_data.tokenString));
		token data(res);
		output = node(data);
	}
	else {
		token data(res);
		output = node(data);
		output.left = &a;
		output.right = &b;
	}
	return output;
}

node node::divide(node a, node b) {
	std::string res = "/";
	node output;
	if (a.evaluateAble() && b.evaluateAble()) {
		res = std::to_string(std::stod(a.m_data.tokenString) / std::stod(b.m_data.tokenString));
		token data(res);
		output = node(data);
	}
	else {
		token data(res);
		output = node(data);
		output.left = &a;
		output.right = &b;
	}
	return output;
}

node node::power(node a, node b) {
	std::string res = "^";
	node output;
	if (a.evaluateAble() && b.evaluateAble()) {
		std::string res = std::to_string(pow(std::stod(a.m_data.tokenString), std::stod(b.m_data.tokenString)));
		token data(res);
		node output(data);
	}
	else {
		token data(res);
		node output(data);
		output.left = &a;
		output.right = &b;
	}
	return output;
}

bool node::isLeaf() {
	return !(left && right);
}

node node::evaluate() {
	if (m_data.tokenType == token::type::Operator) {
		if (m_data.tokenString.compare("+") == 0) {
			node a = left->evaluate();
			node b = right->evaluate();
			return node::add(a, b);
		}
		if (m_data.tokenString.compare("-") == 0) {
			node a = left->evaluate();
			node b = right->evaluate();
			return node::subtract(a, b);
		}
		if (m_data.tokenString.compare("*") == 0) {
			node a = left->evaluate();
			node b = right->evaluate();
			return node::multiply(a, b);
		}
		if (m_data.tokenString.compare("/") == 0) {
			node a = left->evaluate();
			node b = right->evaluate();
			return node::divide(a, b);
		}
		if (m_data.tokenString.compare("^") == 0) {
			node a = left->evaluate();
			node b = right->evaluate();
			return node::power(a, b);
		}
		throw;
	}
	return *this;
}

node node::copy() {
	node out;
	out.m_data = m_data;
	if (left) {
		node* leftNode = new node(left->copy());
		out.left = leftNode;
	}
	if (right) {
		node* rightNode = new node(right->copy());
		out.right = rightNode;
	}
	return out;
}