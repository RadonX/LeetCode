/*
 * https://www.hackerrank.com/contests/openbracket/challenges/making-candies
 * O()
 * #submissions: n
 * Dynamic Programming (sparse)
 * 1. wrong variable (map's it.first, .second not clear)
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// #define DEBUG

struct Pass {
    long long prod;
    long m, w; // m >= w
    Pass(long m, long w):
        prod((long long)m * w), m(max(m,w)), w(min(m,w)) {}
};
struct CmpPass {
    bool operator() (const struct Pass &a, const struct Pass &b) const {
        return (a.prod > b.prod) || (a.prod == b.prod && a.m > b.m) ;
    }
};
map<Pass, long long, CmpPass> f[2];

inline Pass buyWhat(const Pass &pass, long k) {
    long mw = pass.m + pass.w + k;
    long m = max(pass.m, (mw+1)/2);
    long w = mw - m;
    return Pass(m, w);
}

long long curMax, p;

template <class T, typename S, class C>
inline void makeOnePass(map<T, S, C> &prev, map<T, S, C> &cur) {
    pair<map<Pass, long long , CmpPass>::iterator, bool> itpair;
    for (const auto &state: prev) {
        // f[prev][m][w] + m*w -> f[cur][m][w]
        // f[prev][m][w] - p*k + mk*wk -> f[cur][mk][wk]
        long maxk = state.second / p;//state.first.prod / p;
#ifdef DEBUG
        cout << state.second << ',' << maxk << endl;
#endif
        long mink = 0;
        if (p <= state.first.m) mink = maxk; // spend all
        for (auto k = maxk; k >= mink; --k){
            Pass pass = buyWhat(state.first, k);
            long long ncandy = state.second - p*k + pass.prod;
#ifdef DEBUG
            cout << pass.m << ',' << pass.w << '(' << k << "):" << ncandy << endl;
#endif
            itpair = cur.emplace(make_pair(pass, ncandy));
            if (!itpair.second){
                map<Pass, long long, CmpPass>::iterator &it = itpair.first;
                it->second = max(it->second, ncandy);
            }
            curMax = max(curMax, ncandy);
        }
    }
}

int main() {
    long i, m, w;
    long long n;
    cin >> m >> w >> p >> n;
    int toggle = 0;

    i = 1;
    curMax = (long long)m*w;
    f[toggle].emplace(make_pair(Pass(m, w), curMax)); // 1st pass
    while (curMax < n) { // prev
        // new pass
        ++i;
        map<Pass, long long, CmpPass> &b = f[1 - toggle];
        b.clear(); // cur
        makeOnePass(f[toggle], b);
        toggle = 1 - toggle;
#ifdef DEBUG
        cout << curMax << endl << "------------\n";
#endif
    }
    cout << i;

    // enumerate m + w ??
    // binary search ??
    // quadratic ??

    return 0;
}
