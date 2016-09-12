#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;


class Solution {
public:
    int coinChange(const vector<int>& coins, int amount) {
        // f[amount][i] = min(f[amount - coins[i]*k][i-1] + k)

        int i, j;
        // init
        vector<int> f(amount + 1, amount << 1);
        f[0] = 0;
        for (auto & c: coins) { // Comment: coins[i] -> c accelerates solution from 156ms to 104ms.
            // for (j = 0; j <= amount; ++j) cout << f[j] << ' ';
            // cout << endl;
            for (j = 0; j + c <= amount; ++j) {
                f[j + c] = min(f[j + c], f[j] + 1);
            }
        }
        if (f[amount] > amount) return -1;
        return f[amount];
    }
};


// It avoids calculating all combination of amount and coins,
// but due to recursion, it is slower.
class Solution2 {
    vector<vector<int> > f;
    static const int *coinsptr;
    int noSolution;

    int dfs(int amount, int i) {
        if (amount < 0 || i < 0) return noSolution;
        if (f[i][amount] == -2) {
            f[i][amount] = min(dfs(amount - coinsptr[i], i) + 1, dfs(amount, i - 1));
        }
        return f[i][amount];
    }

public:
    int coinChange(const vector<int>& coins, int amount) {
        coinsptr = coins.data();
        noSolution = (amount + 1) << 1;
        f.resize(coins.size(), vector<int>(amount + 1, -2) );
        for (auto &a: f) a[0] = 0;
        int ans = dfs(amount, coins.size() - 1);

        // for (int i = 0; i < coins.size(); ++i) {
        //     for (int j = 0; j <= amount; ++j) cout << f[i][j] << ' ';
        //     cout << endl;
        // }

        if (ans < noSolution) return ans;
        else return -1;
    }
};

const int * Solution2::coinsptr;


// This is a solution to calculate the number of ways
// #ways: f[amount][i] = sum(f[amount - coins[i]*k][i-1])
class Solution4 {
public:
    int coinChange(const vector<int>& coins, int amount) {

        int i, j;
        // init
        vector<int> f(amount + 1, 0);
        f[0] = 1;
        for (i = 0; i < coins.size(); ++i) {
            for (j = 0; j + coins[i] <= amount; ++j) {
                f[j + coins[i]] += f[j];
            }
        }

        return f[amount];
    }
};

int main() {
    Solution solution;
    cout << solution.coinChange(vector<int> {1, 2, 5}, 11);

    return 0;
}
