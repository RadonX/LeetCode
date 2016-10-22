/*
 * https://www.hackerrank.com/contests/openbracket/challenges/coprime-power-sum
 * O(n*k*m); memory: O(n)
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define modulo 1000000007 // 10^9+7
#define maxm 1000000000000
long a[maxm+1];
long m;
int k;

inline void eraseA(long factor) {
    for (long i = factor; i <= m; i += factor) a[i] = -1;
}
inline long powerK(long i) {
    long result = 1;
    for (int j = 1; j <= k; ++j)
        result = (result * i) % modulo;
    return result; // i^k % modulo
}

int main() {
    int q, n, i, j;
    long factor, ans;
    cin >> q;
    for (int qi = 1; qi <= q; ++qi) {
        cin >> n >> k >> m;
        fill_n(a+1, m, 0);
        ans = 0;
        for (i = 0; i < n; ++i) {
            cin >> factor; eraseA(factor);
        }
        for (i = 1; i <= m; ++i) {
            if (a[i] != -1)
                ans = (ans + powerK(i)) % modulo;
        }
        cout << ans << endl;
    }

    return 0;
}
