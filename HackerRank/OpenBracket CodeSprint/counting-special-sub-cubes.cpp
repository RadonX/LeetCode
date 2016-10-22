/*
 * https://www.hackerrank.com/contests/openbracket/challenges/counting-special-sub-cubes
 * O(n^4)
 * #submissions: 1
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
using namespace std;

#define maxn 50
int M[maxn][maxn][maxn][3];


int main() {
    int n, q, qi, l, i, j, k, ans, tmp;
    cin >> q;
    for (qi = 1; qi <=q; ++qi) {
        cin >> n;
        ans = 0;
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++ j)
                for (k = 0; k < n; ++k) {
                    cin >> tmp;
                    fill_n(M[i][j][k],3,tmp);
                    if (M[i][j][k][2] == 1) ans++;
                }
        cout << ans; // l == 1
        for (l = 2; l <= n; ++l) {
            ans = 0;
            for (i = 0; i + l <= n; ++i) // must be ++i
                for (j = 0; j + l <= n; ++j)
                    for (k = 0; k + l <= n; ++k) {
                        M[i][j][k][0] = max(M[i][j][k][0], M[i][j][k+1][0]); // l-1 -> l
                        M[i][j][k][1] = max(M[i][j][k][0], // l
                            max(M[i][j+1][k][1], M[i][j+1][k+1][1])); // l - 1
                        M[i][j][k][2] = max(M[i][j][k][1], // l
                            max(max(M[i+1][j][k][2], M[i+1][j][k+1][2]),
                                max(M[i+1][j+1][k][2], M[i+1][j+1][k+1][2])));
                        if (M[i][j][k][2] == l) ans++;
                    }
            cout << ' ' << ans;
        }

        cout << endl;

    }
    return 0;
}
