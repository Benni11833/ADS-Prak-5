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
	//Graph(bool gerichtet, bool gewichtet);
	Graph() {
		anzKnoten_ = 0;
		gerichtet_ = gewichtet_ = false;
		nodes_.clear();
	}
	~Graph();
	bool init(std::string file);
	void printAll();
	bool depthSearchRek(int startKey);
	bool breadthSearchiter(int startKey);
	double prim(int startKey);
	double kruskal();
	int getAnzKnoten();
	
	bool check_if_connected(int node1, int node2);
};