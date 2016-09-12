#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

class Solution {

public:
    int maximalSquare(vector<vector<char> >& matrix) {
        int height = matrix.size();
        if (height == 0) return 0;
        int width = matrix[0].size();
        if (width == 0) return 0;
        int f[height][width];

        int i, j;
        int maxlen = 0;

        // calc f[0][:]
        for (j = 0; j < width; ++j) {
            f[0][j] = (matrix[0][j] == '1');
            maxlen = max(maxlen, f[0][j]);
        }
        // calc f[1:][:]
        for (i = 1; i < height; ++i) {
            f[i][0] = (matrix[i][0] == '1');
            for (j = 1; j < width; ++j) {
                f[i][j] = (matrix[i][j] == '1')? (min(f[i - 1][j - 1], min(f[i-1][j], f[i][j-1])) + 1) : 0;
                maxlen = max(maxlen, f[i][j]);
            }
        }

        return maxlen * maxlen;
    }
};

int main() {
    Solution solution;
    vector<vector<char> > matrix {{'1','0','1','0','0'}, {'1','0','1','1','1'}, {'1','1','1','1','1'}, {'1','0','0','1','0'}};
    cout << solution.maximalSquare(matrix);

    return 0;
}
