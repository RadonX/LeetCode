// https://leetcode.com/problems/merge-intervals/
// 580ms, 16.91%, 80.53%

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool comp(Interval a, Interval b){
    return (a.start < b.start)? true: (
        (a.start == b.start)? (a.end > b.end? true:false ): false
    );
}

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> res;

        if (intervals.size() == 0) return res;

        sort(intervals.begin(), intervals.end(), comp);

        int st, ed;
        st = intervals[0].start;
        ed = intervals[0].end;
        for (auto& interval : intervals ){

            if (interval.start <= ed){
                if (interval.end > ed) ed = interval.end;
            }else{
                Interval foo(st, ed);
                res.push_back(foo);
                st = interval.start;
                ed = interval.end;
            }
        }
        Interval foo(st, ed);
        res.push_back(foo);

        return res;
    }
};
