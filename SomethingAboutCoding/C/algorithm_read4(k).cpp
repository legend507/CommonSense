/*
Google Interview Qs
下面的第一个class只能support一次read，
support多次read的情况见下面第二个class

Read N Characters Given Read4
  Go to Discuss
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Example 1:

Input: buf = "abc", n = 4
Output: "abc"
Explanation: The actual number of characters read is 3, which is "abc".
Example 2:

Input: buf = "abcde", n = 5 
Output: "abcde"
Note:
The read function will only be called once for each test case.
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        char* myBuf = new char[4];  // read4 put data inthis myBuf
        int ret = 0;
        bool endOfFile = false;
        
        while( !endOfFile && ret < n) {
            int bytes = read4(myBuf);
            if(bytes < 4) endOfFile = true; // if return of read4 is NOT 4, then EOF
            
            for(int i = 0; i < bytes && ret < n; i++)
                buf[ret++] = myBuf[i];
            
        }

        // Do not forget to delete the new-ed memory
        delete [] myBuf;

        return ret;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////

/*
下面是我在2018.06.20进行Google Coding Interview时的面试题，
面试的时候感觉自己给的answer不是非常好，下面是一个标准答案，
虽然还是read4的，但是同样思想可以用来解决read4K

Given a class 
class Read4K {
	public:
	Read4K(const char* path);
	int Read4K();
}

implement another class using this class
class ArbitraryRead {
	public:
	ArbitraryRead(const char* path);
	int read(int n);	// n is # of bytes I want to read
}

Implement this class.
下面的方法是上面的改进版，可以对应arbitraryRead
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    queue<int> left;    // 用来存储上次都剩下的bytes
    int read(char *buf, int n) {
        int len = 0;
        int c;

        // 先把上次都剩下的放到buf里面
        while (left.size() > 0) {
            buf[len++] = left.front();
            left.pop();
            if (len == n) return len;   // 如果此时，len刚好等于n，则返回
        }
        
        // 用read4读新的bytes，如果read4的返回值<4，则到eof了
        while (len < n) {
            c = read4(buf+len); // 直接往input parameter的buf里面放，省去了new和delete，这点值得参考
            len += c;
            if (c < 4) break;
        }
        
        // 如果len > n，说明读的太多；需要把多出来的部分push到queue里面，
        for (int i=n; i<len; i++) {
            left.push(buf[i]);
        }

        // 然后把n的位置放上/0，这里值得商榷，如果buf只有n的size呢？...
        int e = min(len, n);
        buf[e] = '\0';
        return e;
    }
};