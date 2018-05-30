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


/*当需要用unordered_map放pair或自定义data struct时，需要定义一个hash func给unordered_map*/
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

using namespace std;
using Vote = pair<string, string>;
// 这里，key是Vote型的自定义struct，需要提供pair_hash计算方法
using Unordered_map = unordered_map<Vote, int, pair_hash>;

/////////////////////////////////////////////////////////////////////////
// 上面的例子有些不太好懂，参考下面的自定义key for unordered_map
/////////////////////////////////////////////////////////////////////////
#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
using namespace std;

struct MyStruct {
	string val1;
	int val2;
	pair<int,int> val3;

    // constructor
	MyStruct(string v1, int v2, pair<int, int> v3) : val1(v1), val2(v2), val3(v3) {};

    // 需要1，
    //  一个判断MyStruct相等的operator overload，MyStruct被当作unordered_map的Key值时，需要判断两个Key值是否相等的时候用
	bool operator == (const MyStruct& another) const {
		return (val1 == another.val1 && val2 == another.val2 && val3 == another.val3);
	}

    // 这个并不是必须，只是为了cout的时候好看而已
	friend ostream& operator << (ostream& stream, const MyStruct& ms) {
		stream << ms.val1 << "." << ms.val2 << ".(" << ms.val3.first << "," << ms.val3.second << ")";
		return stream;
	}

};

// 需要2，
//  unordered_map会用std::hash函数来计算Key的hash value，我需要定义一个hash方法来计算MyStruct的hash
//  可以定义在namespace std中，也可以定义在外面，差别不明(T.B.D)
//namespace std {
    template <>
    struct hash<MyStruct> {
        size_t operator () (const MyStruct& ms) const {
            auto h1 = hash<string>{}(ms.val1);
            auto h2 = hash<int>{}(ms.val2);
            auto h3 = hash<int>{}(ms.val3.first);
            auto h4 = hash<int>{}(ms.val3.second);

            // simple XOR, just for display purpose, NOT a good hash func
            return (h1^h2^h3^h4);

        }
    };
//}


class Codec {
public:

	int func() {
		unordered_map<MyStruct, int> test;

		MyStruct ms1("name", 1, make_pair(3,4));

		test[ms1] = 10;

		for (auto i = 0; i < test.bucket_count(); i++) {
			for (auto iter = test.begin(); iter != test.end(); iter++) {
				cout << iter->first << ":" << iter->second << endl;
			}
		}

		return 0;
	}

};

int main() {
	Codec codec;

	codec.func();

	system("pause");
	return 0;

}

