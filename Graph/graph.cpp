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
public:
	Graph(int, int);
	virtual ~Graph();
	void addEdge(int, int, int);
	void setHead(int);
	void print();
	deque<int> BFS(int);
	deque<int> DFS(int);
	deque<int> Dijkstra(int);
};

Graph::Graph(int size, int head) : size(size), head(head) {
	adj = new deque<int>[size];
	cost = new int*[size];
	for(auto i = 0; i < size; ++i) {
		cost[i] = new int[size];
		for(auto j = 0; j < size; ++j) {
			cost[i][j] = 0;
		}
	}
}

Graph::~Graph() {
	for(auto i = 0; i < size; ++i) {
		auto curr = adj[i];
		while(!curr.empty()) {
			curr.pop();
		}
	}
	delete adj;
	for(auto i = 0; i < size; ++i) {
		delete cost[i];
	}
	delete cost;
}

void Graph::addEdge(int from, int to, int cost = 0) {
	if(adj[from].find(to) == nullptr) {
		adj[from].push(to);
	}
	if(adj[to].find(from) == nullptr) {
		adj[to].push(from);
	}
	this->cost[from][to] = cost;
	this->cost[to][from] = cost;
}

void Graph::setHead(int head) {
	this->head = head;
}

void Graph::print() {
	std::cout << "Adjacency: " << std::endl; 
	for(auto i = 0; i < size; ++i) {
		std::cout << i << " -> ";
		adj[i].print();
	}
	std::cout << "Cost Matrix: " << std::endl;
	for(auto i = 0; i < size; ++i) {
		for(auto j = 0; j < size; ++j) {
			std::cout << cost[i][j] << "\t";
		}
		std::cout << std::endl;
	} 
}

//Breadth-First Search algorithm implementation
deque<int> Graph::BFS(int s) {
	bool visited[size];
	for(auto i = 0; i < size; i++) {
		visited[i] = false;
	}
	bool found = false;
	int path[size];
	deque<int> queued;

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
	if(!found) return deque<int>(); // empty path

	deque<int> ret;
	int i = s;
	while(true) {
		ret.push_front(i);
		if(i == head) break;
		i = path[i];
	}
	return ret;
}

deque<int> Graph::DFS(int s) {
	bool visited[size];
	for (auto i = 0; i < size; i++) {
		visited[i] = false;
	}
	int path[size];
	bool found = false;
	
	stack<int> stacked;
	stacked.push(head);
	while(!stacked.empty()) {
		auto q = stacked.pop();
		if(visited[q]) continue;
		visited[q] = true;

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
			stacked.push(curr->val);
			path[curr->val] = q;
			curr = curr->next;
		}
	}
	if(!found) {
		return deque<int>(); //empty path
	}
	int i = s;
	deque<int> ret;
	while(true) {
		ret.push_front(i);
		if (i == head) break;
		i = path[i];
	}
	return ret;
}
deque<int> Graph::Dijkstra(int s) {
	bool visited[size];
	for(auto i = 0; i < size; ++i) {
		visited[i] = false;
	}
	
	int visitedTotal = 0;
	int minCost[size];
	for(auto i = 0; i < size; ++i) {
		minCost[i] = INT32_MAX;
	}
	
	int parent[size];
	
	minCost[head] = 0;
	auto currentNode = head;

	while(visitedTotal < size) {
		auto curr = adj[currentNode].head;
		while(curr != nullptr) {
			auto c = cost[currentNode][curr->val] + minCost[currentNode];
			if(c < minCost[curr->val]) {
				minCost[curr->val] = c;
				parent[curr->val] = currentNode;
			}
			curr = curr->next;
		}
		visited[currentNode] = true;
		visitedTotal++;

		auto minCurrCost = INT32_MAX;
		auto nextNode =currentNode;
		for(auto i = 0; i < size; ++i) {
			if(!visited[i] && minCost[i] < minCurrCost) {
				minCurrCost = minCost[i];
				nextNode = i;
			}
		}
		if(nextNode == currentNode) break;
		currentNode = nextNode;
	}
	std::cout << "Minimum cost for node " << s << " is " << minCost[s] << std::endl;
	deque<int> costs(minCost, size);
	costs.print();
	deque<int> ret;
	auto i = s;
	while(true) {
		ret.push_front(i);
		if(i == head) break;
		i = parent[i];
	}
	return ret;
}
};

int main() {
	no_stl::Graph g(7, 0);
	g.addEdge(0, 1, 2);
	g.addEdge(0, 5, 9);
	g.addEdge(1, 2, 2);
	g.addEdge(1, 3, 8);
	g.addEdge(2, 3, 3);
	g.addEdge(2, 4, 4);
	g.addEdge(3, 4, 1);
	g.addEdge(4, 5, 3);
	g.addEdge(5, 6, 3);
	g.print();
	auto path = g.BFS(4);
	path.print();
	path = g.DFS(4);
	path.print();
	path = g.Dijkstra(4);
	path.print();
	return 0;
}
