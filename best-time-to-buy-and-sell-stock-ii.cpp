#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int ans = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i-1]) {
                ans += prices[i] - prices[i-1];
            }
        }
        return ans;

    }
};

int main() {
    Solution solution;
    vector<int> nums {3,2,1,5,6,4};// {1,3,-1,-3,5,3,6,7};
    int ans = solution.maxProfit(nums);
    cout << ans << endl;
    // for (const auto& a: nums) {
    //     cout << a << ' ';
    // }
    return 0;
}
