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
public:
    int minDistance(string word1, string word2) { // 35ms -> 12ms (vector -> int[][])
        int m = word1.size();
        int n = word2.size();
        if (n == 0) return m; if (m == 0) return n;
        int f[m+1][n+1];
        int i, j;
        for (i = 0; i <= m; ++i) {
            f[i][0] = i;
            for (j = 1; j <= n; ++j) {
                if (i == 0) f[0][j] = j;
                else {
                    f[i][j] = min(f[i-1][j-1] + (word1[i-1] != word2[j-1]),
                            min(f[i][j-1] + 1, f[i-1][j] + 1));
                }
            }
        }
        return f[m][n];
    }
};

int main() {
    Solution solution;
    cout << solution.minDistance("string word1", "string word2") << endl;
    cout << solution.minDistance("firefox", "hireox") << endl;
    cout << solution.minDistance("", "hireox") << endl;
    cout << solution.minDistance("min", "") << endl;
    return 0;
}
