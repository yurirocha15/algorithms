#pragma once
#include <iostream>

namespace no_stl {
	
//Simple element used for stack and queue implementation
template<class T>
struct elem {
	T val;
	elem<T> *next;
	elem<T> *before;
	elem() {
		val = 0;
		next = nullptr;
		before = nullptr;
	}
	elem(T v, elem<T> *n, elem<T> *b) {
		val = v;
		next = n;
		before = b;
	}
};

//Double-Ended Queue implementation without using stl functions
template <class T>
struct deque {
	elem<T> *head;
	elem<T> *tail;
	deque() {
		head = nullptr;
		tail = nullptr;
	}
	deque(int* v, int size) {
		head = nullptr;
		tail = nullptr;
		for(auto i = 0; i < size; ++i) {
			push(v[i]);
		}
	}
	bool empty() {
		return head == nullptr;
	}
	void push(T val) {
		if(empty()) {
			head = new elem<T>(val, nullptr, nullptr);
			tail = head;
		}
		else {
			elem<T> *temp = new elem<T>(val, nullptr, tail);
			tail->next = temp;
			tail = temp;
		}
	}
	T pop() {
		if(empty()) return -1;
		elem<T> *temp = head;
		T ret = head->val;
		head = head->next;
		if(head == nullptr) tail = nullptr;
		delete temp;
		return ret;
	}
	void push_front(T val) {
		if(empty()) {
			head = new elem<T>(val, nullptr, nullptr);
			tail = head;
		}
		else {
			elem<T> *temp = new elem<T>(val, head, nullptr);
			head->before = temp;
			head = temp;
		}
	}
	T pop_back() {
		if(empty()) return -1;
		T ret = tail->val;
		elem<T> *temp = tail;
		tail = tail->before;
		if(tail == nullptr) head = nullptr;
		else tail->next = nullptr;
		delete temp;
		return ret;
	}
	elem<T>* find(T s) {
		elem<T>* curr = head;
		while(curr != nullptr) {
			if(curr->val == s) break; 
			curr = curr->next;
		}
		return curr;
	}
	void print() {
		elem<T>* curr = head;
		while(curr != nullptr) {
			std::cout << curr->val << " ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}
};

//stack implementation without using stl functions
template <class T>
struct stack {
	elem<T> *top;
	stack() {
		top = nullptr;
	}
	stack(int* v, int size) {
		top = nullptr;
		for(auto i = 0; i < size; ++i) {
			push(v[i]);
		}
	}
	bool empty() {
		return top == nullptr;
	}
	void push(T val) {
		top = new elem<T>(val, top, nullptr);
	}
	T pop() {
		if(empty()) return -1;
		elem<T> *temp = top;
		T ret = top->val;
		top = top->next;
		delete temp;
		return ret;
	}
	elem<T>* find(T s) {
		elem<T>* curr = top;
		while(curr != nullptr) {
			if(curr->val == s) break; 
			curr = curr->next;
		}
		return curr;
	}
	void print() {
		elem<T>* curr = top;
		while(curr != nullptr) {
			std::cout << curr->val << " ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}
};

//Simple graph implementation with few search algorithms
class Graph {
	int size;
	deque<int> *adj;
	int** cost;
	int head;
    void cleanUp();
public:
    Graph();
	Graph(int, int);
	virtual ~Graph();
    void resize(int);
    void setHead(int);
    int getHead();
    int getSize();
	void addEdge(int, int, int);
	void print();
	deque<int> BFS(int);
	deque<int> DFS(int);
	deque<int> Dijkstra(int);
};
}