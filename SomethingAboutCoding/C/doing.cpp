/*
Google Interview Qs
Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		if (prerequisites.size() == 0) return true;

		unordered_set<int> eliminate;
		unordered_set<int> finishedCourse;
		int finished = 0;

		// after this loop, i can find all finishedCourse course
		for (auto ele : prerequisites) {
			int preCourse = ele.first;
			int course = ele.second;

			finishedCourse.insert(preCourse);
			eliminate.insert(course);
		}
		for (auto ele : eliminate) {
			finishedCourse.erase(ele);
		}

		// how many courses are without prerequests?
		finished = finishedCourse.size();

		while (finished < numCourses) {
			int oldFinished = finished;

			for (auto ele : prerequisites) {
				int preCourse = ele.first;
				int course = ele.second;

				// if prerequisite is finished, then put current course into finishedCourse
				if (finishedCourse.find(preCourse) != finishedCourse.end()) {
					finishedCourse.insert(course);
				}
			}
			finished = finishedCourse.size();
			if (finished == oldFinished) break;
		}

		return (finished == numCourses ? true : false);
	}
};


int main() {
	Solution s;
	vector<pair<int, int>> pre = { {0,1}, {1,0} };

	s.canFinish(2, pre);

	system("pause");
	return 0;

}
