#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Solution {
    inline unsigned int intToPosUint(int a) {
        if ((a < 0) && (a != INT_MIN))
            a = -a;
        return (unsigned int) a;
    }
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) return INT_MAX;
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;

        unsigned int udividend = intToPosUint(dividend);
        unsigned int udivisor = intToPosUint(divisor);
        bool sign = ((dividend >= 0) && (divisor > 0)) || ((dividend < 0) && (divisor < 0));

        //  udivisor * ans <= udivident
        // ans: (1? + 2? + 4? + ...)
        unsigned int ans = 0;
        unsigned int tmp = udivisor;
        unsigned int power = 1; // tmp == dividend * power
        
        while (tmp < udividend) {
            tmp <<= 1; // since udividend <= (unsigned int) INT_MIN, tmp won't overflow
            power <<= 1;
        }
        while (udividend >= udivisor) {
            if (tmp <= udividend) {
                udividend -= tmp; // tmp > new dividend
                ans += power;
            }
            tmp >>= 1;
            power >>= 1;
        }

        return (sign || (ans == INT_MIN))? (int) ans: - (int) ans;
    }
};

int main() {
    Solution solution;
    cout << solution.divide(-101, 9) << endl;
    cout << solution.divide(101, 1) << endl;
    cout << solution.divide(0, 1) << endl;
    cout << solution.divide(101, 0) << endl;
    cout << solution.divide(-1301, 2) << endl;
    cout << solution.divide(1301, -2) << endl;
    cout << solution.divide(-2147483648, -1) << endl;
    cout << solution.divide(-2147483648, 1) << endl;
    cout << solution.divide(2147483647, 1) << endl;

	return 0;
}
