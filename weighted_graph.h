#include "Edge.h"
#include <vector>
#include <map>
#include <iostream>

class Weighted_graph{
private:
    unsigned int Knoten_;
    unsigned int Kanten_;
    std::map<int, std::vector<Edge>> adjacent_;
	std::vector<bool> marked;
	std::vector<int> edgeTo;
public:
    Weighted_graph(unsigned int Knoten = 0, unsigned int Kanten = 0){
        Knoten_ = Knoten;
        Kanten_ = Kanten;
    }
    Weighted_graph(unsigned int Knoten, unsigned int Kanten, std::map<int, std::vector<Edge>>& adjacent);
    unsigned int getKnoten()const;
    unsigned int getKanten()const;
    void setKnoten(unsigned int Knoten);
    void setKanten(unsigned int Kanten);
    void print_adjacent();
    std::map<int, std::vector<Edge>>& getAdjacent();
	void Depth_first_search();
	void Depth_first_search_rec(Edge v);
	void Depth_first_search_iterativ();
	void Depth_first_path_finding();
	void Depth_first_path_finding_rec(Edge v);
	//bool check_if_connected(Edge& e1, Edge& e2);
    void check_if_connected(Edge &e1, Edge &e2);
    std::vector<int> pathTo(int s, int v);
};