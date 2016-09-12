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
    string simplifyPath(string path) {
        if (path.size() == 0) return "";

        if (path[path.size() - 1] != '/') path.append(1, '/');

        vector<string> dirs;
        int i, j;
        // path[0] == '/'
        for (i = 1; i < path.size(); ++i) {
            // find next '/' to get cur dir
            j = i - 1;
            while (path[++j] != '/') {}
            const string &dir = path.substr(i, j - i);
            i = j;

            if (dir == "." || dir == "") continue;
            else if (dir == "..") {
                if (!dirs.empty()) dirs.pop_back();
            } else dirs.push_back(dir);
        }
        if (dirs.size() == 0) return "/";
        string ans;
        for (auto & dir: dirs) {
            ans.append("/" + dir);
        }
        return ans;
    }
};


int main() {
    Solution solution;
    cout << solution.simplifyPath("/home/") << endl;
    cout << solution.simplifyPath("/a/./b/../../c/") << endl;
    cout << solution.simplifyPath("/./b/c/../../..") << endl;
    cout << solution.simplifyPath("/////") << endl;

    return 0;
}
