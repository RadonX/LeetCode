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
    vector<int> left, right;
public:
    int trap(const vector<int>& height) {
        if (height.size() <= 2) return 0;
        int highest;
        left.resize(height.size());
        right.resize(height.size());

        vector<int>::const_iterator it = height.begin();
        vector<int>::iterator itLeft = left.begin();
        *(itLeft++) = 0;
        highest = *(it++);
        for (; it != height.end(); ++it, ++itLeft) {
            *itLeft = highest;
            highest = max(highest, *it);
        }

        vector<int>::const_reverse_iterator rit = height.rbegin();
        vector<int>::reverse_iterator ritRight = right.rbegin();
        *(ritRight++) = 0;
        highest = *(rit++);
        for (; rit != height.rend(); ++rit, ++ritRight) {
            *ritRight = highest;
            highest = max(highest, *rit);
        }

        int ans = 0;
        for (int i = 1; i < height.size() - 1; ++i) {
            ans += max(0, min(left[i], right[i]) - height[i]);
        }
        return ans;
    }
};


int main() {
    Solution solution;
    cout << solution.trap(vector<int> {100, 4, 200, 1, 3, 2}) << endl;
    cout << solution.trap(vector<int> {2,4,6,7,5,3,1}) << endl;
    cout << solution.trap(vector<int> {0,1,0,2,1,0,1,3,2,1,2,1}) << endl;
    cout << solution.trap(vector<int> {0}) << endl;
    return 0;
}
