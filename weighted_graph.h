#include "Edge.h"
#include <vector>
#include <map>

class Weighted_graph{
private:
    unsigned int Knoten_;
    unsigned int Kanten_;
    std::map<int, std::vector<Edge>> adjacent_;
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
    void print_adjacent()const;
    std::map<int, std::vector<Edge>>& getAdjacent();
    void insert(Edge &edge);
};