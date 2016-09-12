#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        int len = s.size();
        if (len == 0) return 0;

        int *f = (int*) malloc(sizeof(int) * (len + 1) );

        // f[i] = f[i-1] * ? + f[i-2] * ?
        f[0] = 1; // remind: 1 instead of 0
        // '0'
        f[1] = (s[0] != '0');
        for (int i = 2; i <= len; i++) {
            // f[i] = f[i-1] * (s[i-1] != '0')
            //         + f[i-2] * ((s[i-2] == '1') || ((s[i-2] == '2') && s[i-1] <= '6') );
            if (s[i-1] != '0') f[i] = f[i-1]; else f[i] = 0;
            if ((s[i-2] == '1') || ((s[i-2] == '2') && s[i-1] <= '6') ) f[i] += f[i-2];
        }

        return f[len];
    }
};


int main() {
    Solution solution;
    cout << solution.numDecodings("12") << endl;
    cout << solution.numDecodings("0") << endl;
    cout << solution.numDecodings("1") << endl;
    cout << solution.numDecodings("") << endl;
    cout << solution.numDecodings("123") << endl;
    cout << solution.numDecodings("3123") << endl;
    cout << solution.numDecodings("1203") << endl;
    cout << solution.numDecodings("31023") << endl;

    return 0;
}
