/*
总结一下Goldman Sachs面试失败原因，我觉得是因为我花了太多时间在这个问题上，还是C++写的太少，
*/

/* Problem Name is &&& HashMap &&& PLEASE DO NOT REMOVE THIS LINE. */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

/**
* Instructions to candidate.
*  1) Run this code in the REPL to observe its behaviour. The
*     execution entry point is main().
*  2) Consider adding some additional tests in doTestsPass().
*  3) Implement MyHashMap correctly.
*  4) If time permits, some possible follow-ups.
*/

// my hash node 
template<typename K, typename V>
class MyHashNode {
public:
	V value;
	K key;

	// constructor
	MyHashNode(pair<K, V> oneNode) {
		this->value = oneNode.second;
		this->key = oneNode.first;
	}

	MyHashNode(K key, V value) {
		this->value = value;
		this->key = key;
	}
	MyHashNode() {

	}

};


/**
* class MyHashMap
*
* Associates a key-value pair in memory such that lookups
* and inserts can be performed in O(1) time for a reasonably
* small set of data, and scales linearly (at worst) for larger
* sets of key-value pairs.
*
* Each unique key is associated with one single value.
*/
template<typename K, typename V>
class MyHashMap
{
public:
	//private:
	MyHashNode<K, V> **hashMap;  // * ?
	int capacity;

	MyHashMap()
	{
		capacity = 20;
		hashMap = new MyHashNode<K, V>*[capacity];

		for (int idx = 0; idx < capacity; idx++) {
			hashMap[idx] = NULL;
		}
	}

	~MyHashMap()
	{
		for (int idx = 0; idx < capacity; idx++) {
			if (hashMap[idx] != NULL)
				delete hashMap[idx];
		}

		delete[] hashMap;
	}

	V& operator[](const K& key)
	{
		int index = convertKeyToIndex(key);
		if (hashMap[index] == NULL) {
			hashMap[index] = new MyHashNode<K, V>;
		}

		return hashMap[index]->value;
	}

	/*
	to convert key, regardless of int or string, a number ranged 0~199
	*/
	int convertKeyToIndex(K key) {
		stringstream ss;
		ss << key;
		string tmp = ss.str();
		unsigned long var = 0;
		for (int idx = 0; idx < tmp.size(); idx++) {
			var = var << 8;	// move 8 bit left
			var += tmp[idx];
		}

		return var % capacity;
	}
};

void doTestsPass()
{
	const list<pair<int, int>> testCases = { { 1, 2 },{ 3, 4 },{ 5, 6 },{ 1, 7 },{ 1, 8 } };
	const list<pair<string, string>> stringTestCases = { { "one", "two" },{ "three", "four" },{ "one", "five" } };

	MyHashMap<int, int> map;

	MyHashMap<string, string> stringMap;
	bool passed = true;

	for (const auto test : testCases)
	{
		int key = test.first;
		int value = test.second;

		map[key] = value;

		if (value != map[key])
		{
			passed = false;

			cout << "Test case failed [" << key << ',' << value << ']' << endl;
		}
	}

	for (const auto test : stringTestCases)
	{
		string key = test.first;
		string value = test.second;

		stringMap[key] = value;

		if (value != stringMap[key])
		{
			passed = false;

			cout << "Test case failed [" << key << ',' << value << ']' << endl;
		}
	}

	if (passed)
	{
		cout << "All tests passed." << endl;
	}
}

int main() {

	doTestsPass();
	system("pause");
	return 0;
}