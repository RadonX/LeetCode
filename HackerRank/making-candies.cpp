/*
 * https://www.hackerrank.com/contests/openbracket/challenges/making-candies
 * O()
 * #submissions: n
 * Dynamic Programming (sparse)
 * 1. Why cannot previous version pass 1 1 7 12 -> 12 test case
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
    long tmp;

    // spend all candies
    Pass &pass = cur;
    pass = buyMW(state, maxk);
    pass.ncandy = state.ncandy - p*maxk + pass.prod;
    curMax = max(curMax, pass.ncandy);
    // estimate maxi
    tmp = i + max((long long)ceil((double)(n - pass.ncandy) / pass.prod) , 0LL);
    maxi = min(maxi, tmp);
#ifdef DEBUG
    cout << pass.m << ',' << pass.w << '(' << maxk << "):" << pass.ncandy
        << " - " << maxi << endl;
#endif

    // select a best k \in [0, maxk]
    if (maxk == 0) return;
    if (p <= state.m) return; // must spend all
    long long targetNcandy = n - state.ncandy;
    if (maxk <= state.m - state.w) {
        // need to buy k Ws
        // minimize (targetNcandy + p*k) / (m*w+m*k)
        if (p * state.w - targetNcandy <= 0) return; // maxk is best
    }
    // try k == 0
    long long ncandy = state.ncandy + state.prod;
    // not buy more machine or worker in the future
    // estimate maxi
    tmp = i + max((long long)ceil((double)(n - ncandy) / state.prod) , 0LL);
    maxi = min(maxi, tmp);
}

int main() {
    long  m, w;
    cin >> m >> w >> p >> n;
    int toggle = 0;

    i = 1;
    curMax = (long long)m*w;
    maxi =  (long long)ceil((double)n  / curMax);
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
    // quadratic ??

    return 0;
}
