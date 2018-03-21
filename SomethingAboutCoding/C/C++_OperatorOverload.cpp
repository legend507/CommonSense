template <typename T>
struct interval {
	T start;
	T end;
	// constructor
	interval(int x, int y) : start(x), end(y) {};
	// operator overload
	friend ostream& operator << (ostream& stream, const interval<T>& obj) {
		stream << "{" << obj.start << "," << obj.end << "}";
		return stream;
	};
	// compare func
	static bool compare(interval<T>& i1, interval<T>& i2) {
		return (i1.start < i2.start);
	}
};


struct cell {
	int parent_i;	// parent i coordinate
	int parent_j;	// parent j coordinate
	double f;	// f = g + h
	double g;	// physical distance from (i,j) to (i',j') or Euclid Dist
	double h;	//

				// operator overload ==
	inline bool operator==(const cell& cell) {
		return (cell.parent_i == parent_i && cell.parent_j == parent_j);
	}

	cell() :parent_i(-1), parent_j(-1), f(FLT_MAX), g(FLT_MAX), h(FLT_MAX) {};
};

