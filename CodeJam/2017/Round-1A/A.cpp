// https://code.google.com/codejam/contest/5304486/dashboard#s=p0

// O(RC), Greedy

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

char board[25][25];
int pos[26][4];
int R, C;

bool fillByCol(int ch, int i) {
    bool flag = true;
    for (int j = pos[ch][0]; j <= pos[ch][1]; ++j) {
        if (board[j][i] != '?') {
            flag = false;
            break;
        }
    }
    if (flag) {
        for (int j = pos[ch][0]; j <= pos[ch][1]; ++j) {
            board[j][i] = 'A' + ch;
        }
    }
    return flag;
}

bool fillByRow(int ch, int i) {
    bool flag = true;
    for (int j = pos[ch][2]; j <= pos[ch][3]; ++j) {
        if (board[i][j] != '?') {
            flag = false;
            break;
        }
    }
    if (flag) {
        for (int j = pos[ch][2]; j <= pos[ch][3]; ++j) {
            board[i][j] = 'A' + ch;
        }
    }
    return flag;
}

void grow(int ch) {
    // upward
    for (int i = pos[ch][0] - 1; i >=0; --i) {
        if (fillByRow(ch, i)) pos[ch][0] = i;
        else break;
    }
    // leftward
    for (int i = pos[ch][2] - 1; i >=0; --i) {
        if (fillByCol(ch, i)) pos[ch][2] = i;
        else break;
    }
    // rightward
    for (int i = pos[ch][3] + 1; i < C; ++i) {
        if (fillByCol(ch, i)) pos[ch][3] = i;
        else break;
    }
    // downward
    for (int i = pos[ch][1] + 1; i < R; ++i) {
        if (fillByRow(ch, i)) pos[ch][1] = i;
        else break;
    }

}

void fillBoard() {
    fori(i, 26) {
        if (pos[i][0] == -1) continue;
        for (int j = pos[i][0]; j <= pos[i][1]; j++) {
            for (int k = pos[i][2]; k <= pos[i][3]; k++) {
                board[j][k] = 'A' + i;
            }
        }
    }
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
        printf("Case #%d:\n", T);
        cin >> R >> C;
        memset(pos, -1, sizeof(pos));
        fori(i, R)
            fori(j, C) {
                char ch;
                cin >> ch;
                board[i][j] = ch;
                if (ch == '?') continue;
                int p = ch - 'A';
                // up
                pos[p][0] = (pos[p][0] == -1)? i: pos[p][0];
                // down
                pos[p][1] = (pos[p][1] == -1)? i: i;
                // left
                pos[p][2] = (pos[p][2] == -1)? j: min(pos[p][2], j);
                // right
                pos[p][3] = (pos[p][3] == -1)? j: max(pos[p][3], j);
            }

        fillBoard();
        fori(i, R)
            fori(j, C) {
                if (board[i][j] != '?') {
                    grow(board[i][j] - 'A');
                }
            }

        fori(i, R) {
            fori(j, C) {
                printf("%c", board[i][j]);
            }
            printf("\n");
        }

    }
	return 0;
}
