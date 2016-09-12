#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // end with i, f -> max, g -> min
        // f[i] = max{f[i-1]*a[i], g[i-1]*a[i], a[i]}
        // g[i] = min{f[i-1]*a[i], g[i-1]*a[i], a[i]}
        int f, g;
        f = nums[0];
        g = nums[0];
        int ans = f;
        int t1, t2;
        for (int i = 1; i < nums.size(); i++) {
            t1 = f * nums[i];
            t2 = g * nums[i];
            f = max(t1, t2);
            f = max(nums[i], f);
            g = min(t1, t2);
            g = min(nums[i], g);
            if (ans < f) ans = f;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> nums { 0, -1, -1};// {1,3,-1,-3,5,3,6,7};
    int ans = solution.maxProduct(nums);
    cout << ans;
    // print vector
    // for (auto const& a : ans)
    //     cout << a << ' ';
    return 0;
}
