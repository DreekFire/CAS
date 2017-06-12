/*#pragma once
#include <iostream>
#include <vector>

template <class T> class queue {
	public:
		std::vector<T> queueArray;
		int front;
		int rear;
		int m_size;
		int cap;
		queue(int size);

		~queue();

		void enqueue(T token);

		T dequeue();

		void clear();

		T peek();

		int size();

		void enqueueList(T token[]);

		T* dequeueList(int elements);

		enum full {
			Empty,
			Partial,
			Full
		};
};

template<class T> queue<T>::queue(int size) {
	front = 0;
	rear = 0;
	m_size = size;
};

template<class T> queue<T>::~queue() {
};

template<class T> void queue<T>::enqueue(const T token) {
	try {
		if (cap == Empty) {
			cap = Partial;
		}
		if (cap != Full) {
			queueArray.at(rear) = token;
			if (rear == m_size - 1) {
				rear = 0;
			}
			else {
				rear++;
			}
			if (front == rear) {
				cap = Full;
			}
		}
		else {
			throw 1;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "no element to dequeue" << std::endl;
		}
		else {
			std::cout << "queue overflow" << std::endl;
		}
	}
};

template<class T> T queue<T>::dequeue() {
	try {
		if (cap == Full) {
			cap = Partial;
		}
		if (cap != Empty) {
			T res = queueArray[front];
			if (front == m_size - 1) {
				front = 0;
			}
			else {
				front++;
			}
			if (front == rear) {
				cap = Empty;
			}
			return res;
		}
		else {
			throw 0;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "queue underflow" << std::endl;
		}
		else {
			std::cout << "queue overflow" << std::endl;
		}
		return '\0';
	}
};

template<class T> void queue<T>::clear() {
	front = 0;
	rear = 0;
};

template<class T> T queue<T>::peek() {
	try {
		if (cap != Empty) {
			return queueArray[front];
		}
		else {
			throw 0;
		}
	}
	catch (int e) {
		if (e == 0) {
			std::cout << "queue underflow" << std::endl;
		}
		else {
			std::cout << "queue overflow" << std::endl;
		}
		return '\0';
	}
};

template<class T> int queue<T>::size() {
	return m_size;
};

template<class T> void queue<T>::enqueueList(T token[]) {
	for (int i = 0; i < sizeof(token); i++) {
		enqueue(token[i]);
	}
};

template<class T> T* queue<T>::dequeueList(int elements) {
	std::vector<T> temp;
	for (int i = 0; i < elements; i++) {
		temp.push_back(dequeue());
	}
	return temp.data();
};*/