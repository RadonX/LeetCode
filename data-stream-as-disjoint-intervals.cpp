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


struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class SummaryRanges {
    map<int, int> ranges; // RBT
    // alternative: set<pair>
    // http://stackoverflow.com/questions/9843278/c-set-search-for-pair-element
    // http://www.cplusplus.com/reference/algorithm/lower_bound/

public:

    void addNum(int val) {
        map<int,int>::iterator before, after, cur;
        after = ranges.upper_bound(val);
        if (after != ranges.begin()) {
            before = prev(after);
            if (before->first < val) { // <=
                if (before->second >= val) return;
                else { // <
                    if (before->second + 1 == val) {
                        // merge [before, val]
                        before->second = val;
                        cur = before;
                    } else cur = ranges.insert(make_pair(val, val)).first;
                }
            }
        } else {
            cur = (ranges.insert(make_pair(val, val))).first;
        }
        // merge [cur, after]
        if (after != ranges.end() && val + 1 == after->first) {
            cur->second = after->second;
            ranges.erase(after);
        }
        // cout << "size:" << ranges.size() << endl;
    }

    vector<Interval> getIntervals() {
        vector<Interval> ans;
        for (const auto &range: ranges) {
            ans.push_back(Interval(range.first, range.second));
        }
        return ans;
    }
};


int main() {
    SummaryRanges obj;
    obj.addNum(6);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(6);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(0);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(4);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(8);
    for (auto interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(7);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(6);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(4);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(7);
    for (auto & interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;
    obj.addNum(5);
    for (auto interval: obj.getIntervals()) { cout << interval.start << '-' << interval.end << ','; } cout << endl;

    return 0;
}
