#include "Graph.h"
#include <fstream>

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
		nodes_[i]->setVisited(false);
	}
}

bool Graph::checkVisited()	//???
{
	return false;
}

void Graph::startDephSearchRek(GraphNode * node)
{
	 
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
}

bool Graph::init(std::string file)
{
	std::ifstream inFile;
	int from, to;
	double weight;
	inFile.open(file);
	if (!inFile) {
		std::cerr << "Datei " << file << " konnte nicht geoeffnet werden.\n";
		return false;
	}
	inFile >> anzKnoten_;
	nodes_.resize(anzKnoten_, nullptr);
	while (!inFile.eof()) {
		inFile >> from >> to >> weight;
		if (nodes_[from] == nullptr) {	//Knoten existiert noch nicht
			nodes_[from] = new GraphNode{ from };
			Edge e = Edge{ to, weight };
			nodes_[from]->addEdge(e);
		}
		else {	////Knoten existiert schon -> nur neue Edge hinzufuegen
			nodes_[from]->addEdge(Edge{ to, weight });
		}
	}
	//inFile.close();

	return true;
}

void Graph::printAll()
{
	for (int i = 0; i < nodes_.size(); i++) {
		if (nodes_[i] != nullptr) {
			std::cout << nodes_[i]->getKey();
			for (int ii = 0; ii < nodes_[i]->getNumberOfEdges(); ii++) {
				std::cout << "\t-> " << nodes_[i]->getEdge(ii)->To_ << nodes_[i]->getEdge(ii)->Weight_;
			}
		}
	}
	std::cout << std::endl;
}

bool Graph::depthSearchRek(int startKey)
{
	return false;
}

bool Graph::breadthSearchiter(int startKey)
{
	return false;
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
	return 0;
}
