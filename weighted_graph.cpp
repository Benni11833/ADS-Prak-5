#include "weighted_graph.h"
#include <queue>
#include <stack>

Weighted_graph::Weighted_graph(unsigned int Knoten, unsigned int Kanten, std::map<int, std::vector<Edge>>& adjacent){
    Knoten_ = Knoten;
    Kanten_ = Kanten;
    adjacent_ = adjacent;
}

unsigned int Weighted_graph::getKnoten()const{ return Knoten_; }
unsigned int Weighted_graph::getKanten()const{ return Kanten_; }
void Weighted_graph::setKnoten(unsigned int Knoten){
    Knoten_ = Knoten;
}
void Weighted_graph::setKanten(unsigned int Kanten){
    Kanten_ = Kanten;
}

void Weighted_graph::print_adjacent()
{
	for (int i = 0; i < adjacent_.size(); i++) {
		std::cout << "Kanten von Knoten " << i << ": " << std::endl;
		for (int ii = 0; ii < adjacent_[i].size(); ii++)
			std::cout << adjacent_[i][ii].From_ << " -> " << adjacent_[i][ii].To_ << "\tweight: " << adjacent_[i][ii].Weight_ << std::endl;
		std::cout << std::endl << std::endl;
	}
}

std::map<int, std::vector<Edge>>& Weighted_graph::getAdjacent(){
    return adjacent_;
}

void Weighted_graph::Depth_first_search() {
	marked.resize(Knoten_+1, false);	//fangen bei 1-4 and und nicht von 0-3
	int i = 0;
	while (adjacent_[i].size() == 0)	//damit leere maps(zb wenn Knoten 6 nicht enthalten ist, uebersprungen werden)
		i++;
	Depth_first_search_rec(adjacent_[i].front());
}

void Weighted_graph::Depth_first_search_rec(Edge v)
{
	marked[v.From_] = true;
	/*Do Something with v...*/
	std::cout << "Knoten: " << v.From_ << std::endl;
	for (int i = 0; i < adjacent_[v.From_].size(); i++) {
		if(marked[adjacent_[v.From_][i].To_] == false)
			//if(adjacent_[v.To_].size() != 0)
				Depth_first_search_rec(adjacent_[v.To_][0]);
	}
}

void Weighted_graph::Depth_first_search_iterativ() {
	marked.clear();
	marked.resize(Knoten_ + 1, false);
	std::stack<Edge> stk;
	Edge v{ 0, 0, 0 };
	int i = 0, ii = 0;
	while (adjacent_[i].size() == 0)	//suche ersten Knoten mit adj liste >= 1
		i++;
	stk.push(adjacent_[i][ii++]);
	while (!stk.empty()) {
		v = stk.top();
		marked[v.From_] = true;
		stk.pop();
		/*Do Something with v...*/
		std::cout << "Knoten: " << v.From_ << std::endl;

		if (v.From_ == 1) {
			std::cout << "Adjazenzliste von " << v.From_ << std::endl;
			for (i = 0; i < adjacent_[v.From_].size(); i++)
				std::cout << adjacent_[v.From_][i].To_ << " ";
			std::cout << std::endl << std::endl;
		}

		//Alle adjazenten Knoten auf stack pushen, wenn vorhanden
		for (i = 0, ii=0; i < adjacent_[v.From_].size(); i++) {
			if (marked[adjacent_[v.From_][i].To_] == false) {
				std::cout << "Pushe Knoten " << adjacent_[v.To_][0].From_ << " auf Stack, weil Adjazent von Knoten " << v.From_ << std::endl;
				//std::cin.get();
				stk.push(adjacent_[v.To_][0]);
			}
		}
	}
}

void Weighted_graph::Depth_first_path_finding()
{
	marked.resize(Knoten_ + 1, false);	//fangen bei 1-4 and und nicht von 0-3
	edgeTo.resize(Knoten_ + 1, 0);
	int i = 0;
	while (adjacent_[i].size() == 0)	//damit leere maps(zb wenn Knoten 6 nicht enthalten ist, uebersprungen werden)
		i++;
	std::cout << "StartKnoten: " << adjacent_[i].front().From_ << std::endl;
	Depth_first_path_finding_rec(adjacent_[i].front());
	std::cout << "edgeTo:\n";
	i = 0;
	while (adjacent_[i].size() == 0)	//leere Eintraege in edgeTo ueberspringen
		i++;
	i++;	//erster Eintrag ist nicht erreichbar, da StartKnoten -> ueberspringen
	for (; i < edgeTo.size(); i++)
		std::cout << "Knoten " << i << " ueber Kante " << edgeTo[i] << " erreichbar.\n";
	std::cout << std::endl << std::endl;
}

void Weighted_graph::Depth_first_path_finding_rec(Edge v)
{
	marked[v.From_] = true;
	/*Do Something with v...*/
	std::cout << "Knoten: " << v.From_ << std::endl;
	std::cin.get();
	for (int i = 0; i < adjacent_[v.From_].size(); i++) {
		if (marked[adjacent_[v.From_][i].To_] == false) {
			//if(adjacent_[v.To_].size() != 0)
			//Depth_first_search_rec(marked, adjacent_[v.To_][0]);
			edgeTo[adjacent_[v.From_][i].To_] = v.From_;
			Depth_first_path_finding_rec(adjacent_[v.To_][0]);
		}
	}
}

bool Weighted_graph::check_if_connected(Edge & e1, Edge & e2)
{
	return false;
}
