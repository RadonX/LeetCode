#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len < 1) return 0;

        // f[i]: sell <= day i, maxProfit, (one trans if ==)
        // optimize (space): integrate the calculation of f to the
        // loop of that of g. f[] -> f
        int ans = 0; // #trans == 0
        vector<int> f(len);
        int fsell, fbuy;
        // f = 0;
        f[0] = 0;
        fbuy = prices[0];
        fsell = fbuy;
        for (int i = 1; i < len; i++) {
            if (prices[i] > fsell) {
                fsell = prices[i];
            } else if (prices[i] < fbuy) {
                // f = max(f, fsell - fbuy);
                fbuy = prices[i];
                fsell = fbuy;
            }
            f[i] = max(f[i-1],fsell - fbuy);
        }
        // f = max(f, fsell - fbuy);
        ans = f[len - 1];
        if (len < 4) return ans;

        vector<int> gsell(len); // max sell price after(>=) day i
        gsell[len - 1] = prices[len - 1];
        for (int j = len - 2; j >= 2; j--) {
            gsell[j] = max(prices[j], gsell[j+1]);
        }

        // g[i]: buy == day i, maxProfit
        // g[i] = max(p[j]) - p[i], j >= i (no trans if j == i)
        int g = 0;
        for (int i = 2; i <= len - 2; i++) {
            // g -> g[i]
            g = gsell[i] - prices[i];
            ans = max(ans, g + f[i]);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> nums {3,2,1,5,6,4};// {1,3,-1,-3,5,3,6,7};
    int ans = solution.maxProfit(nums);
    cout << ans << endl;
    // for (const auto& a: f) {
    //     cout << a << ' ';
    // }
    // cout << endl;
    return 0;
}
