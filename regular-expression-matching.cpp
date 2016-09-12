#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>

using namespace std;

class Solution {
    vector<pair<char, bool> > pp;
    inline bool matchChar(char s, char p) {
        return (p == '.' || p == s);
    }

public:

    // I always enjoy working on DP problems in a loop way
    bool isMatch(string s, string p) {
        if (p.size() == 0) {
            return (s.size() == 0);
        }

        // parse p -> pp: a, ., a*, .*
        int i;
        pp.clear();
        for (i = 0; i < p.size() - 1; i++) {
            if (p[i + 1] == '*') {
                pp.push_back(make_pair(p[i], true));
                i++;
            } else pp.push_back(make_pair(p[i], false));
        }
        if (i == p.size() - 1) pp.push_back(make_pair(p[i], false));


        // f[i][j]: s[:i] match pp[:j]

        vector<vector<bool> > f(s.size() + 1, vector<bool>(pp.size() + 1, false) ); // init
        f[0][0] = true;
        // f[i][0] = false, if i > 0

        int j;
        for (j = 1; j <= pp.size(); j++) {
            // i == 0
            if (pp[j-1].second) {
                f[0][j] = f[0][j-1];
            }

            for (i = 1; i <= s.size(); i++) {
                if (pp[j-1].second) {
                    f[i][j] = f[i][j-1] || (matchChar(s[i-1],pp[j-1].first) && f[i-1][j]);
                } else {
                    // pp[j-1].first must match s[i-1]
                    f[i][j] = f[i-1][j-1] && matchChar(s[i-1],pp[j-1].first);
                }
            }
        }

        // for (const auto &a: f) {
        //     for (const auto &b: a) {
        //         cout << b << ' ';
        //     }
        //     cout << endl;
        // }

        return f[s.size()][pp.size()];
    }

};


class Solution1 { // 588ms, beats only 14.38%
public:

    // easy DFS
    bool isMatch(string s, string p) {
        if (p.size() == 0) {
            return (s.size() == 0);
        } else if (p.size() == 1) {
            if (s.size() == 1) {
                return (p[0] == '.') || (p[0] == s[0]);
            } else return false;
        } else {
            // get a char
            if (p[0] == '*') return false;// pattern invalid
            if (p[1] == '*') {
                // match p[0] zero times
                bool ans = isMatch(s, p.substr(2)); // ""??
                if (ans) return ans;

                // match p[0]
                ans = false;
                if (s.size() != 0 && (s[0] == p[0] || p[0] == '.') ) {
                    ans = isMatch(s.substr(1), p);
                }
                return ans;
            } else {
                bool ans = false;
                if (s.size() != 0 && (s[0] == p[0] || p[0] == '.' ) ) {
                    ans = isMatch(s.substr(1), p.substr(1));
                }
                return ans;
            }
        }

    }

    // optimize: move ptr instead of copy substring
    // use memory can save significant time, and that makes it DP
    // https://discuss.leetcode.com/topic/50570/4ms-c-dp-to-eliminate-duplicate-calls
};


int main() {
    Solution solution;
    cout << solution.isMatch("aa","a") << endl;
    cout << solution.isMatch("aa","aa") << endl;
    cout << solution.isMatch("aaa","aa") << endl;
    cout << solution.isMatch("aa", "a*") << endl;
    cout << solution.isMatch("aata", ".*") << endl;
    cout << solution.isMatch("aab", "c*a*b") << endl;
    cout << solution.isMatch("", "c*a*") << endl;
    cout << solution.isMatch("", "") << endl;
    cout << solution.isMatch("", "crt") << endl;
    cout << solution.isMatch("crt", "") << endl;

    return 0;
}
