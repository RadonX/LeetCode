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
        int low, high;
        low = prices[0];
        high = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > high) {
                high = prices[i];
            } else if (prices[i] < low) {
                ans = max(ans, high - low);
                low = prices[i];
                high = low;
            }
        }
        ans = max(ans, high - low);
        return ans;

    }
};

int main() {
    Solution solution;
    vector<int> nums {7, 6, 4, 3, 1};// {3,3,7,1,5,6,4};
    int ans = solution.maxProfit(nums);
    cout << ans << endl;
    // for (const auto& a: nums) {
    //     cout << a << ' ';
    // }
    return 0;
}
