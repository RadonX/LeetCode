// https://code.google.com/codejam/contest/5304486/dashboard#s=p1

// O(N*PlogP + N*P), Greedy

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
#define fori(i, n) for (int i = 0; i < (int)(n); ++i)
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

int N, P;
int R[50];
int count[50][50];
vector<int> W[50];
vector<int>::iterator it[50];
int bound[50][2];

int NWayMerge() {
    int ans = 0;
    fori(i, N) {
        it[i] = W[i].begin();
    }
    int serving = 0;
    bool inc = true;
    while (true) {
        if (inc) {
            if (it[0] == W[0].end()) return ans;
            double sample = *(it[0]);
            serving = max(serving + 1, (int) ceil(sample / (1.1 * R[0])));
            fori(i, N) {
                bound[i][0] = ceil(0.9*(serving*R[i]));
                bound[i][1] = floor(1.1*(serving*R[i]));
            }
            inc = false;
        }
        bool found = true;
        fori(i, N) {
            // Find ingredient within weight bounds
            auto &r = it[i];
            while (r != W[i].end()) {
                if (*r >= bound[i][0]) break;
                else ++r;
            }
            if (r == W[i].end()) { // all too light
                return ans;
            }
            //
            if (*r <= bound[i][1]) {
            } else {
                found = false;
                break;
            }
        }
        if (found) {
            ans++;
            fori(i, N) {
                (it[i])++;
                // it[i] is for this kit
                // move iterator next
            }
        } else {
            inc = true;
        }
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
        cin >> N >> P;
        memset(R, 0, sizeof(R));
        fori(i, N) {
            cin >> R[i];
        }
        double Q;
        fori(i, N) {
            W[i].clear();
            fori(j, P) {
                cin >> Q;
                int serving = round(Q / R[i]);
                if (serving == 0) continue;
                W[i].push_back(Q);
                    // printf("(%d:%d)", i, serving);
            }
            sort(W[i].begin(), W[i].end());
        }

        printf("%d\n", NWayMerge());
    }
	return 0;
}
