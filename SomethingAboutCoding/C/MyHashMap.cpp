/*
下面是一个 MyHashMap Class
构造是 有20个Bucket，根据Key值算出Bucket，然后往Bucket里面加元素
用的是operator overload[]
*/

#include <string>
#include <iostream>
using namespace std;

//template for generic type
template<typename K, typename V>
struct HashNode {
	K key;
	V value;
	HashNode* next;

	//Constructor of hashnode 
	HashNode(K key, V value) : key(key), value(value), next(NULL) {};
};

//template for generic type
template<typename K, typename V>

//Our own Hashmap class
class HashMap
{
	//hash element array
	HashNode<K, V> **arr;
	int capacity;
	//current size
	int size;

public:
	HashMap()
	{
		capacity = 20;
		size = 0;
		arr = new HashNode<K, V>*[capacity];	// keyIndex = 0~19

												//Initialise all elements of array as NULL
		for (int i = 0; i < capacity; i++)	arr[i] = NULL;
	}

	/*operator overload, to get value of given key*/
	V& operator[] (K key) {
		int keyIndex = calcKeyIndex(key);

		// if current chain list empty,
		//	make a new node and return
		if (arr[keyIndex] == NULL) {
			arr[keyIndex] = new HashNode<K, V>(key, 0);
			return arr[keyIndex]->value;
		}

		// if current chain list not empty,
		HashNode<K, V> *nodePtr = arr[keyIndex];
		HashNode<K, V> *lastNode = nodePtr;
		// traverse this chain list to see if key exist
		while (nodePtr != NULL) {
			// found key
			if (nodePtr->key == key)
				return nodePtr->value;
			// if not found, move node ptr along chain list
			lastNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// if not found key, make a new node (behind last node) and initialize value to be 0
		lastNode->next = new HashNode<K, V>(key, 0);

		return lastNode->next->value;
	}

	/*ONLY consider integer for now!!!*/
	int calcKeyIndex(int key) {

		return key % capacity;
	}
	int calcKeyIndex(string key) {

		return key.size() % capacity;
	}
	int calcKeyIndex(char key) {

		return (int)key % capacity;
	}

	void display() {
		for (int i = 0; i < capacity; i++) {
			cout << i << ": ";
			HashNode<K, V> *nodePtr = arr[i];
			while (nodePtr != NULL) {
				cout << nodePtr->key << "(" << nodePtr->value << "),  ";
				nodePtr = nodePtr->next;
			}
			cout << endl;
		}
	}
};

//Driver method to test map class
int main()
{
	HashMap<int, int> hm;

	hm[10] = 10;
	cout << hm[10] << endl;

	hm[10] = 9;
	cout << hm[10] << endl;

	hm[30] = 30;
	cout << hm[30] << endl;

	hm[30] = 29;
	cout << hm[30] << endl;

	HashMap<string, int> hmString;
	hmString["f*ck"] = 10;
	hmString["u"] = 1;
	hmString["twice"] = 11;
	hmString["1234"] = 10;
	hmString.display();

	system("pause");
	return 0;
}