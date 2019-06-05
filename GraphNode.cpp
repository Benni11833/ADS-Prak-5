#include "GraphNode.h"

GraphNode::GraphNode(int key) {
	key_ = key;
	//def-construktor fuer edge_
}
bool GraphNode::getVisited() { return visited_; }
void GraphNode::setVisited(bool visited) { visited_ = visited; }
int GraphNode::getKey() { return key_; }
void GraphNode::setKey(int key) { key_ = key; }
void GraphNode::addEdge(Edge edge) { edges_.push_back(edge); }
Edge* GraphNode::getEdge(int key) { return &(edges_[key]); }
int GraphNode::getNumberOfEdges() { return edges_.size(); }
int GraphNode::getComponent() { return component_; }
void GraphNode::setComponent(int component) { component_ = component; }
