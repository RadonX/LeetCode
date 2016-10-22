/*
 * https://www.hackerrank.com/contests/openbracket/challenges/strange-advertising
 * O(n)
 * #submissions: 1
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    long m = 5, ans = m / 2;
    cin >> n;
    for (int i = 2; i <=n; ++i) {
        m = m / 2 * 3;
        ans += m / 2;
    }
    cout << ans;
    return 0;
}
