/*
 * https://www.hackerrank.com/contests/openbracket/challenges/coprime-power-sum
 * O(n*m); memory: O(m)
 * #submissions: -
 *
 * TLE
 * maybe should try multiple threads?
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define modulus 1000000007 // 10^9+7
#define maxm 1000000000000
long m, i;
int k;

struct Factor {
    long cur, f;
    Factor(long cur, long f): cur(cur), f(f) {}
};
struct CmpFactor { // min heap
    bool operator() (const struct Factor &a, const struct Factor &b) {
        return a.cur > b.cur;
    }
};
priority_queue<Factor, vector<Factor>, CmpFactor> heap;

bool isCoprime(long i) {
    if (i < heap.top().cur) return true;
    while (i == heap.top().cur) {
        long factor = heap.top().f;
        long next = heap.top().cur + heap.top().f;
        heap.pop(); heap.emplace(Factor(next, factor));
    }
    return false;
}
// http://stackoverflow.com/questions/8496182/calculating-powa-b-mod-n
inline long powerK(long long base) { // i^k % modulus
    int exp = k;
    base %= modulus;
    long long result = 1;
    if (exp & 1) result = (result * base) % modulus;
    exp >>= 1;
    while (exp > 0) {
        base = (base * base) % modulus;
        if (exp & 1) result = (result * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main() {
    int q, n;
    long factor, ans;
    cin >> q;
    for (int qi = 1; qi <= q; ++qi) {
        cin >> n >> k >> m;
        ans = 0;
        // http://stackoverflow.com/questions/2852140/priority-queue-clear-method
        heap = priority_queue<Factor, vector<Factor>, CmpFactor>();
        for (i = 0; i < n; ++i) {
            cin >> factor; heap.emplace(Factor(factor, factor));
        }
        for (i = 1; i <= m; ++i) {
            if (isCoprime(i))
                ans = (ans + powerK(i)) % modulus;
        }
        cout << ans << endl;
    }

    return 0;
}
