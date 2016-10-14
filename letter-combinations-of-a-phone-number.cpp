#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    static vector<string> mapping;
    vector<string> ans;
    int len;
    void backtrace(const string &digits, int i, string &str) {
        if (len == i) { ans.push_back(str); return; }
        int digit = digits[i] - '0';
        for (auto ch: mapping[digit]) {
            str[i] = ch;
            backtrace(digits, i+1, str);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        ans.clear();
        len = digits.size();
        if (len > 0) {
            string str(len, ' ');
            backtrace(digits, 0, str);
        }
        return ans;
    }
};
vector<string> Solution::mapping {"", "","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

int main() {
    Solution solution;
    for (const auto &str: solution.letterCombinations("23") ) cout << str << ','; cout << endl;
    return 0;
}
