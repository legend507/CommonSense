/* Problem Name is &&& HashMap &&& PLEASE DO NOT REMOVE THIS LINE. */

#include <iostream>
#include <vector>
#include <list>
#include <string>

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
	MyHashNode(pair<int, int> oneNode) {
		this->value = oneNode.second;
		this->key = oneNode.first;
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
	MyHashNode<K, V> **array;  // * ?
	int capacity;

	MyHashMap()
	{
		capacity = 20;
		array = new MyHashNode<K, V>*[capacity];
		for (int i = 0; i < capacity; i++)
			array[i] = NULL;


	}

	~MyHashMap()
	{
		delete array;
	}

	V operator[](const K& key)
	{
		// todo: implement
		int index = convertKeyToIndex(key);

		while (array[index] != NULL) {
			if (array[index]->key == key) {
				return array[index]->value;
			}
			//
			index++;
			index = index % capacity;

		}

		// if key not found 
		return NAN;
	}

	int convertKeyToIndex(K key) {
		return key % capacity;
	}

	void insertNode(pair<int, int> oneNode) {
		MyHashNode<K, V> *temp = new MyHashNode<K, V>(oneNode);

		int index = convertKeyToIndex(oneNode.first);

		while (array[index] != NULL
			&& array[index]->key != oneNode.second
			) {

			if (index == convertKeyToIndex(oneNode.first)) {
				array[index]->value = oneNode.second;
				break;
			}


			index++;
			index = index % capacity;
		}



		array[index] = temp;

	}


};

void doTestsPass()
{
	const list<pair<int, int>> testCases = { { 1, 2 },{ 3, 4 },{ 5, 6 },{ 1, 7 },{ 1, 8 } };
	const list<pair<string, string>> stringTestCases = { { "one", "two" },{ "three", "four" },{ "one", "five" } };

	MyHashMap<int, int> map;

	MyHashMap<string, string> stringMap;
	bool passed = true;

	//for (const auto test : testCases)
	//{
	//	int key = test.first;
	//	int value = test.second;

	//	map.insertNode(test);

	//	if (value != map[key])
	//	{
	//		passed = false;

	//		cout << "Test case failed [" << key << ',' << value << ']' << endl;
	//	}
	//}

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