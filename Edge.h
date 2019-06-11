struct Edge{
	int From_;
    int To_;
    double Weight_;
    
	Edge(int From = -1, int To = -1, double Weight = -1.0) {
		From_ = From;
        To_ = To;
        Weight_ = Weight;
    }
	friend bool operator<(const Edge& e1, const Edge& e2) {
		if (e1.Weight_ > e2.Weight_)	//fuer priority-queue
			return true;
		return false;
	}
};