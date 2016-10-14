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

// https://discuss.leetcode.com/topic/56932/clean-c-0ms-solution-with-comments

class Solution {
    vector<int> left, right;
    vector<int> rdelete;
    int ldelete;
    const char *s;
    int len;
    vector<string> answers;

    void countParentheses(const string &s) {
        // count number of left/right brackets
        left.clear(); left.push_back(0); right.clear(); right.push_back(0);
        int tmpleft = 0, tmpright = 0;
        for (auto ch: s) {
            if (ch == '(') ++tmpleft;
            else if (ch == ')') ++tmpright;
            left.push_back(tmpleft); right.push_back(tmpright);
        }

        // rdelete[i]: the number of ')' that should be deleted before(<) index i
        rdelete.clear();
        int tmp = 0;
        for (int i = 0; i <= len; ++i) {
            if (left[i] < right[i] - tmp) ++tmp;
            rdelete.push_back(tmp); // left[i] >= right[i] - rdelete[i]
            // cout << tmp << ' ';
        }
        // the number of '(' that should be deleted
        ldelete = left[len] - (right[len] - rdelete[len]);
        // cout << endl << ldelete << endl;
    }


    void backtraceWithCur(int i, int rdeleted, bool rpre, int ldeleted, bool lpre, string &ans) {
        ans.push_back(s[i]);
        backtrace(i + 1, rdeleted, rpre, ldeleted, lpre, ans);
        ans.pop_back();
    }
    void backtrace(int i, int rdeleted, bool rpre, int ldeleted, bool lpre, string &ans) {

        if (i == len) {
            if (rdeleted == rdelete[len] && ldeleted == ldelete)
                answers.push_back(ans);
            return;
        }

        // sanity check: rdeleted & ldeleted are in an reasonable range
        // can delete ')' more than rdelete[i]
        // as long as total deleted ')' == rdelete[len - 1]
        if ((rdeleted < rdelete[i]) || (rdeleted > rdelete[len]) || // my trick to avoid unnecessary searches, but not decreasing much time.
            (left[len] - left[i] + ldeleted < ldelete) ||
            (left[i] - ldeleted < right[i] - rdeleted)) // use `state` instead of calculating every time
            return;

        // cout << "state: " << i << ',' << rdeleted << ',' << ldeleted << endl;

        // delete ')' earlier and '(' later
        if (s[i] == ')') {
            backtrace(i + 1, rdeleted + 1, false, ldeleted, true, ans);
            if (rpre) backtraceWithCur(i, rdeleted, true, ldeleted, true, ans);
        } else if (s[i] == '(') {
            backtrace(i + 1, rdeleted, true, ldeleted + 1, false, ans);
            if (lpre) backtraceWithCur(i, rdeleted, true, ldeleted, true, ans);
        } else backtraceWithCur(i, rdeleted, true, ldeleted, true, ans);

    }

public:
    vector<string> removeInvalidParentheses(string s) {
        len = s.size();
        if (len == 0) return vector<string> {""};
        answers.clear();
        this->s = s.data();
        countParentheses(s);
        string str = "";
        backtrace(0, 0, true, 0, true, str);
        return answers;
    }
};

int main() {
    Solution solution;
    for (auto str: solution.removeInvalidParentheses(")(")) cout << str << ','; cout << endl;
    for (auto str: solution.removeInvalidParentheses("(a)())()")) cout << str << ','; cout << endl;
    for (auto str: solution.removeInvalidParentheses("a")) cout << str << ','; cout << endl;
    for (auto str: solution.removeInvalidParentheses("()())()")) cout << str << ','; cout << endl;
    return 0;
}
