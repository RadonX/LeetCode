#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

/*
http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm
http://www.tutorialspoint.com/cplusplus/cpp_interview_questions.htm

https://www.hrwhisper.me/leetcode-tree/
*/

class Solution {
    vector<int> ww, hh; // the index of max envelope that this envelope can hold by w/h
    vector<int> indByW, indByH;
    vector<int> fw, fh;
    int len;

    //http://stackoverflow.com/questions/446296/where-can-i-get-a-useful-c-binary-search-algorithm
    template<class Iter, class T>
    Iter binarySearch(Iter begin, Iter end, T val) {
        // Finds the lower bound in at most log(last - first) + 1 comparisons
        Iter i = lower_bound(begin, end, val);

        if (i != end && !(val < *i)) // val >= *i --> val == *i
            return i; // found
        else
            return end; // not found
    }


    // http://fusharblog.com/3-ways-to-define-comparison-functions-in-cpp/
    // my qsort: http://www.cplusplus.com/reference/algorithm/sort/
    static bool cmphh(int i, int j) {
        if (myenvelopes[i].second < myenvelopes[j].second) {
            return true;
        }
        else if (myenvelopes[i].second == myenvelopes[j].second
                && myenvelopes[i].first < myenvelopes[j].first) {
            return true;
        } else return false;
    }
    static bool cmpww(int i, int j) {
        if (myenvelopes[i].first < myenvelopes[j].first) {
            return true;
        }
        else if (myenvelopes[i].first == myenvelopes[j].first
                && myenvelopes[i].second < myenvelopes[j].second) {
            return true;
        } else return false;
    }

    template <typename Compare>
    void updateQueue(deque<int> &Q, vector<int>& nums, int j, Compare cmp) {
        while (!Q.empty() && cmp(nums[Q.back()], nums[j])) Q.pop_back();
        Q.push_back(j);
    }

public:

    void foo(deque<int> &Q, vector<int>& nums, int j) {
        updateQueue(Q, nums, j, less_equal<int>());
    }

    static vector<pair<int, int>> myenvelopes;
    void sortInd(vector<int> &ind, bool (*cmp)(int, int) ) {
        ind.resize(len);
        for (int i = 0; i < len; i++) {
            ind[i] = i;
        }
        sort(ind.begin(), ind.end(), cmp);
    }

    static bool canContain(int a, int b) {
        return (myenvelopes[a].first > myenvelopes[b].first) && (myenvelopes[a].second > myenvelopes[b].second );
    }

    void findSmallerByInd(vector<int> ind, vector<int> &maxSmaller) {
        maxSmaller.resize(len);
        int i = len - 1, j = len - 2;
        while (j >= 0) {
            if (canContain(ind[i], ind[j]) ) {
                maxSmaller[ind[i]] = ind[j];// the index of max envelope that this envelope can hold.
                cout << ind[i] << '>' << ind[j] << endl;
                i--;
            } else {
                j--;
            }
        }
        while (i >= 0) {
            maxSmaller[ind[i]] = -1;
            i--;
        }
    }

    void normalizeEnvelopes(vector<pair<int, int>>& envelopes) {
        for (auto & envelope : envelopes) { // get item by reference
            if (envelope.first < envelope.second) {
                swap(envelope.first, envelope.second);
            }
        }
    }

    int getEnvelopeNum(int a) {
        if (fw[a] == 0) {
            if (ww[a] == -1) fw[a] = 1;
            else fw[a] = getEnvelopeNum(ww[a]) + 1;
            if (hh[a] == -1) fh[a] = 1;
            else fh[a] = getEnvelopeNum(hh[a]) + 1;
        }
        return max(fw[a], fh[a]);
    }

    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        len = envelopes.size();
        normalizeEnvelopes(envelopes);
        // myenvelopes.assign(envelopes.begin(), envelopes.end());
        myenvelopes = envelopes;
        sortInd(indByW, cmpww);
        sortInd(indByH, cmphh);
        findSmallerByInd(indByW, ww);
        findSmallerByInd(indByH, hh);

        fw.assign(len, 0);
        fh.assign(len, 0);
        int ans = 0;
        for (int i = 0; i < len; i++) {
            ans = max(ans, getEnvelopeNum(i));
            cout << ans << ' ' << i << endl;
        }

        return ans;

        for (auto const& a : hh)
            cout << a << ' ';
    }
};

vector<pair<int, int>> Solution::myenvelopes;

int main() {
    Solution solution;
    vector<pair<int, int>> envelopes = {{46,89},{50,53},{52,68},{72,45},{77,81}};
    //{{1,3},{3,5},{6,7},{6,8},{8,4},{9,5}};
    //{{46,89},{50,53},{52,68},{72,45},{77,81}}; //{{5,4},{6,4},{6,7},{2,3}};
    int ans = solution.maxEnvelopes(envelopes);
    cout << ans;

    return 0;
}
