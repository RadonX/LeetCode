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

using namespace std;

// |nums[i] - nums[j]| <= t
// |i - j| <= k
class Solution {

    int k;
    deque<int> maxQ, minQ; // max index difference: k

    template <typename Compare>
    void updateQueue(deque<int> &Q, const vector<int>& nums, int j, Compare cmp) {
        while (!Q.empty() && cmp(nums[Q.back()], nums[j])) Q.pop_back();
        Q.push_back(j);
    }

    inline void removeFromQueue(deque<int> &Q, int j) {
        // requires Q non-empty
        if (Q.front() + k < j) Q.pop_front();
    }

public:
    bool containsNearbyAlmostDuplicate(const vector<int>& nums, int k, int t) {
        if (nums.size() < 2 || k <= 0 || t < 0) return false;

        this->k = k;

        maxQ = deque<int> {0};
        minQ = deque<int> {0};

        int j;
        for (j = 1; j < nums.size(); ++j) {
            removeFromQueue(maxQ, j);
            removeFromQueue(minQ, j);
            // check if nums[j] almost duplicates
            int upperBound = nums[j] + t;
            int lowerBound = nums[j] - t;
            if ((minQ.front() <= upperBound) && (maxQ.front() >= lowerBound))
                return true;
            updateQueue(maxQ, nums, j, less_equal<int>());
            updateQueue(minQ, nums, j, greater_equal<int>());
        }
        return false;

    }
};

int main() {
    Solution solution;
    cout << solution.containsNearbyAlmostDuplicate(vector<int> {0, 1, 2}, 0, 0) << endl;

    return 0;
}
