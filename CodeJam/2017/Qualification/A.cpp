// https://code.google.com/codejam/contest/3264486

// O(NK)
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

int main()
{
#ifdef LOCAL
    freopen(FNAME".in", "r", stdin);
    freopen(FNAME".out", "w", stdout);
#endif

    int i, j, k;
    int T, TT;
    cin >> TT;
    for(T = 1; T <= TT; T++)
    {
        printf("Case #%d: ", T);
        string S;
        int K;
        cin >> S >> K;
        bool success = true;
        int count = 0;
        i = 0;
        for (; i + K <= S.length(); ++i) {
            if (S[i] == '-') {
                count++; // flip at position i
                for (j = 1; j < K; ++j) {
                    S[i+j] = (S[i+j] == '+')? '-': '+';
                }
            }
        }
        for (; i < S.length(); ++i) {
            if (S[i] == '-') {
                success = false;
                break;
            }
        }
        if (success) {
            printf("%d\n", count);
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
	return 0;
}
