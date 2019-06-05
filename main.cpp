#include "Graph.h"
#include <iostream>

int main() {

	Graph g1{ false, true };
	//g1.init("graph1.txt");
	//g1.printAll();
	GraphNode gn1{ 0 };
	Edge e{ 1, 7 };
	gn1.addEdge(e);
	e = Edge{ 3, 5 };
	gn1.addEdge(e);

	system("pause");
	return 0;
}