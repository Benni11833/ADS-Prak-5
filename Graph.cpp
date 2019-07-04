#include "Graph.h"
#include <fstream>
#include <queue>

/*
init
printAll
*/

GraphNode *Graph::getNodeByKey(int key)
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

bool Graph::init(std::string file)	//initialisiert/erstellt einen Graphen mit hilfe einer Textdatei der Form(v -> w Kosten)
{
	std::ifstream inFile;
	inFile.open(file);//Datei zum einlesen oeffnen
	int from, to;	//Kante from - to/ von - bis
	double weight;	//kosten der Kante from-to
	if (!inFile) {	//wenn Datei nicht geoeffnet werden konnte, breche ab
		std::cerr << "Datei " << file << " konnte nicht geoeffnet werden.\n";
		return false;
	}
	inFile >> anzKnoten_;	//erster Eintrag in TextDatei ist die Anzahl der Knoten
	nodes_.resize(anzKnoten_, nullptr);	//KnotenArray resizen mit der Anzahl der Knoten
	while (inFile >> from >> to >> weight) {	//einlesen der Kante: von - bis - Kosten der Kante
		if (!nodes_[from])	//Knoten 'from/von' existiert noch nicht im KnotenArray
			nodes_[from] = new GraphNode{ from };	//->neuen Knoten anlegen
		if (!nodes_[to])	//Knoten 'to/bis' existert noch nicht im KnotenArray
			nodes_[to] = new GraphNode{ to };	//->neuen Knoten anlegen
		//Pruefen ob Edge schon in nodes_[from]:
		if (!checkForEdge(nodes_[from], to)) {	//ueberpruefen ob Die Kante bereits in dem Knoten 'from/von' enthalten ist
			Edge e = Edge{ from, to, weight };	//->wenn nicht, neue Kante erzeugen
			nodes_[from]->addEdge(e);			//-> und zum KantenArray(edges_) des Knotens 'from/von' hinzufuegen
		}
		if (!checkForEdge(nodes_[to], from)) {	//gleiches wie oben, nur fuer den Knoten 'to/bis' ...
			Edge e = Edge{ to, from, weight };
			nodes_[to]->addEdge(e);
		}
	}

	return true;
}

void Graph::printAll()	//gibt den Graphen aus
{
	for (int i = 0; i < nodes_.size(); i++) {	//Alle Knoten durchgehen
		if (nodes_[i] != nullptr) {	//wenn der Knoten vorhanden ist(ist er != nullptr)
			std::cout << nodes_[i]->getKey();	//Knoten ausgeben(seinen Wert/Schluessel)
			for (int ii = 0; ii < nodes_[i]->getNumberOfEdges(); ii++) {	//Alle Kanten, die von dem Knoten/Schluessel zu einem adjazenten/benachbarten Knoten fuehren ausgeben
				std::cout << " -> " << nodes_[i]->getEdge(ii)->To_ << " [" << nodes_[i]->getEdge(ii)->Weight_ << ']';	//Ziel der Kante ('to/bis') und Kosten/gewicht der Kante
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

double Graph::prim(int startKey)	//Liefert MST / Minimal Spanning Tree - Minimaler SpannBaum(der von einem startKnoten alle Knoten mit den wenigsten Kosten erreicht)
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
		//std::cout << "Knoten: " << w << " Weight: " << e.Weight_ << std::endl;
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
	std::priority_queue<Edge> pq;
	Edge e;
	std::vector<GraphNode*> e_vec;
	for (int i = 0; i < nodes_.size(); i++) {
		e_vec.push_back(nodes_[i]);
		nodes_[i]->setComponent(i);
		for (int j = 0; j < nodes_[i]->getNumberOfEdges(); j++)
			pq.push(*(nodes_[i]->getEdge(j)));
	}

	while (!pq.empty()) {
		e = pq.top();	pq.pop();
		v = e.From_;	w = e.To_;
		if (nodes_[v]->getComponent() != nodes_[w]->getComponent()) {
			mst_weight += e.Weight_;
			std::cout << "Knoten: " << w << "->" << v << " Weight: " << e.Weight_ << std::endl;
			for (int i = 0; i < nodes_.size(); i++)
				if (i != w && nodes_[i]->getComponent() == nodes_[w]->getComponent())
					nodes_[i]->setComponent(nodes_[v]->getComponent());
			nodes_[w]->setComponent(nodes_[v]->getComponent());	//i->componen = v->component aendert wert so, dass vorherige Baum-IDs/Component nicht mehr erkannt werden
		}
	}

	return mst_weight;
}

int Graph::getAnzKnoten()
{
	int count = 0;
	for (int i = 0; i < nodes_.size(); i++)
		if (nodes_[i])
			++count;
	return count;
}
