/*
Google Interview Qs

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