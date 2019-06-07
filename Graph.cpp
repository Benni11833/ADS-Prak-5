#include "Graph.h"
#include <fstream>
#include <queue>

GraphNode * Graph::getNodeByKey(int key)
{
	for (int i = 0; i < nodes_.size(); i++) {
		if (nodes_[i]->getKey() == key)
			return nodes_[i];
	}
	return nullptr;
}

void Graph::setAllUnvisited()
{
	for (int i = 0; i < nodes_.size(); i++) {
		if(nodes_[i])
			nodes_[i]->setVisited(false);
	}
}

bool Graph::checkAllVisited()
{
	for (int i = 0; i < nodes_.size(); i++)
		if (nodes_[i] && !nodes_[i]->getVisited())
			return false;
	return true;
}

void Graph::startDephSearchRek(GraphNode * node)
{
	node->setVisited(true);
	std::cout << "DFS - Knoten: " << node->getKey() << std::endl;
	for (int i = 0; i < node->getNumberOfEdges(); i++)
		if(nodes_[node->getEdge(i)->To_] && !nodes_[node->getEdge(i)->To_]->getVisited())
			//Kein nullptr und wurde noch nicht besucht
			startDephSearchRek(nodes_[node->getEdge(i)->To_]);
}

bool Graph::testChildComponent(GraphNode * node)	//???
{
	return false;
}

Graph::Graph(bool gerichtet, bool gewichtet)
{
	gerichtet_ = gerichtet;
	gewichtet_ = gewichtet;
}

Graph::~Graph()
{
	for (int i = 0; i < nodes_.size(); i++)
		if (nodes_[i])
			delete nodes_[i];
	nodes_.resize(0);
}

bool Graph::init(std::string file)
{
	std::ifstream inFile;
	inFile.open(file);
	int from, to;
	double weight;
	if (!inFile) {
		std::cerr << "Datei " << file << " konnte nicht geoeffnet werden.\n";
		return false;
	}
	inFile >> anzKnoten_;
	nodes_.resize(anzKnoten_, nullptr);
	while (inFile >> from >> to >> weight) {
		if (nodes_[from] == nullptr) {	//Knoten existiert noch nicht
			nodes_[from] = new GraphNode{ from };
			Edge e = Edge{ to, weight };
			nodes_[from]->addEdge(e);
		}
		else {	////Knoten existiert schon -> nur neue Edge hinzufuegen
			nodes_[from]->addEdge(Edge{ to, weight });
		}
	}

	return true;
}

void Graph::printAll()
{
	for (int i = 0; i < nodes_.size(); i++) {
		if (nodes_[i] != nullptr) {
			std::cout << nodes_[i]->getKey();
			for (int ii = 0; ii < nodes_[i]->getNumberOfEdges(); ii++) {
				std::cout << " -> " << nodes_[i]->getEdge(ii)->To_ << " [" << nodes_[i]->getEdge(ii)->Weight_ << ']';
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

bool Graph::depthSearchRek(int startKey)
{
	setAllUnvisited();
	startDephSearchRek(nodes_[startKey]);
	return checkAllVisited();
}

bool Graph::breadthSearchiter(int startKey)
{
	setAllUnvisited();
	std::queue<GraphNode*> q;
	GraphNode *v = nullptr;
	q.push(nodes_[startKey]);
	nodes_[startKey]->setVisited(true);
	while (!q.empty()) {
		v = q.front();
		//v->setVisited(true);
		q.pop();
		std::cout << "BFS - Knoten: " << v->getKey() << std::endl;
		if (v != nullptr) {
			for (int i = 0; i < v->getNumberOfEdges(); i++)
				if (nodes_[v->getEdge(i)->To_] && !nodes_[v->getEdge(i)->To_]->getVisited()) {
					nodes_[v->getEdge(i)->To_]->setVisited(true);
					q.push(nodes_[v->getEdge(i)->To_]);
				}
		}
	}

	return checkAllVisited();
}

double Graph::prim(int startKey)
{
	return 0.0;
}

double Graph::kruskal(int startKey)
{
	return 0.0;
}

int Graph::getAnzKnoten()
{
	//return nodes_.size();	//gibt mehr Knoten an als normalerweise drin sind
	int count = 0;
	for (int i = 0; i < nodes_.size(); i++)
		if (nodes_[i])
			++count;
	return count;
}
