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
    static const int k = 10;
    int count[k], a[k];
public:
    int findDuplicate(const vector<int>& nums) {
        // requires that !nums.empty

        int start, end, len, len1;
        start = 1; end = nums.size() - 1; len = nums.size() - 1;
        int i;
        while (len > 1) { // length of [start, end]
            // cout << start << ',' << end << endl;

            // Divide [start, end] into k ranges,
            // each with len except that the last with len1
            // When length < k, the last few count[i] will be 0.
            len = (end - start) / k + 1;
            count[0] = 0; a[0] = start;
            for (i = 1; i < k; ++i) {
                count[i] = 0; a[i] = a[i - 1] + len;
            }
            len1 = max(0, end + 1 - a[k - 1]);

            // length = end - start + 1
            // Put >length eles into k drawers which can at most hold length
            // distinct eles. B/c only one duplicate, there must be exactly
            // one drawer holding more than len(1) eles.

            // count by range
            for (const auto &num: nums) {
                if (num < start || num > end) continue;
                ++count[(num - start) / len];
            }
            if (count[k - 1] > len1) {
                start = a[k - 1];
                len = len1;
            } else {
                for (i = 0; i < k - 1; ++i) {
                    if (count[i] > len) {
                        start = a[i]; end = a[i] + len - 1;
                        break;
                    }
                }
            }
        }

        return start;
    }
};


int main() {
    Solution solution;
    cout << solution.findDuplicate(vector<int> {4,5,7,3,6,5,1,2,5}) << endl;
    cout << solution.findDuplicate(vector<int> {4,5,7,3,6,5,1,2,5,9,10,11,12,13,14,15}) << endl;

    return 0;
}
