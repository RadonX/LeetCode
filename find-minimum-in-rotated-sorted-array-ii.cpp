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

// Comment: I like this idea.
// skip the duplicate from high to reduce to problem https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// while (end > 0 && nums[end] == nums[start]) --end;
// mine is too fancy. 
class Solution {
public:
    int findMin(const vector<int>& nums) {
        const int k0 = 2;
        int k, range, len;
        int start = 0, end = nums.size() - 1; // >= 0
        int s, t;
        k = k0;
        while (end - start > 1) {
            // cout << start << ',' << end << ';';
            len = end - start + 1; // > 2
            do {
                range = (len - 2)/ k + 1;
                k <<= 1;// ++k;

                s = start; t = s + range;
                // if (nums[s] < nums[t])
                if (nums[start] < nums[end]) return nums[start];
                for (; s <= end && s < t; s = t, t = min(s + range, end) ) {
                    if (nums[s] > nums[t]) {
                        start = s + 1; end = t; k = k0; break;
                    }
                    // == provides no info.
                    // < suggests that there is previous > one.
                }
                if (range == 1 && k != k0) return nums[start];
            } while (k != k0); // all nums[sample] equals

        }
        return min(nums[start], nums[end]);

    }
};

int main() {
    Solution solution;
    cout << solution.findMin(vector<int> {4,5,6,7,0,1,2}) << endl;
    cout << solution.findMin(vector<int> {4}) << endl;
    cout << solution.findMin(vector<int> {0,0,0,0,0,0,0,0,0,0}) << endl;
    cout << solution.findMin(vector<int> {1,1,2,2,3,3,4,4,5,5,6,6}) << endl;
    cout << solution.findMin(vector<int> {6,7,2,2,2,3,4,5,6,6}) << endl;
    cout << solution.findMin(vector<int> {6,7,2,3,4,5,6,6}) << endl;
    return 0;
}
