#include "node.h"
#include "Rewriting/rule.h"

/*node::node(std::vector<token> build) {
    std::vector<node> nodeStack;
    int size = (int)build.size();
    for (int i = 0; i < size; i++) {
        if (build.at(i).tokenType == token::Constant || build.at(i).tokenType == token::Variable || build.at(i).tokenType == token::Expression) {
            node* out;
            out = new node(build.at(i));
            nodeStack.push_back(out);
        }
        else if (build.at(i).tokenType == token::Operator || build.at(i).tokenType == token::Function) {
            node* out;
            out = new node(build.at(i));
            int ary = token::arity.at(build.at(i).tokenString);
            out->children.resize(ary);
            for (int j = 1; j <= ary; j++) {
                if (i == size - 1) {
                    children.resize(ary);
                    children.at(ary - j) = new node(nodeStack.back());
                }
                else {
                    out->children.at(ary - j) = new node(nodeStack.back());
                }
                nodeStack.pop_back();
            }
            nodeStack.push_back(out);
        }
    }
    m_data = nodeStack.back().m_data;
    nodeStack.pop_back();
}*/
node::node(std::vector<token> build) {
    std::vector<node> nodeStack;
    for (int i = 0; i < (int)build.size(); i++) {
        if (build.at(i).tokenType == token::Constant || build.at(i).tokenType == token::Variable || build.at(i).tokenType == token::Expression) {
            nodeStack.push_back(build.at(i));
        }
        else if (build.at(i).tokenType == token::type::Operator) {
            //currently only does binary operators, because debugging
            node* out = new node(build.at(i));
            node* b = new node(nodeStack.back());
            nodeStack.pop_back();
            node* a = new node(nodeStack.back());
            nodeStack.pop_back();
            out->children.push_back(a);
            out->children.push_back(b);
            nodeStack.push_back(*out);
        }
    }
    m_data = nodeStack.back().m_data;
    node* a;
    for (int i = 0; i < nodeStack.back().children.size(); i++) {
        a = new node(nodeStack.back().children.at(i));
        children.push_back(a);
    }
    nodeStack.pop_back();
}

node::node() {
	m_data = token();
    children.clear();
}

node::node(token data) {
	m_data = data;
    children.clear();
}

node::node(node*& source) {
    m_data = source->m_data;
    for (int i = 0; i < source->children.size(); i++) {
        children.push_back(source->children.at(i));
    }
}

node::~node() {
    for_each(children.begin(), children.end(), clearChildren);
    children.clear();
}

void node::buildList(node proto, std::vector<node> &currentList) {
	if (proto.m_data.tokenType == token::Expression) {
		int position = std::stoi(proto.m_data.tokenString.substr(1, std::string::npos)) - 1;
		if (currentList.empty() || !currentList.at(position).compare(*this)) {
			currentList.insert(currentList.begin() + position, *this);
		}
	}
    for (int i = 0; i < (int)children.size(); i++) {
        if (children.at(i) && proto.children.at(i)) {
            children.at(i)->buildList(proto.children.at(i), currentList);
        }
    }
}

bool node::matchProto(node target, std::vector<std::vector<constraint>> constraints) {
	if (target.m_data.tokenType == token::Expression) {
		return true;
	}
    if (m_data.tokenString != target.m_data.tokenString) {
        if ((m_data.tokenString.compare("+") != 0 || target.m_data.tokenString.compare("-") != 0) || (m_data.tokenString.compare("-") != 0 || target.m_data.tokenString.compare("+") != 0)) {
            return false;
        }
        if (m_data.tokenString.compare("-") == 0) {
            m_data.tokenString = "+";
            for_each(children.begin(), children.end(), [=](node a) {
                a = operate(std::vector<node>{node(token("-1")), a}, multiply);
            });
        }
        if (m_data.tokenString.compare("+") == 0) {
            m_data.tokenString = "-";
            for_each(children.begin(), children.end(), [=](node a) {
                a = operate(std::vector<node>{node(token("-1")), a}, multiply);
            });
        }
    }
    if ([=]() { for (int i = 0; i < children.size(); i++) { if ((!!children.at(i) != !!target.children.at(i)) || (!!children.at(i) && !children.at(i)->matchProto(*target.children.at(i), constraints))) return false; } return true; }()) {
		return false;
	}
	return true;
}

void node::fillProto(node &proto, std::vector<node> expressList) {
    for (int i = 0; i < proto.children.size(); i++) {
		fillProto(*proto.children.at(i), expressList);
	}
	if (proto.m_data.tokenType == token::Expression) {
		proto = expressList.at(std::stoi(proto.m_data.tokenString.substr(1, std::string::npos)) - 1);
	}
}

