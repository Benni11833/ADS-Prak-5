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

/*Graph::Graph(bool gerichtet, bool gewichtet)
{
	gerichtet_ = gerichtet;
	gewichtet_ = gewichtet;
	anzKnoten_ = 0;
}*/

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
			Edge e = Edge{from, to, weight };
			nodes_[from]->addEdge(e);
		}
		else {	////Knoten existiert schon -> nur neue Edge hinzufuegen
			nodes_[from]->addEdge(Edge{from, to, weight });
		}
		if (!nodes_[to]) {
			//std::cout << "!nodes_[" << to << "]..." << std::endl;
			nodes_[to] = new GraphNode{ to };
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
	if (!nodes_[startKey])
		return false;
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
		//std::cout << "BFS - Knoten: " << v->getKey() << std::endl;
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
	if (!nodes_[startKey]) {
		std::cerr << "Startkey: " << startKey << "nicht gueltig..." << std::endl;
		return -1;
	}

	std::priority_queue<Edge> pq;
	double mst_weight = 0.0;
	Edge e;
	setAllUnvisited();
	//Kanten von StartKnoten in pq pushen
	for (int i = 0; i < nodes_[startKey]->getNumberOfEdges(); i++)
		pq.push(*(nodes_[startKey]->getEdge(i)));
	while (!pq.empty()) {
		e = pq.top();	pq.pop();
		if (!nodes_[e.From_]->getVisited()) {
			nodes_[e.From_]->setVisited(true);
			mst_weight += e.Weight_;
		}
		for (int i = 0; i < nodes_[e.To_]->getNumberOfEdges(); i++) {
			if (!nodes_[nodes_[e.To_]->getEdge(i)->To_]->getVisited())
				pq.push(*(nodes_[e.To_]->getEdge(i)));
		}
	}

	return mst_weight;
}

double Graph::kruskal()
{
	setAllUnvisited();
	double mst_weight = 0;
	Edge e;
	std::priority_queue<Edge> pq;
	for (int i = 0; i < nodes_.size(); i++)
		if (nodes_[i]) {
			for (int j = 0; j < nodes_[i]->getNumberOfEdges(); j++)
				pq.push(*(nodes_[i]->getEdge(j)));
		}
	//Leichteste Kante rausnehmen und an MST anhaengen, wenn durch diese kein Zyklus entsteht(From, To sollten unvisited sein)
	while (!pq.empty()) {
		e = pq.top();	pq.pop();
		if (nodes_[e.To_] && !getNodeByKey(e.To_)->getVisited() && !getNodeByKey(e.From_)->getVisited()) {
			getNodeByKey(e.From_)->setVisited(true);
			mst_weight += e.Weight_;
			//std::cout << "Mst - Knoten: " << e.From_ << "->" << e.To_ << ", Weight: " << e.Weight_ << std::endl;
			//std::cin.get();
		}
	}

	return mst_weight;
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
