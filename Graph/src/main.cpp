#include <iostream>
#include "graph.hpp"

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