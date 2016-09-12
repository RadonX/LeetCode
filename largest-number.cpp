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

    // a > b
    struct {
        bool operator() (const string &a, const string &b) const {
            const char *pa = a.data(), *pb = b.data();
            while (*pa && *pb) {
                if (*pa > *pb) return true;
                else if (*pa < *pb) return false;
                ++pa; ++pb;
            }
            if (*pa || *pb) return (a + b) > (b + a);
            else return false; // equal
        }
    } compare;
    // "ab" > "cd"
    // "abc" < "de"
    // cat: "abc"  "ab"->aba:
    // aba/ab? ab/aba?


public:

    // bucket sort

    string largestNumber(vector<int>& nums) {
        if (nums.size() == 0) return "";
        vector<string> numsStr(nums.size());
        vector<string>::iterator it = numsStr.begin();
        for (auto & num: nums) {
            *it = to_string(num);
            ++it;
        }

        sort(numsStr.begin(), numsStr.end(), compare);
        if (numsStr[0] == "0") return "0";
        string ans;
        for (auto &numstr: numsStr) ans.append(numstr);
        return ans;
    }
};

int main() {
    Solution solution;
    // vector<int> nums {0,0};
    vector<int> nums {3, 30, 34, 5, 9};
    cout << solution.largestNumber(nums);
    return 0;
}
