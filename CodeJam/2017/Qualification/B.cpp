// https://code.google.com/codejam/contest/3264486

// O(len(S))
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

void outputNumber(string str) {
    if (str == "0") {
        cout << "0";
    } else {
        int i = 0;
        for (; i < str.length(); ++i) {
            if (str[i] != '0') break;
        }
        for (; i < str.length(); ++i) {
            cout << str[i];
        }
    }
}

int main() {
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
        string S;
        string::size_type sz;
        cin >> S;
        string ans = S;
        char mins[S.length()];
        char maxs[S.length()];
        mins[S.length()-1] = S[S.length()-1];
        maxs[S.length()-1] = S[S.length()-1];
        for (i = S.length()-2; i >= 0; --i) {
            mins[i] = min(mins[i+1], S[i]); // smallest in [i,:]
            // largest sssss that <= S[i,:]
            // therefore, maxs[i] <= S[i]
            if (S[i] >= S[i+1]) maxs[i] = maxs[i+1];
            else maxs[i] = S[i];
        }
        bool flag = true;
        for (i = 0; i < S.length(); ++i) {
            if (flag) {
                if (maxs[i] == S[i]) {
                    // ans[i] = S[i];
                } else {
                    flag = false;
                    ans[i] = S[i] - 1;
                }
            } else {
                // free to choose any
                ans[i] = '9';
            }
        }
        outputNumber(ans);
        cout << endl;
    }
	return 0;
}
