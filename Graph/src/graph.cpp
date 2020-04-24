#include "graph.hpp"

no_stl::Graph::Graph() : size(0), head(-1) {
	adj = nullptr;
	cost = nullptr;
}

no_stl::Graph::Graph(int size, int head) : size(size), head(head) {
	adj = new no_stl::deque<int>[size];
	cost = new int*[size];
	for(auto i = 0; i < size; ++i) {
		cost[i] = new int[size];
		for(auto j = 0; j < size; ++j) {
			cost[i][j] = 0;
		}
	}
}

no_stl::Graph::~Graph() {
	this->cleanUp();
}

void no_stl::Graph::cleanUp() {
	if(adj != nullptr) {
		for(auto i = 0; i < size; ++i) {
			auto curr = adj[i];
			while(!curr.empty()) {
				curr.pop();
			}
		}
		delete [] adj;
	}
	if(cost != nullptr) {
		for(auto i = 0; i < size; ++i) {
			delete [] cost[i];
		}
		delete [] cost;
	}
}

void no_stl::Graph::resize(int size) {
	if(this->size == size) return;

	no_stl::deque<int> new_adj[size];
	int *new_cost[size];


	int min_s = (this->size > size) ? size : this->size;
	for(int i = 0; i < min_s; ++i) {
		new_adj[i] = adj[i];
		new_cost[i] = new int[size];
		for(int j = 0; j < min_s; ++j) {
			new_cost[i][j] = cost[i][j];
		}
		delete [] cost[i];
	}
	delete [] adj;
	delete [] cost;

	adj = new_adj;
	cost = new_cost;
	this->size = size;
	this->head = -1; //avoids referencing heads that were deleted after reducing the graph size
}

void no_stl::Graph::addEdge(int from, int to, int cost = 0) {
	if(from < 0 || from >= size || to < 0 || to >= size) throw "Out of boundary.";

	if(adj[from].find(to) == nullptr) {
		adj[from].push(to);
	}
	if(adj[to].find(from) == nullptr) {
		adj[to].push(from);
	}
	this->cost[from][to] = cost;
	this->cost[to][from] = cost;
}

void no_stl::Graph::setHead(int head) {
	this->head = head;
}

int no_stl::Graph::getHead() {
	return this->head;
}

int no_stl::Graph::getSize() {
	return this->size;
}

void no_stl::Graph::print() {
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
no_stl::deque<int> no_stl::Graph::BFS(int s) {
	if(size <= 0 || head < 0 || head >= size) return no_stl::deque<int>(); //empty path
	bool visited[size];
	for(auto i = 0; i < size; i++) {
		visited[i] = false;
	}
	bool found = false;
	int path[size];
	no_stl::deque<int> queued;

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
	if(!found) return no_stl::deque<int>(); // empty path

	no_stl::deque<int> ret;
	int i = s;
	while(true) {
		ret.push_front(i);
		if(i == head) break;
		i = path[i];
	}
	return ret;
}

no_stl::deque<int> no_stl::Graph::DFS(int s) {
	if(size <= 0 || head < 0 || head >= size) return no_stl::deque<int>(); //empty path
	bool visited[size];
	for (auto i = 0; i < size; i++) {
		visited[i] = false;
	}
	int path[size];
	bool found = false;
	
	no_stl::stack<int> stacked;
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
		return no_stl::deque<int>(); //empty path
	}
	int i = s;
	no_stl::deque<int> ret;
	while(true) {
		ret.push_front(i);
		if (i == head) break;
		i = path[i];
	}
	return ret;
}
no_stl::deque<int> no_stl::Graph::Dijkstra(int s) {
	if(size <= 0 || head < 0 || head >= size) return no_stl::deque<int>(); //empty path
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
	no_stl::deque<int> costs(minCost, size);
	costs.print();
	no_stl::deque<int> ret;
	auto i = s;
	while(true) {
		ret.push_front(i);
		if(i == head) break;
		i = parent[i];
	}
	return ret;
}