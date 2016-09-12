#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<pair<int, int> > maxs;
        vector<int> ans;
        int i;

        //Comment: can get rid of this block by adding if statement in second block
        // get 1st one and save its maxs
        for (i = 0; i < k - 1; i++) {
            // push nums[i]
            while (!maxs.empty() && maxs.back().first <= nums[i]) {
                maxs.pop_back();
            }
            maxs.push_back(make_pair(nums[i], i));
        }

        // i == -1 won't do harm even when nums.size() == (u_int)0, k == 0.
        for (i = k - 1; i < nums.size(); i++) {
            // push nums[i]
            while (!maxs.empty() && maxs.back().first <= nums[i]) {
                maxs.pop_back();
            }
            maxs.push_back(make_pair(nums[i], i)); //Comment: pair.first is redundant
            if (maxs.front().second + k <= i) {
                maxs.pop_front();
            }

            ans.push_back(maxs.front().first);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    // int numsarr[] = {1,3,-1,-3,5,3,6,7};
    // vector<int> nums(numsarr, &numsarr[0]+sizeof(numsarr));
    vector<int> nums {1,3,-1,-3,5,3,6,7};
    vector<int> ans = solution.maxSlidingWindow(nums, 0);

    // print vector
    for (auto const& a : ans)
        cout << a << ' ';
    // http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
    return 0;
}
