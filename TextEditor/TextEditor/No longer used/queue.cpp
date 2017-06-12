/*#include "queue.h"

queue::queue<T>(int size) {
	queueArray = new T[size];
	front = 0;
	rear = 0;
	m_size = size;
}

queue::~queue() {
	delete[] queueArray;
}

void queue::enqueue(char token) {
	try {
		if (cap == Empty) {
			cap = Partial;
		}
		if (cap != Full) {
			queueArray[rear] = token;
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
}

char queue::dequeue() {
	try {
		if (cap == Full) {
			cap = Partial;
		}
		if (cap != Empty) {
			char res = queueArray[front];
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
}

void queue::clear() {
	front = 0;
	rear = 0;
}

char queue::peek() {
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
}

int queue::size() {
	return m_size;
}

void queue::enqueueList(char token[]) {
	for (int i = 0; i < sizeof(token); i++) {
		enqueue(token[i]);
	}
}

const char* queue::dequeueList(int elements) {
	std::string temp;
	for (int i = 0; i < elements; i++) {
		temp += dequeue();
	}
	const char* result = temp.c_str();
	return temp.c_str();
}*/