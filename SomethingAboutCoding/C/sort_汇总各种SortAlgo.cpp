/*
下面有各种Sort算法的实装
1. insertion sort
2. selection sort
3. heap sort
4. bucket sort
5. counting sort
6. quick sort
7. merge sort
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

class Sorter {
public:
	/*
	1. 插入排序法，insertion sort
	想法是，从前往后依次看每个数，比较这个数与其前面所有数，把这个数查到最适合的位置
	当看i时，我能确定0～i-1都是按大小摆好的，我只需要找到把i查到那
	O(n^2)*/
	int insertionSort(vector<int>& arr) {
		for (int i = 1; i < arr.size(); i++) {
			int key = arr[i];
			int ii = i - 1;		// from i-1 to 0, compare one by one

			/*看所有i之前的数，如果大于key，则把那个数往后移一位*/
			while (ii >= 0 && arr[ii] > key) {
				arr[ii + 1] = arr[ii];
				ii = ii - 1;
			}
			arr[ii + 1] = key;
		}
		return 0x00;
	}

	/*
	2. 选择排序，selectin sort
	想法是，从i=0开始，每次找到i+1~end中最小的数，然后交换这个数和arr[i]]
	(0～i就可以想象为sorted region，i+1～end是unsorted region)
	O(n^2)
	*/
	int selectionSort(vector<int>& arr) {
		int size = arr.size();
		for (int i = 0; i < size - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < size; j++) {
				if (arr[j] < arr[minIndex])
					minIndex = j;
			}
			swap(arr[minIndex], arr[i]);
		}
		return 0x00;
	}

	/*
	3. heap sort
	O(nLogn)
	想法是将arr考虑成一个Tree，
	先用heapify将array转化成node其child大的tree
	然后将root和arry最后一个元素交换，之后移除最后一个元素（aka就是把最大的元素移除）
	循环，直到所有元素都移除
	e.g.,arr = { 64, 25, 12, 22, 26 };时，
		tree是
				64
				/\
			  25  12
			  /\
			22	26*/
	int heapSort(vector<int>& arr) {
		int size = arr.size();
		/*这一步之后，e.g.,中的tree变成以下
		目的是确保每个node都要比其child大（root是最大的）
				64
				/\
			  26  12
			  /\
			22	25*/
		for (int i = size / 2 - 1; i >= 0; i--)
			heapify(arr, i, size);

		for(int i = size-1; i >= 0; i--) {
			swap(arr[0], arr[i]);		// 交换最大的root和最后一个元素
			heapify(arr, 0, i);			// 移除最后一个元素，之后对0～size-1在进行heapify操作，确保每个node都要比其child大
		}
		return 0x00;
	}
	int heapify(vector<int>& arr, int i, int size) {
		/*
					0
				/		\
			  1			2
			/\			/\
			3 4			5 6
		以下的max，left，right是用vector index的方式表示一个binary tree*/
		int max = i;			// 0 1 2	<- root
		int left = 2 * i + 1;	// 1 3 5	<- left
		int right = 2 * i + 2;	// 2 4 6	<- right
		///
		if (left < size && arr[left] > arr[max]) max = left;
		///
		if (right < size && arr[right] > arr[max]) max = right;
		///
		if (max != i) {
			swap(arr[i], arr[max]);		// 如果子节点大于父节点，则swap父子
			heapify(arr, max, size);	// 交换之后，看以前父节点（现在子节点）的新子节点
		}
		return 0x00;
	}

	/*
	4. Bucket sort
	Best: O(n+k)	Worst: O(n^2)
	用处：Bucket sort is mainly useful when input is uniformly distributed over a range.
	举例就是，当arr中都是小数，且都在0.0~1.0之中时，用bucket sort
	其他情况不要用！！！
	*/
	int bucketSort(vector<int>& arr) {
		int len = arr.size();

		// 1. create buckets
		vector<int>* bucket = new vector<int>[len];

		// 2. put arr into bucket
		for (int i = 0; i < len; i++) {
			int index = arr[i] * len;	//<-  这一行需要按照input array来redesign
			bucket[index].push_back(arr[i]);
		}

		// 3. sort each individual bucket
		for (int i = 0; i < len; i++)
			sort(bucket[i].begin(), bucket[i].end());

		// 4. concatenate all buckets 
		int index = 0;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < bucket[i].size(); j++)
				arr[index++] = bucket[i][j];
		}
		return 0x00;
	}

	/*
	5. counting sort
	O(n+k)
	想法是，先算出每个元素的出现回数(元素排列从小到大)
	然后再从元素小到大遍历，按这个顺序把元素放到返回arr中
	用处，当元素有明确范围（比如说char0～255）时可用这个sort
	其他时候没啥用
	*/
	int countingSort(vector<char>& arr) {
		int size = arr.size();
		vector<char> sortedArr(arr.size());

		// 因为char型只能存0～255
		int count[255 + 1] = { 0 };
		
		// 数arr中每个char的出现回数
		for (int i = 0; i < size; i++)
			count[arr[i]] ++;

		// 转化成sortedArr的index？
		for (int i = 1; i <= 255; i++)
			count[i] += count[i - 1];

		for (int i = 0; i < size; i++) {
			sortedArr[count[arr[i]] - 1] = arr[i];
			count[arr[i]]--;
		}

		// trivial, 将sortedArr带入回arr
		for (int i = 0; i < size; i++)
			arr[i] = sortedArr[i];

		return 0x00;
	}

	/*
	6. quick sort
	Best: O(nlogn)	Worst:O(n^2)
	就是选pivot，先把这个pivot放对位置，然后看前后两个subArr*/
	int quickSort(vector<int>& arr) {
		int low = 0;
		int high = arr.size()-1;

		quickSortRecurse(arr, low, high);

		return 0x00;
	}
	int quickSortRecurse(vector<int>& arr, int low, int high) {
		if (low < high) {
			// choose pivot
			int pivot = partition(arr, low, high);

			// separatly sort (low~pivot + 1) and (pivot+1~high)
			//	pivot is already in the correct position
			quickSortRecurse(arr, low, pivot - 1);
			quickSortRecurse(arr, pivot + 1, high);
		}
		return 0x00;
	}
	int partition(vector<int>& arr, int low, int high) {
		/*此函数返回index，并重新排列arr，s.t.所有low～index-1都<=index，所有index+1～high都>index*/

		int pivot = arr[high];	// <- choose last element as pivot
		int nextSmall = low;

		for (int j = low; j <= high - 1; j++) {
			/*依次看low～high-1，如果看到比pivot小的值
			则顺次往前仍*/
			if (arr[j] <= pivot && j != nextSmall) {
				swap(arr[nextSmall], arr[j]);
				nextSmall++;
			}
		}
		swap(arr[nextSmall], arr[high]);	// swap 
		return (nextSmall);		// 可以确保所有low～nextSmall-1的元素都<=nextSmall，nextSmall+1～high的都>nextSmall
	}

	/*
	7. merge sort
	Best: O(nlogn)	Worst: O(nlogn)
	有传言quickSort对Array比较有效，而mergeSort对linkedList比较有效	*/
	int mergeSort(vector<int>& arr) {
		int left = 0; 
		int right = arr.size()-1;

		mergeSortRecurse(arr, left, right);
		return 0x00;
	}
	int mergeSortRecurse(vector<int>& arr, int left, int right) {
		if (left < right) {
			int middle = left + (right - left) / 2;

			/*recurse到最后，就是两个元素的比较*/
			mergeSortRecurse(arr, left, middle);
			mergeSortRecurse(arr, middle + 1, right);

			/*to merge 2 Sorted sub arr (arr[left~middle] and arr[middle+1~right])*/
			merge(arr, left, middle, right);
		}
		return 0x00;
	}
	int merge(vector<int>& arr, int left, int middle, int right) {
		/*此函数merge两个subarray，arr[left~middle] and arr[middle+1~right]*/

		// break arr[left~right] into left, right 2 parts
		vector<int> leftArr;
		for (int i = left; i <= middle; i++)	leftArr.push_back(arr[i]);
		vector<int> rightArr;
		for (int i = middle+1; i <= right; i++)	rightArr.push_back(arr[i]);

		/*
		同时traverse leftArr和rightArr，把比较小的元素放进arr*/
		int leftP = 0;
		int rightP = 0;
		int p = left;	// pointer to arr[left]
		while (leftP < leftArr.size() && rightP < rightArr.size()) {
			if (leftArr[leftP] <= rightArr[rightP])	arr[p++] = leftArr[leftP++];
			else									arr[p++] = rightArr[rightP++];
		}

		/*如果还有余下的元素，也放进arr*/
		while (leftP < leftArr.size())		arr[p++] = leftArr[leftP++];
		while (rightP < rightArr.size())	arr[p++] = rightArr[rightP++];

		return 0x00;
	}
};

int main(int argc, const char * argv[]) {
	vector<int> arr = { 38,27,43,3,9,82,10 };
	vector<char> charArr = { 'g','e','e','k','s','f','o','r','g','e','e','k','s' };
	Sorter s;
	s.mergeSort(arr);

	for (auto oneEle : arr)
		cout << oneEle << " ";

	system("pause");
	return 0;
}
