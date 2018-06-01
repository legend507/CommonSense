/*
Google Interview Question

Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
1->4->5,
1->3->4,
2->6
]
Output: 1->1->2->3->4->4->5->6
*/
#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<algorithm>
#include	<set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {


public:
	/*下面方法是我自己的，但是只beat了2%...，需要想一个更好的方法*/
	int findMinIndex(vector<ListNode*>& lists) {
		int ret = -1;
		int size = lists.size();

		for (int i = 0; i < size; i++) {
			if (lists[i] == NULL)	continue;

			if (ret == -1 || lists[ret]->val > lists[i]->val) ret = i;
		}
		return ret;
	}
	/*
	入口函数*/
	ListNode * mergeKLists_slow(vector<ListNode*>& lists) {
		ListNode* ret = new ListNode(-1);	// insert a dummy node, remeber to delete this!!!
		ListNode* curNode = ret;

		int size = lists.size();
		int count = 0;			// how many lists reached the end

		for (auto ptr : lists) {
			if (ptr == NULL) count++;
		}

		while (count < size) {
			int minIdex = findMinIndex(lists);

			curNode->next = new ListNode(lists[minIdex]->val);
			curNode = curNode->next;

			lists[minIdex] = lists[minIdex]->next;

			if (lists[minIdex] == NULL)	count++;
		}

		return ret->next;
	}

	/////////////////////////////////////////////////////////////////////
	/*
	下面方法是别人的，
	每次merge 2个list，beat 20%左右，但还是不完美...
	*/
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL)	return l2;
		if (l2 == NULL) return l1;

		ListNode* ret = new ListNode(-1);
		ListNode* curNode = ret;

		while (l1 != NULL && l2 != NULL) {
			if (l1->val <= l2->val) {
				curNode->next = new ListNode(l1->val);
				l1 = l1->next;
			} 
			else {
				curNode->next = new ListNode(l2->val);
				l2 = l2->next;
			}
			curNode = curNode->next;
		}

		while (l1 != NULL) {
			curNode->next = new ListNode(l1->val);
			l1 = l1->next;
			curNode = curNode->next;
		}
		while (l2 != NULL) {
			curNode->next = new ListNode(l2->val);
			l2 = l2->next;
			curNode = curNode->next;
		}
		ListNode* temp = ret->next;
		delete ret;
		return temp;
	}
	ListNode * mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty())	return nullptr;

		while (lists.size() > 1) {
			lists.push_back(mergeTwoLists(lists[0], lists[1]));
			lists.erase(lists.begin());
			lists.erase(lists.begin());
		}

		return lists[0];
	}

};

int main() {



	Solution s;
	
	system("pause");
	return 0;

}
