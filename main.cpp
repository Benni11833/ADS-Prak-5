#include <fstream>
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
    int e1, e2;
    read_adjacent("tinyEWG.txt", g1);

	g1.print_adjacent();
	std::cout << std::endl << std::endl;
	std::cin.get();
	std::cout << "Rekursiv:\n";
	g1.Depth_first_search();
	std::cout << "Iterativ:\n";
	g1.Depth_first_search_iterativ();
	//std::cin.get();
	g1.Depth_first_path_finding();

    std::cout << "Edge1: "; std::cin >> e1;
    std::cout << "Edge2: "; std::cin >> e2;

    g1.check_if_connected(g1.getAdjacent()[e1][0], g1.getAdjacent()[e2][0]);

	//system("pause");
    return 0;
}