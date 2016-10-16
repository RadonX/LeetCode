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

// #define DEBUG

struct Pass {
    long long prod;
    long m, w; // m >= w
    long long ncandy;
    Pass(long m, long w, long long ncandy = 0):
        prod((long long)m * w), m(max(m,w)), w(min(m,w)), ncandy(ncandy) {}
};
Pass f[2] = {Pass(0,0),Pass(0,0)};

inline Pass buyMW(const Pass &pass, long k) {
    long mw = pass.m + pass.w + k;
    long m = max(pass.m, (mw+1)/2);
    long w = mw - m;
    return Pass(m, w);
}

long long curMax, p;
long long n;
long i, maxi;

inline void makeOnePass(Pass &prev, Pass &cur) {
    auto &state = prev;
    // f[prev][m][w] + m*w -> f[cur][m][w]
    // f[prev][m][w] - p*k + mk*wk -> f[cur][mk][wk]
    long maxk = state.ncandy / p;
    for (auto k = maxk; k >= 0; --k){
        Pass pass = buyMW(state, k);
        pass.ncandy = state.ncandy - p*k + pass.prod;
        curMax = max(curMax, pass.ncandy);
        // if not buy more machine or worker in the future
        // estimate i
        long tmp = i + max(n - pass.ncandy + pass.prod - 1, 0LL) / pass.prod;
        maxi = min(maxi, tmp);
        if (k == maxk) cur = pass;
#ifdef DEBUG
        cout << pass.m << ',' << pass.w << '(' << k << "):" << pass.ncandy
            << " - " << maxi << endl;
#endif
        if (p <= state.m) break; // must spend all, need to try other k
    }

}

int main() {
    long  m, w;
    cin >> m >> w >> p >> n;
    int toggle = 0;

    i = 1;
    maxi = (n+m*w-1) / (m*w);
    curMax = (long long)m*w;
    f[toggle] = Pass(m, w, curMax); // 1st pass
    while (i < maxi && curMax < n) { // prev
        // new pass
        ++i;
#ifdef DEBUG
        cout << '[' << i << ']' << endl;
#endif
        Pass &b = f[1 - toggle];
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
