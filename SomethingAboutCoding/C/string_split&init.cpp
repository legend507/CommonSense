#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main() {
    using namespace std;
    string sentence = "And I feel fine...";
    istringstream iss(sentence);
    
    // method 1
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         ostream_iterator<string>(cout, "\n"));
		 
    // method 2
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
    istream_iterator<string>(),
    back_inserter(tokens));

    // method 3
	vector<string> tokens{istream_iterator<string>{iss},
                      istream_iterator<string>{}};
}

// how to initialized a string with 10 dots: string str(10, '.');