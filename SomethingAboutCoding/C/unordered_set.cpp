#include	<unordered_set>
#include	<iostream>
#include	<string>
using namespace std;

int main() {
	unordered_set<string> stringSet;

	// 添加新元素的方法
	stringSet.insert("fuck");
	stringSet.insert("fucker");
	stringSet.insert("fuckest");

	string key = "fun";
	// 查找元素是否存在的方法
	if (stringSet.find(key) == stringSet.end()) {
		cout << key << " not found" << endl;
	}
	else {
		cout << key << " found" << endl;
	}

	// 遍历方法
	for (unordered_set<string>::iterator itr = stringSet.begin(); itr != stringSet.end(); itr++) {
		cout << *itr << endl;
	}

	// 同样的元素在插一次会发生啥？ 经实验验证，啥都不发生，同样的元素只能存在一个
	stringSet.insert("fuck");	// 虽然fuck插了两次，但是下面的cout仍然只打印一个fuck

	// 遍历方法
	for (unordered_set<string>::iterator itr = stringSet.begin(); itr != stringSet.end(); itr++) {
		cout << *itr << endl;
	}

	system("pause");
	return 0;
}

/*
unordered_set简单来说就是一个没有value的 unordered_map
*/
