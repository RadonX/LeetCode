#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

class Solution {

    static bool cmpbyw(const pair<int,int> &i, const pair<int,int> &j) {
        if (i.first < j.first) {
            return true;
        }
        else if (i.first == j.first
                && i.second > j.second) { // to parse first higher envelopes with equal width
            return true;
        } else return false;
    }

public:

    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int len = envelopes.size();
        if (len == 0) return 0;

        sort(envelopes .begin(), envelopes .end(), cmpbyw);

        // Longest Increasing Subsequence
        vector<int> f {-1};
        vector<int>::iterator found;
        for (int i = 0; i < len; i++) {
            // f[i]: the max smaller H for an envelope that can russian doll i
            found = lower_bound(f.begin(), f.end(), envelopes [i].second);
            if (found != f.end()) {
                if (envelopes [i].second < *found) {
                    *found = envelopes [i].second;
                }
            } else {
                f.push_back(envelopes [i].second);
            }
        }

        // for (auto const& a : f)
        //     cout << a << ' ';
        // cout << endl;

        return f.size() - 1;

    }
};



int main() {
    Solution solution;
    // vector<pair<int, int>> envelopes = {{5,4},{6,4},{6,7},{2,3}}; // 3
    vector<pair<int, int>> envelopes = {{46,89},{50,53},{52,68},{72,45},{77,81}}; // 3
    // vector<pair<int, int>> envelopes = {{1,3},{3,5},{6,7},{6,8},{8,4},{9,5}}; // 3
    int ans = solution.maxEnvelopes(envelopes);
    cout << ans;

    return 0;
}
