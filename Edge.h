class Edge{
public:
    int To_;
    int From_;
    double Weight_;
    
    Edge(int To, int From, double Weight){
        To_ = To;
        From_ = From;
        Weight_ = Weight;
    }
};