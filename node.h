#pragma once
#include <vector>
#include "token.h"

class node {
public:
	node(token data);
	node(node *source);
	node();
	~node();
	token m_data;
	static void remove(node* &rootNode);
	static void fillProto(node &proto, std::vector<node> expressList);
	static node add(node a, node b);
	static node subtract(node a, node b);
	static node multiply(node a, node b);
	static node divide(node a, node b);
	static node power(node a, node b);
	bool evaluateAble();
	bool isLeaf();
	void print();
	void buildList(node proto, std::vector<node> &currentList);
	bool match(node target);
	bool compare(node targetRoot);
	void insert(int i, token data);
	node evaluate();
	node copy();
	node* left = NULL;
	node* right = NULL;
};