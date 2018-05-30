/*
Design data structures for a very large social network like Facebook or Linkedln
How would you design the data structures for a very large social network like Facebook or Linkedln? Describe how you would design an algorithm to show the shortest path between two people (e.g., Me-> Bob-> Susan-> Jason-> You).
*/

#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<sstream>			// istringstream and ostringstream
#include	<set>
#include	<climits>
#include	<algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////
class Person {
private:
	int id;
	string name;
	unordered_set<int> friendList;
};

class Machine {
private:
	int mID;	// id of this machine
	unordered_map<int, Person*> personList;	// a list of all persons in this machine
public:
	// if pId is not found on this machine, returll 0x00 (NULL)
	Person* getPersonById(int pId) {
		return personList[pId];
	}
};

class Server {
private:
	// Server should keep a list of all machines
	unordered_map<int, Machine*> machineList;
	// Server should keep a list of which person is on which machine
	unordered_map<int, int>	personToMachine;
public:
	// get a machine& by its id
	Machine* getMachineById(int mId) {
		return machineList[mId];
	}


	// get a person by person Id
	Person* getPersonById(int pId) {
		int machineId = personToMachine[pId];	// which machines is the person on
		Machine* targetMachine = getMachineById(machineId);
		
		if (targetMachine == NULL)	return NULL;
		else return targetMachine->getPersonById(pId);
	}

};

int main() {
	unordered_map<int, Person*> test;
	test[10] = NULL;

	// if a key is not inserted, then value is 0
	Person* a = test[11];
	cout << a;

	system("pause");
	return 0;
}


/*
Optimization: Reduce machine jumps
Jumping from one machine to another is expensive. Instead of randomly jumping from machine to machine with each friend, try to batch this jumps-e.g., if five of my friends live on one machine, I should look them up all at once.

Optimization: Smart division of people and machines
People are much more likely to be friends with people who live in the same country as they do. Rather than randomly dividing people across machines, try to divide them by country, city, state, and so on. This will reduce the number of jumps.

Question: Breadth-first search usually requires “marking” a node as visited. How do you do that in this case?
Usually, in BFS, we mark a node as visited by setting a visited flag in its node class. Here, we don’t want to do that. There could be multiple searches going on at the same time, so it’s a bad idea to just edit our data.

Instead, we could mimic the marking of nodes with a hash table to look up a node id and determine whether it’s been visited.

Other Follow-Up Questions:
1. In the real world, servers fail. How does this affect you?
2. How could you take advantage of caching?
3. Do you search until the end of the graph (infinite)? How do you decide when to give up?
4. In real life, some people have more friends of friends than others and are therefore more likely to make a path between you and someone else. How could you use this data to pick where to start traversing?
*/