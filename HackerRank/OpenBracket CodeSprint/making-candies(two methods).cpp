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
    long long prod, m, w; // m >= w
    long long ncandy, npass; //
    Pass(long long m, long long w, long npass = 0, long long ncandy = 0):
        prod(m * w), m(max(m,w)), w(min(m,w)), npass(npass), ncandy(ncandy) {}
};

Pass f[2] = {Pass(0,0),Pass(0,0)};

inline Pass buyMW(const Pass &pass, long k) {
    long long mw = pass.m + pass.w + k;
    long long m = max(pass.m, (mw+1)/2);
    long long w = mw - m;
    return Pass(m, w);
}

long long curMax, p;
long long n;
long long i, maxi;

inline void makeOnePass(Pass &prev, Pass &cur) {
    auto &state = prev;
    // f[prev][m][w] + m*w -> f[cur][m][w]
    // f[prev][m][w] - p*k + mk*wk -> f[cur][mk][wk]
    long long maxk = state.ncandy / p;
    long long tmp;

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


inline void makeCandyUntilMWAffordable(Pass &state) {
    long long day = ceil((double)(p - state.ncandy) / (double)state.prod);
    state.npass += day;
    state.ncandy += state.prod * day;
    // return day;
}


int main() {
    long long  m, w;
    cin >> m >> w >> p >> n;

    curMax = (long long)m*w;
    maxi =  (long long)ceil((double)n  / curMax);

if (maxi <= 1000000) {
    int toggle = 0;
    i = 1;
    f[toggle] = Pass(m, w, 1, curMax); // 1st pass
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
} else {
    Pass state(m, w, 1, m*w);
    long long npass = (long long) ceil((double)n  / (m*w)); // possible day to reach target
    while (state.npass < npass && state.ncandy < n) {
        // in this state
        // f[prev][m][w] + m*w -> f[cur][m][w]
        // f[prev][m][w] - p*k + mk*wk -> f[cur][mk][wk]

#ifdef DEBUG
        cout << '[' << state.npass << ']' << endl;
#endif
        // if buy no more machine or worker
        npass = min(npass, state.npass + max((long long)ceil((double)(n - state.ncandy) / state.prod), 0LL) ); // no need
        // if want to buy machine or worker
        if (state.ncandy < p) {
            // buy nothing in following days
            makeCandyUntilMWAffordable(state);
        } else {
            // buy now
            state.npass += 1;
            long long maxk = state.ncandy / p;
            long long mw = state.m + state.w + maxk;
            state.m = max(state.m, (mw+1)/2);
            state.w = mw - state.m;
            state.prod = state.m * state.w;
            state.ncandy = state.ncandy - p*maxk + state.prod;
        }
#ifdef DEBUG
        cout << state.ncandy << endl << "------------\n";
#endif
    }
    if (state.ncandy >= n) npass = min(npass, state.npass);
    cout << npass;

}

    // enumerate m + w ??
    // quadratic ??

    return 0;
}
