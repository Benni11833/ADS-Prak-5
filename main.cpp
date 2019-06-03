#include <fstream>
#include <iostream>
#include <iterator>
//#include "weighted_graph.h"
/*Edge gibt jeweils eine Kante an mit (v, w) und Kosten */

#include <map>
#include <vector>
#include "weighted_graph.h"

void read_adjacent(const char *datafile, Weighted_graph& graph){
    int tmp;
    graph.getAdjacent().clear();
    Edge Ed = Edge{0, 0, 0};
    //test[1].push_back(newEdge);
    std::ifstream inFile;
    inFile.open(datafile);
    if(!inFile.is_open())
        std::cerr << datafile << " konnte nicht geoeffnet werden.\n";
    inFile >> tmp;
    graph.setKnoten(tmp);
    inFile >> tmp;
    graph.setKanten(tmp);

    while(!inFile.eof()){
        inFile >> Ed.From_ >> Ed.To_ >> Ed.Weight_;
        graph.getAdjacent()[Ed.From_].push_back(Ed);
    }
    inFile.close();
}

int main(){

    Weighted_graph g1{0, 0};
    read_adjacent("tinyEWG.txt", g1);

    std::cout << "Map.size(): " << g1.getAdjacent().size() << std::endl;
    for(int i=0; i < g1.getAdjacent().size(); i++){
        std::cout << "Kanten von Knoten " << i << ": " << std::endl;
        for(int ii=0; ii < g1.getAdjacent()[i].size(); ii++)
            std::cout << g1.getAdjacent()[i][ii].From_ << " -> " << g1.getAdjacent()[i][ii].To_ << "\tweight: " << g1.getAdjacent()[i][ii].Weight_ << std::endl;
        std::cout << std::endl << std::endl;
    }

    return 0;
}