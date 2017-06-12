/*#pragma once
#include <iostream>
#include <vector>

template<class T> class stack {
public:
	std::vector<T> stackArray;
	int top;
	int m_size;
	int cap;
	stack(int size);

	~stack();

	void push(T token);

	T pop();

	void clear();

	T peek();

	int size();

	void pushList(T token[]);

	T* popList(int elements);

	enum full {
		Empty,
		Partial,
		Full
	};
};

#include "stack.h"

template<class T> stack<T>::stack(int size) {
	top = 0;
	m_size = size;
};

template<class T> stack<T>::~stack() {
};

template<class T> void stack<T>::push(T token) {
	try {
		if (cap == Empty) {
			cap = Partial;
		}
		if (cap != Full) {
			stackArray[top] = token;
			top++;
			if (top == m_size) {
				cap = Full;
			}
		}
		else {
			throw 1;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "stack underflow" << std::endl;
		}
		else {
			std::cout << "stack overflow" << std::endl;
		}
	}
};

template<class T> T stack<T>::pop() {
	try {
		if (cap == Full) {
			cap = Partial;
		}

		if (cap != Empty) {
			if (top == 1) {
				cap = Empty;
			}

			top--;
			return stackArray[top];
		}
		else {
			throw 0;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "stack underflow" << std::endl;
			throw;
		}
		else {
			std::cout << "stack overflow" << std::endl;
			throw;
		}
	}
};

template<class T> void stack<T>::clear() {
	top = 0;
};

template<class T> T stack<T>::peek() {
	try {
		if (cap != Empty) {
			return stackArray[top - 1];
		}
		else {
			throw 0;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "stack underflow" << std::endl;
		}
		else {
			std::cout << "stack overflow" << std::endl;
		}
		return '\0';
	}
};

template<class T> int stack<T>::size() {
	return m_size;
};

template<class T> void stack<T>::pushList(T token[]) {
	for (int i = 0; i < sizeof(token); i++) {
		push(token[i]);
	}
};

template<class T> T* stack<T>::popList(int elements) {
	std::vector<T> temp;
	for (int i = 0; i < elements; i++) {
		temp.push_back(pop());
	}
	return temp.data();
};*/