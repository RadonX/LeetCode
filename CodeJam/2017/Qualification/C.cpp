// https://code.google.com/codejam/contest/3264486

// O(1)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <functional>
#include <cmath>
#define MOD 1000000007
#define MAX 0x3f3f3f3f
#define MAX2 0x3f3f3f3f3f3f3f3fll
#define ERR 1e-10
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#pragma warning(disable:4996)
using namespace std;

typedef long long ll;
typedef long double ldb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

int my_log2(ll x) {
    if (x <= 0LL) return -1LL; // why 0LL??
    int ans = -1;
    while (x != 0LL) {
        ans++;
        x >>= 1;
    }
    // printf("[%d]", ans);
    return ans;
}

ll my_pow2(int x) {
    ll ans = 1LL;
    while (x > 0) {
        x--;
        ans <<= 1;
    }
    return ans;
}

int main()
{
#ifdef LOCAL
    freopen(FNAME".in", "r", stdin);
    freopen(FNAME".out", "w", stdout);
#endif

    int i, j, k;
    int T, TT;
    cin >> TT;
    for (T = 1; T <= TT; T++)
    {
        printf("Case #%d: ", T);
        ll N, K;
        // every one choose before i is better off than i
        cin >> N >> K;
        int level = my_log2(K);
        ll firstInThisLevel = my_pow2(level);
        ll nsplit = firstInThisLevel; // my_pow2(level)
        ll nEmpty = N - (firstInThisLevel << 1) + 1LL;
        ll n = nEmpty / nsplit;
        ll r = nEmpty % nsplit; // note that nEmpty can be < 0, and r < 0
        if (K - firstInThisLevel < r) n++;
        printf("%lld %lld\n", (n+1) >> 1, n >> 1);
    }
	return 0;
}
