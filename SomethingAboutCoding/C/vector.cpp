
// This creates a vector of RR size CC vectors, filled with 0.
vector<vector<int> > matrix(RR, std::vector<int>(CC));
vector<vector<char>> answer(boundary_x, vector<char>(boundary_y, '0')); // declare with initilization to '0'

// get the size of matrix 
vector<vector<char>> board:
int boundary_x = board.size();
int boundary_y = board[0].size();

// print out a matrix
template <typename T>
void printVectorMadeMatrix(vector<vector<T>>& data) {
	for (int i = 0; i < data.size(); i++) {
		std::copy(data[i].begin(), data[i].end(), std::ostream_iterator<T>(std::cout, " "));
		cout << endl;
	}
}

// print out a vector
template <typename T>
void Print(const std::vector<T>& v) {
    for(auto& i : v)
        std::cout << i << '\n';
}

// vector<pair<int1, int2>> sorting problem,
/// sort the vector, ascend on int1, descend on int2 if int1 are the same
class Solution {
public:
	static bool cmp_first(const pair<int, int>& i, const pair<int, int>& j) {
		if (i.first == j.first)
			return i.second > j.second;
		return i.first < j.first;
	}
	int maxEnvelopes(vector<pair<int, int>>& envelopes) {
		sort(envelopes.begin(), envelopes.end(), cmp_first);
		vector<int> dp;
		for (int i = 0; i < envelopes.size(); ++i) {

			// lower_bound: Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
			auto itr = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
			if (itr == dp.end()) {
				dp.push_back(envelopes[i].second);
			}
			else {
				*itr = envelopes[i].second;
			}
		}
		return dp.size();
	}
};

// find max/min element in a vector
#include <iostream>     // std::cout
#include <algorithm>    // std::min_element, std::max_element

int main()
{
    std::vector<double> v {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    auto biggest = std::max_element(std::begin(v), std::end(v));
    std::cout << "Max element is " << *biggest
        << " at position " << std::distance(std::begin(v), biggest) << std::endl;

    auto smallest = std::min_element(std::begin(v), std::end(v));
    std::cout << "min element is " << *smallest
        << " at position " << std::distance(std::begin(v), smallest) << std::endl;
		
		
	// *max_element(vector.begin(), vector.end()) // This also work
}

// iterate forward a vector
/// 1. use iterator
for(std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
/// 2. Range C++11
for(auto const& value: a) 	// vector<int> a={1, 2, 3}; value is iterated 1, 2, 3
/// 3. use indices
for(std::vector<int>::size_type i = 0; i != v.size(); i++)



// iterate and erase 怎样边遍历vector边消除元素
for (vector<string>::iter = vec.begin(); iter != vec.end(); /*no iter++*/) {
	if (? ? ? )
		iter = vec.erase(iter);	// must have this "iter ="
	else
		iter++;
}

