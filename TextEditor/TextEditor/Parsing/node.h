#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "Parsing/token.h"

class rule;
class ruleSet;

double add(std::vector<double> operands);

double subtract(std::vector<double> operands);

double multiply(std::vector<double> operands);

double divide(std::vector<double> operands);

double power(std::vector<double> operands);

class node {
public:
    typedef bool (*constraint)(node express);
    typedef double (*operation)(std::vector<double> operands);
    node(std::vector<token> build);
	node(token data);
	node(node*& source);
	node();
	~node();
	token m_data;
    std::vector<node*> children;
	
    static void clearChildren(node* &rootNode);
	static void fillProto(node &proto, std::vector<node> expressList);
	bool evaluateAble() const;
	bool isLeaf() const;
	std::string toString() const;
	void buildList(node proto, std::vector<node> &currentList);
	bool matchProto(node target, std::vector<std::vector<constraint>> constraints);
	bool compare(node targetRoot);
	void insert(int i, token data);
    void replace(token source, token dest);
	node copy();
    std::vector<node> find(node target);

    //math
    static node& operate(std::vector<node> &operands, operation op);
	node evaluate();
    double evaluate(double x);
    void expand();
    int getHighestDeg();
};