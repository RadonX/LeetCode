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


// https://discuss.leetcode.com/topic/50057/0ms-17-lines-readable-c-solution
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0) return "";
        if (numerator == 0) return "0";
        string ans;
        if ((numerator < 0) ^ (denominator < 0)) ans = "-";
        unsigned int unumerator = (unsigned int)
                ((numerator < 0) && (numerator != INT_MIN))? -numerator: numerator;
        unsigned long udenominator = labs(denominator);

        ans += to_string(unumerator / udenominator);
        unsigned int remain = unumerator % udenominator;
        if (remain == 0) return ans;
        ans += ".";
        unordered_map<unsigned int, unsigned int> rem;

        rem[0] = 0;
        while (rem.find(remain) == rem.end()) { // first appearance
            unsigned long tmp = (unsigned long) remain * 10;
            // Comment: this part saves significant time from % and /. 
            while (tmp < udenominator) {
                rem[remain] = ans.size(); // remain * 10^n: first appearance
                remain = (unsigned int) tmp;
                ans.append(1, '0');
                tmp *= 10;
            }
            rem[remain] = ans.size();
            remain = tmp % udenominator;
            ans.append(1, '0' + tmp / udenominator);
        }

        if (remain != 0) {
            ans.insert(rem[remain],1,'(');
            ans += ")";
        }

        return ans;
    }
};

class Solution2 {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0) return "";
        if (numerator == 0) return "0";
        string ans;
        if ((numerator < 0) ^ (denominator < 0)) ans = "-";
        unsigned int unumerator = (unsigned int)
                ((numerator < 0) && (numerator != INT_MIN))? -numerator: numerator;
        unsigned int udenominator = (unsigned int)
                ((denominator < 0) && (denominator != INT_MIN))? -denominator: denominator;

        ans += to_string(unumerator / udenominator);
        unsigned int remain = unumerator % udenominator;
        if (remain == 0) return ans;
        ans += ".";
        unsigned int remainOld = remain;
        unordered_map<unsigned int, pair<char, unsigned int> > rem;

        // first pass
        while (remain != 0) {
            if (rem.find(remain) == rem.end()) { // first appearance
                unsigned long tmp = (unsigned long) remain * 10;
                rem[remain].first = '0' + tmp / udenominator;
                rem[remain].second = tmp % udenominator;
                remain = rem[remain].second;
            } else { // repeating starts here
                break;
            }
        }

        // second pass
        // Comment: cutting this pass can decrease running time from 4ms to 3ms
        unsigned int repeatRem = remain;
        remain = remainOld;
        unsigned int tmp = 0;
        while (remain != tmp) {
            if (remain == repeatRem){
                ans += "(";
                tmp = repeatRem;
            }
            ans.append(1, rem[remain].first);
            remain = rem[remain].second;
        }
        if (tmp != 0) ans += ")";

        return ans;
    }
};

int main() {
    Solution solution;
    cout << solution.fractionToDecimal(2, 3) << endl;
    cout << solution.fractionToDecimal(2, -1) << endl;
    cout << solution.fractionToDecimal(-1, -2) << endl;
    cout << solution.fractionToDecimal(-100, 19) << endl;
    cout << solution.fractionToDecimal(1453, 30) << endl;
    cout << solution.fractionToDecimal(1, 214748364) << endl;
    cout << solution.fractionToDecimal(1, -2147483648) << endl;
    cout << solution.fractionToDecimal(-1, -2147483648) << endl;
    cout << solution.fractionToDecimal(1, 2147483648) << endl;
    cout << solution.fractionToDecimal(2147483647, 1) << endl;

    return 0;
}
