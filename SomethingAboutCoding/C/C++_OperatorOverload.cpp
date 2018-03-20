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


// how to use self defined compare
sort(input.begin(), input.end(), interval<int>::compare);
