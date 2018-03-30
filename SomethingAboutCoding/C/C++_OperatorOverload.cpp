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
	// compare func, is i1 smaller than i2? if used in sort, result is ascending
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

/*
以下是一个把Person的名字按照字典序拍列的compare func
注意，如果两个人名完全一样，则 compare(p1, p2) == true, 并且 compare(p2, p1) == true
这时候会有 runtime error
*/
// a structure of TreeNode
struct Person {
	string familyName;
	string givenName;

	Person(string fn, string gn) :familyName(fn), givenName(gn) {}

	/*is p1 small than p2*/
	static bool compare(Person& p1, Person& p2) {
		string p1FullName = p1.familyName + " " + p1.givenName;
		string p2FullName = p2.familyName + " " + p2.givenName;

		int i = 0;
		int j = 0;
		for (;
			i < p1FullName.size() && j < p2FullName.size();
			i++, j++) {
			// p1:a, p2:a
			if (p1FullName[i] == p2FullName[j])	continue;
			// p1:b, p2:a
			if (p1FullName[i] > p2FullName[j]) return false;
			else return true;
		}

		// one reached the end
		if (i == p1FullName.size())	return true;
		else return false;
	}

	friend ostream& operator << (ostream& os, Person& p) {
		os << p.familyName << " " << p.givenName;
		return os;
	}
};


int main() {

	vector<Person> names = { Person("ab", "cd"), Person("a", "bcd"), Person("ac", "bd"), Person("ab", "c"), Person("e", "l") };

	sort(names.begin(), names.end(), Person::compare);
	for (auto one : names)	cout << one << endl;


	system("pause");
	return 0;
}

