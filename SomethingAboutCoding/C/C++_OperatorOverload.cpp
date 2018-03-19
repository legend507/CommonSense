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
};