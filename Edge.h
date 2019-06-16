struct Edge{
	int From_;
    int To_;
    double Weight_;
    
	Edge(int From = -1, int To = -1, double Weight = -1.0) {
		From_ = From;
        To_ = To;
        Weight_ = Weight;
    }
	friend bool operator <(Edge e1, Edge e2) {
		return (e1.Weight_ > e2.Weight_);
	}
	bool operator ()(const Edge* e1, const Edge* e2) const	//Priority Queue vergleichs-funktion
	{
		return e1->Weight_ < e2->Weight_;
	}
};