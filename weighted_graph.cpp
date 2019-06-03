#include "weighted_graph.h"

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

std::map<int, std::vector<Edge>>& Weighted_graph::getAdjacent(){
    return adjacent_;
}