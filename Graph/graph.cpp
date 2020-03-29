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

//Queue implementation without using stl functions
template <class T>
struct queue {
	elem<T> *head;
	elem<T> *tail;
	queue() {
		head = nullptr;
		tail = nullptr;
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
	queue<int> *adj;
	int head;
public:
	Graph(int, int);
	virtual ~Graph();
	void addEdge(int, int);
	void setHead(int);
	void print();
	queue<int> BFS(int);
	queue<int> DFS(int);
};

Graph::Graph(int size, int head) : size(size), head(head) {
	adj = new queue<int>[size];
}

Graph::~Graph() {
	for(auto i = 0; i < size; ++i) {
		auto curr = adj[i];
		while(!curr.empty()) {
			curr.pop();
		}
	}
	delete adj;
}

void Graph::addEdge(int from, int to) {
	if(adj[from].find(to) == nullptr) {
		adj[from].push(to);
	}
}

void Graph::setHead(int head) {
	this->head = head;
}

void Graph::print() {
	for(auto i = 0; i < size; ++i) {
		std::cout << i << " -> ";
		adj[i].print();
	}
}

//Breadth-First Search algorithm implementation
queue<int> Graph::BFS(int s) {
	bool visited[size];
	for(auto i = 0; i < size; i++) {
		visited[i] = false;
	}
	bool found = false;
	int path[size];
	queue<int> queued;

	queued.push(head);
	visited[head] = true;
	
	while(!queued.empty()) {
		auto q = queued.pop();
		if(q == s) {
			found = true;
			break;
		}

		auto curr = adj[q].head;
		while(curr != nullptr) {
			if(visited[curr->val]) {
				curr = curr->next;
				continue;
			}
			queued.push(curr->val);
			path[curr->val] = q;
			visited[curr->val] = true;
			curr = curr->next;
		}
	}
	if(!found) return queue<int>(); // empty path

	queue<int> ret;
	int i = s;
	while(true) {
		ret.push_front(i);
		if(i == head) break;
		i = path[i];
	}
	return ret;
}

queue<int> Graph::DFS(int s) {
	
	return queue<int>();
}
};

int main() {
	no_stl::Graph g(6, 0);
	g.addEdge(0, 1);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(1, 3);
	g.addEdge(1, 2);
	g.addEdge(3, 1);
	g.addEdge(4, 3);
	g.addEdge(4, 5);
	g.addEdge(5, 0);
	g.print();
	auto path = g.BFS(5);
	path.print();
	return 0;
}
