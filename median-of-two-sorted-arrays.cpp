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
#include <unordered_set>

using namespace std;

class Solution {
    int findKthElement2(const vector<int>& A, int a0, int a1,
            const vector<int>& B, int b0, int b1, int k) { // 32ms
        // requires: k <= (lenA + lenB)
        // cout << a0 << ',' << a1 << ';'<< b0 << ',' << b1 << ';' << k << endl;
        if (a1 < a0) return B[b0 + k - 1];
        if (b1 < b0) return A[a0 + k - 1];
        int lenA = a1 - a0 + 1;
        int lenB = b1 - b0 + 1;
        if (k == lenA + lenB) return max(A[a1], B[b1]);
        int i = ceil(k * lenA / double(lenA + lenB)); // \in [1, lenA/k]
        int j = k + 1 - i; // \in [1, lenB/k]
        // cout << lenA << ',' << lenB << endl;
        if (A[a0 + i - 1] <= B[b0 + j - 1]) {
            if (j == 1 || A[a0 + i - 1] >= B[b0 + j - 2]) return A[a0 + i - 1];
            a0 = a0 + i; // a
            k = k - i;
            b1 = b0 + j - 2;
        } else {
            if (i == 1 || B[b0 + j - 1] >= A[a0 + i - 2]) return B[b0 + j - 1];
            b0 = b0 + j;
            k = k - j;
            a1 = a0 + i - 2;
        }
        return findKthElement2(A, a0, a1, B, b0, b1, k);
    }

    int findKthElement(const vector<int>& A, int a0, int a1,
            const vector<int>& B, int b0, int b1, int k) { // 32ms, 10.68%, 69.39%
        // requires: k <= (lenA + lenB)
        // cout << a0 << ',' << a1 << ';'<< b0 << ',' << b1 << ';' << k << endl;
        if (a1 < a0) return B[b0 + k - 1];
        if (b1 < b0) return A[a0 + k - 1];
        int amid = (a0 + a1) / 2;
        int bmid = (b0 + b1) / 2;
        int i = amid - a0 + 1;
        int j = bmid - b0 + 1;


        if (i + j <= k) {
            if (A[amid] <= B[bmid]) { a0 = amid + 1; k = k - i; }
            else { b0 = bmid + 1; k = k - j; }
        } else {
            if (A[amid] <= B[bmid]) { b1 = bmid - 1; }
            else { a1 = amid - 1; }
        }

        return findKthElement(A, a0, a1, B, b0, b1, k);
    }

    int bar(const vector<int>& A, const vector<int>& B, int k) { // 35ms, 8.78%, 59.78%
        int i = 0, j = 0, mid;
        int m = A.size(), n = B.size();
        if (m == 0) return B[k - 1]; // 0-indexed
        if (n == 0) return A[k - 1];
        while (k > 1) {
            mid = k / 2;
            if (i + mid - 1 >= m) j += mid;
            else if (j + mid - 1 >= n) i += mid;
            else if (A[i + mid - 1] < B[j + mid - 1]) i += mid;
            else j += mid;
            k -= mid;
        }
        if (i >= m) return B[j];
        else if (j >= n) return A[i];
        else return min(A[i], B[j]);
    }
public:
    double findMedianSortedArrays(const vector<int>& A, const vector<int>& B) {
        // == 1?
        int s1 = A.size(), s2 = B.size();
        int s = s1 + s2; // != 0
        if (s % 2 == 0) {
            // return (findKthElement(A, 0, s1 - 1, B, 0, s2 - 1, s/2)
            //         + findKthElement(A, 0, s1 - 1, B, 0, s2 - 1, s/2 + 1))/2.0;
            return (bar(A, B, s/2) + bar(A, B, s/2 + 1))/2.0;
        } else return bar(A, B, s/2 + 1);

    }
};


int main() {
    Solution solution;
    cout << solution.findMedianSortedArrays(vector<int> {1,3}, vector<int> {2}) << endl;
    cout << solution.findMedianSortedArrays(vector<int> {1,3,4,8}, vector<int> {2,9}) << endl;
    return 0;
}
