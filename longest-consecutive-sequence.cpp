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
    int ans;
    unordered_map<int, pair<int, int> > subsets; // num -> parent, size

    int find(int num) { // with path compression
        // requirement: subsets[num] exists
        if (subsets[num].first != num) {
            subsets[num].first = find(subsets[num].first); // only size at root is correct
        }
        return subsets[num].first;
    }

    inline void Union(int x, int y) {
        // requirement: subsets has x and y
        int xRoot = find(x);
        int yRoot = find(y);
        // union by size
        if (subsets[xRoot].second <= subsets[yRoot].second) {
            subsets[xRoot].first = yRoot;
            subsets[yRoot].second += subsets[xRoot].second;
            ans = max(ans, subsets[yRoot].second);
        } else {
            subsets[yRoot].first = xRoot;
            subsets[xRoot].second += subsets[yRoot].second;
            ans = max(ans, subsets[xRoot].second);
        }

    }

    inline void insert(int num) {
        if (subsets.find(num) == subsets.end()) {
            // new element
            subsets[num] = make_pair(num, 1);
            if (subsets.find(num - 1) != subsets.end()) Union(num, num - 1);
            if (subsets.find(num + 1) != subsets.end()) Union(num, num + 1);
        }
    }

public:
    int longestConsecutive(const vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        ans = 1;
        subsets.clear();
        for (const auto & num: nums) insert(num);
        return ans;
    }
};


int main() {
    Solution solution;
    cout << solution.longestConsecutive(vector<int> {100, 4, 200, 1, 3, 2}) << endl;
    cout << solution.longestConsecutive(vector<int> {2,4,6,7,5,3,1}) << endl;
    cout << solution.longestConsecutive(vector<int> {0,0,1,-1}) << endl;
    cout << solution.longestConsecutive(vector<int> {0}) << endl;
    return 0;
}
