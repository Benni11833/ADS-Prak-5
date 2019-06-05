#include "Edge.h"
#include <vector>

class GraphNode {
private:
	//Edge edge_;
	int key_;
	std::vector<Edge> edges_;
	int component_;	//wofür
	bool visited_;
public:
	GraphNode(int key);
	bool getVisited();
	void setVisited(bool visited);
	int getKey();
	void setKey(int key);
	void addEdge(Edge edge);
	Edge* getEdge(int key);
	int getNumberOfEdges();
	int getComponent();
	void setComponent(int component);
};