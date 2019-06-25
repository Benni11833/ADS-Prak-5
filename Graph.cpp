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
	//std::cout << "DFS - Knoten: " << node->getKey() << std::endl;
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

bool checkForEdge(GraphNode* node, int From) {
	for (int i = 0; i < node->getNumberOfEdges(); i++)
		if (node->getEdge(i)->To_ == From)
			return true;
	return false;
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
		if (!nodes_[from])	//Knoten existiert noch nicht
			nodes_[from] = new GraphNode{ from };
		if (!nodes_[to])
			nodes_[to] = new GraphNode{ to };
		//Pruefen ob Edge schon in nodes_[from]:
		if (!checkForEdge(nodes_[from], to)) {
			Edge e = Edge{ from, to, weight };
			nodes_[from]->addEdge(e);
		}
		if (!checkForEdge(nodes_[to], from)) {
			Edge e = Edge{ to, from, weight };
			nodes_[to]->addEdge(e);
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
	int v, w;
	
	nodes_[startKey]->setVisited(true);
	//alle adj von startKey pushen:
	for (int i = 0; i < nodes_[startKey]->getNumberOfEdges(); i++)
			pq.push(*(nodes_[startKey]->getEdge(i)));

	while (!pq.empty()) {
		e = pq.top();
		pq.pop();
		v = e.From_;
		w = e.To_;

		//kein Zyklus
		if (nodes_[v]->getVisited() && nodes_[w]->getVisited())
			continue;

		//e zum mst hinzufuegen
		mst_weight += e.Weight_;

		//Adjazenten von v und w zum PQ hinzufuegen, wenn nicht schon vorher
		if (!nodes_[v]->getVisited()) {
			nodes_[v]->setVisited(true);
			for (int i = 0; i < nodes_[v]->getNumberOfEdges(); i++)
				if (!nodes_[nodes_[v]->getEdge(i)->To_]->getVisited())
					pq.push(*(nodes_[v]->getEdge(i)));
		}
			
		if (!nodes_[w]->getVisited()) {
			nodes_[w]->setVisited(true);
			for (int i = 0; i < nodes_[w]->getNumberOfEdges(); i++)
				if (!nodes_[nodes_[w]->getEdge(i)->To_]->getVisited())
					pq.push(*(nodes_[w]->getEdge(i)));
		}
	}

	return mst_weight;
}

double Graph::kruskal()
{
	setAllUnvisited();
	double mst_weight = 0;
	int v, w;
	std::vector<int> treeID;	treeID.resize(nodes_.size());
	std::priority_queue<Edge> pq;
	Edge e;
	std::vector<GraphNode*> e_vec;
	for (int i = 0; i < nodes_.size(); i++) {
		e_vec.push_back(nodes_[i]);
		treeID[i] = i;
		for (int j = 0; j < nodes_[i]->getNumberOfEdges(); j++)
			pq.push(*(nodes_[i]->getEdge(j)));
	}

	while (!pq.empty()) {
		e = pq.top();	pq.pop();
		v = e.From_;	w = e.To_;
		if (treeID[v] != treeID[w]) {
			mst_weight += e.Weight_;
			for (int i = 0; i < treeID.size(); i++)
				if (i != w && treeID[i] == treeID[w])
					treeID[i] = treeID[v];
			treeID[w] = treeID[v];	//treeID[i] = treeID[v] aendert wert so, dass vorherige Baum-IDs nicht mehr erkannt werden
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
