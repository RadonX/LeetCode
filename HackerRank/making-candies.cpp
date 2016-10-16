/*
 * https://www.hackerrank.com/contests/openbracket/challenges/making-candies
 * O()
 * #submissions: n
 * Dynamic Programming (sparse)
 * 1. wrong variable (map's it.first, .second not clear)
 * 2. boundary == sign not set appropriately
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#define DEBUG

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
long long n;
long i, maxi;

template <class T, typename S, class C>
inline void makeOnePass(map<T, S, C> &prev, map<T, S, C> &cur) {
    pair<map<Pass, long long , CmpPass>::iterator, bool> itpair;
    for (const auto &state: prev) {
        // f[prev][m][w] + m*w -> f[cur][m][w]
        // f[prev][m][w] - p*k + mk*wk -> f[cur][mk][wk]
        long maxk = state.second / p;//state.first.prod / p;
        for (auto k = maxk; k >= 0; --k){ // k == 0
            Pass pass = buyWhat(state.first, k);
            long long ncandy = state.second - p*k + pass.prod;
            curMax = max(curMax, ncandy);
            // if not buy more machine or worker in the future
            // estimate i
            long tmp = i + max(n - ncandy + pass.prod - 1, 0LL) / pass.prod;
            maxi = min(maxi, tmp);
            if (k == maxk) {
                // we already estimate i, so need to add k < maxk state
                itpair = cur.emplace(make_pair(pass, ncandy));
                if (!itpair.second){
                    map<Pass, long long, CmpPass>::iterator &it = itpair.first;
                    it->second = max(it->second, ncandy);
                }
            }
#ifdef DEBUG
            cout << pass.m << ',' << pass.w << '(' << k << "):" << ncandy
                << " - " << maxi << endl;
#endif
            if (p <= state.first.m) break; // must spend all, need to try other k
        }
    }
}

int main() {
    long  m, w;
    cin >> m >> w >> p >> n;
    int toggle = 0;

    i = 1;
    maxi = (n+m*w-1) / (m*w);
    curMax = (long long)m*w;
    f[toggle].emplace(make_pair(Pass(m, w), curMax)); // 1st pass
    while (i < maxi && curMax < n) { // prev
        // new pass
        ++i;
#ifdef DEBUG
        cout << '[' << i << ']' << endl;
#endif
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
