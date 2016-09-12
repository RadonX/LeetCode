#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;

class Solution {

    vector<string> ans;
    int len;

    void getOperators(string &num, int target, int i, const string &opers) {
        if (i == 0) {
            if (target == 0) {
                ans.push_back(opers);
            }
            return;
        }

        for (int j = i - 1; j >= 0; j--) {
            for (auto a: getProducts(num, j, i)) {
                getOperators(num, target + a.first, j, "+" + a.second + opers);
                getOperators(num, target - a.first, j, "-" + a.second + opers);
            }
        }
        // f[i, target]: f[ii, t1] + getProduct( +/-(target-t1) )


    }

public:
    vector<string> addOperators(string num, int target) {
        ans.clear();

        len = num.size();

        vector<vector<vector<string> > > f(10, vector<vector<string> >(11) ); // init

        getOperators(num, target, num.size(), "");

    }
};

int main() {
    Solution solution;

    return 0;
}
