#include "GraphNode.h"
#include <string>
#include <iostream>

class Graph {
private:
	int anzKnoten_;
	bool gerichtet_;
	bool gewichtet_;
	std::vector<GraphNode*> nodes_;

	GraphNode* getNodeByKey(int key);
	void setAllUnvisited();
	bool checkAllVisited();
	void startDephSearchRek(GraphNode *node);
	bool testChildComponent(GraphNode *node);
public:
	Graph(bool gerichtet, bool gewichtet);
	~Graph();
	bool init(std::string file);
	void printAll();
	bool depthSearchRek(int startKey);
	bool breadthSearchiter(int startKey);
	double prim(int startKey);
	double kruskal(int startKey);
	int getAnzKnoten();
};