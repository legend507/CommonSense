#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, int> hash;		// 也可以声明 unordered_map<string, int> hash, 然后用 hash["test"]　＝　１０ 来添加新元素，另一种添加方式是 hash.insert(make_pair("test",10));
    hash[4] = 1;
    hash[6] = 9;
    hash[20] = 12;
    hash[10] = 11;

	// 注意，必须要用iterator和first,second关键字来获得hash表内数据
    for (auto it = hash.begin(); it != hash.end(); it++) {
        cout << " " << it->first << ":" << it->second;
    }
    cout <<endl;
    cout << "# of buckets: " << hash.bucket_count() << endl;
    for(unsigned i = 0; i < hash.bucket_count(); i++) {
        cout << "bucket #" << i << " contains:";
        for (auto local_it = hash.begin(i); local_it != hash.end(i); local_it++) {
            cout << " " << local_it->first << ":" << local_it->second;
        }
        cout << endl;
    }

	// 查看某一元素是否在hash表内方法
    if(hash.find(4) != hash.end()) {
        cout << "found 4@ " << hash[4] << endl;
    }
    if(hash.find(1) != hash.end()) {
        cout << "found 1@ " << hash[1] << endl;
    }

    return 0;
}

/************************************************
Output:
*************************************************
 10:11 20:12 6:9 4:1
# of buckets: 5
bucket #0 contains: 10:11 20:12
bucket #1 contains: 6:9
bucket #2 contains:
bucket #3 contains:
bucket #4 contains: 4:1
found 4@ 1

*************************************************
説明：
unordered_map是一个hash表，上例中元素是『key：content』；unordered_map根据key值决定把元素放在哪（顺序不定）；一个key值只能对应一个content
查找的时候需要按key值查找
可以当成是一个简易数据库
*/