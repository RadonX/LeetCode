#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;


// Comment: accelerate from 24ms -> 8ms
// by reverting inner and outter loop and making 2D -> 1D
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) return 0;
        if (s.size() == t.size()) return (s == t);
        if (t.size() == 0) return 1;

        vector<int> f(t.size() + 1, 0);
        f[0] = 1; // f[i][0] = 1

        bool same = true;
        int i, j;
        for (i = 1; i <= s.size(); ++i) {
            if (i <= t.size()) {
                same = same & (s[i - 1] == t[i - 1]);
                f[i] = same;
                j = i - 1;
            } else j = t.size();
            for (; j >= 1; --j) {
                // f[i][j] = f[i - 1][j];
                if (s[i - 1] == t[j - 1]) f[j] += f[j - 1];
            }
        }

        return f[t.size()];
    }
};


class Solution2 {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) return 0;
        if (s.size() == t.size()) return (s == t);
        if (t.size() == 0) return 1;

        // f[i][0] = 1
        //      (s[i - 1] == t[j - 1]) |   -
        // f[i][j] = f[i - 1][j - 1]   +   f[i-1][j], i >= j
        vector<vector<int> > f(s.size() + 1, vector<int>(t.size() + 1, 1));
        bool same = true;
        for (int j = 1; j <= t.size(); ++j) {
            same = same & (s[j - 1] == t[j - 1]);
            f[j][j] = same;
            for (int i = j + 1; i <= s.size(); ++i) {
                f[i][j] = f[i - 1][j];
                if (s[i - 1] == t[j - 1]) f[i][j] += f[i - 1][j - 1];
            }
        }

        return f[s.size()][t.size()];
    }
};


int main() {
    Solution solution;

    cout << solution.numDistinct("rabbit", "rabbit") << endl;
    // cout << solution.numDistinct("rabbbiit", "rabbit") << endl;
    cout << solution.numDistinct("rapfbbpbilit", "rabbit") << endl;

    return 0;
}
