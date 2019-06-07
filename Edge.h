struct Edge{
    int To_;
    double Weight_;
    
    Edge(int To=-1, double Weight=-1.0){
        To_ = To;
        Weight_ = Weight;
    }
	friend bool operator<(const Edge& e1, const Edge& e2) {
		if (e1.Weight_ > e2.Weight_)	//fuer priority-queue
			return true;
		return false;
	}
};