bool compareFlag = true;
bool node::compare(node targetRoot) {
    if (compareFlag) {
        for (int i = 0; i < (int)children.size(); i++) {
            if ((!!children.at(i) != !!targetRoot.children.at(i))) {
                return false;
            }
        }
        for (int i = 0; i < (int)children.size(); i++) {
            if (!children.at(i)->compare(targetRoot.children.at(i))) {
                compareFlag = false;
                return false;
            }
        }
        return m_data.tokenString.compare(targetRoot.m_data.tokenString) == 0;
    }
    return false;
}

std::string node::toString() const {
	if (isLeaf()) {
		return m_data.tokenString;
	}
	else if (m_data.tokenType == token::Function) {
		std::cout << m_data.tokenString;
		std::cout << "(";
        for (int i = 0; i < (int)children.size(); i++) {
            std::cout << children.at(i)->m_data.tokenString + ", " << std::endl;
        }
		std::cout << ")";
	}
    else {
        return "(" + children.at(0)->toString() + m_data.tokenString + children.at(1)->toString() + ")";
    }
}

/*std::vector<node> node::find(node target) {
    std::vector<node> results;
    if (m_data.compare(target.m_data)) {

    }
}*/

//I know it should be evaluatable but w/e
bool node::evaluateAble() const {
    if (m_data.tokenType == token::Constant) {
        return true;
    }
    else {
        for (node* i : children) {
            if (!i->evaluateAble()) {
                return false;
            }
        }
        return true;
    }
}

void node::clearChildren(node* &rootNode) {
	if (rootNode) {
        for (int i = rootNode->children.size(); i > 0; i--)
        {
            clearChildren(rootNode->children.back());
		    rootNode->children.pop_back();
        }
        rootNode->children.clear();
	}
}

double add(std::vector<double> operands) {
    double sum = 0;
    for (int i = 0; i < (int)operands.size(); i++) {
        sum += operands.at(i);
    }
    return sum;
}

double subtract(std::vector<double> operands) {
    double sum = operands.at(0);
    for (int i = 1; i < (int)operands.size(); i++) {
        sum -= operands.at(i);
    }
    return sum;
}

double multiply(std::vector<double> operands) {
    double product = 1;
    for (int i = 0; i < (int)operands.size(); i++) {
        product *= operands.at(i);
    }
    return product;
}

double divide(std::vector<double> operands) {
    double quotient = operands.at(0);
    for (int i = 1; i < (int)operands.size(); i++) {
        quotient /= operands.at(i);
    }
    return quotient;
}

double power(std::vector<double> operands) {
    if ((int)operands.size() == 2) {
        return std::pow(operands.at(0), operands.at(1));
    }
    else {
        return std::pow(operands.at(0), power(std::vector<double>(operands.begin() + 1, operands.end())));
    }
}

std::unordered_map<node::operation, std::string> opMapRev = { { add, "+" }, { subtract, "-" }, { multiply, "*" }, { divide, "/" }, { power, "^" } };
std::unordered_map<std::string, node::operation> opMap = { { "+", add }, { "-", subtract }, { "*", multiply }, { "/", divide }, { "^", power } };

node& node::operate(std::vector<node> &operands, operation op) {
    if ([=](){ for (int i = 0; i < (int)operands.size(); i++) {
            if (!operands.at(i).evaluateAble()) {
                return false;
            }
        }
        return true; }()) {
        std::vector<double> ops(operands.size());
        for (int i = 0; i < (int)operands.size(); i++) {
            ops.at(i) = std::stod(operands.at(i).m_data.tokenString);
        }
        node* res = new node(token(std::to_string(op(ops))));
        return *res;
    }
    else {
        token tok(opMapRev[op]);
        node* res = new node(tok);
        for (int i = 0; i < (int)operands.size(); i++) {
            res->children.push_back(&operands.at(i).copy());
        }
        return *res;
    }
}

/*node node::add(node a, node b) {
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
}*/

bool node::isLeaf() const {
	return children.size() == 0;
}

node node::evaluate() {
    if (m_data.tokenType == token::Constant) {
        return *this;
    }
	else if (m_data.tokenType == token::Operator) {
        std::vector<node> evalChild;
        for (int i = 0; i < children.size(); i++) {
            evalChild.push_back(children.at(i)->evaluate());
        }
        return operate(evalChild, opMap[m_data.tokenString]);
	}
	return *this;
}

double node::evaluate(double x) {
    node duplicate = copy();
    duplicate.replace(token("x"), token(std::to_string(x)));
    duplicate.evaluate();
    return stod(duplicate.m_data.tokenString);
}

node node::copy() {
    node* out;
    out = new node(m_data);
    node* a;
    for (int i = 0; i < children.size(); i++) {
        a = new node(children.at(i));
        out->children.push_back(a);
    }
	return *out;
}

void node::replace(token source, token dest) {
    if (m_data.compare(source)) {
        m_data = dest;
    }
    for (int i = 0; i < (int)children.size(); i++) {
        children.at(i)->replace(source, dest);
    }
}

ruleSet expandRules;
void node::expand() {
    for (rule i : expandRules.rules) {
        rule::apply(*this, i);
    }
}

/*int node::getHighestDeg() {

}*/