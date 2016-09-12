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
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;
        const int nascii = 128;

        int i, pos[nascii], ans = 1;
        // f[i]: starting pos of substr that ends with i, -> [f[i], i]
        int f[s.size()];
        memset(pos, -1, sizeof(int) * nascii);
        f[0] = 0; pos[s[0]] = 0;
        for (i = 1; i < s.size(); ++i) {
            // if substr_i doesn't contain s[i]
            f[i] = max(f[i - 1], pos[s[i]] + 1);
            if (i - f[i] + 1 > ans) ans = i - f[i] + 1;
            pos[s[i]] = i;
        }
        return ans;
    }
};


int main() {
    Solution solution;
    cout << solution.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << solution.lengthOfLongestSubstring("bbbbb") << endl;
    cout << solution.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << solution.lengthOfLongestSubstring("aA::") << endl;

    return 0;
}
