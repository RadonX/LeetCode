// https://www.lintcode.com/problem/largest-rectangle-in-histogram/description
// 96.4%

public class Solution {

    int[] leftBound;
    int[] rightBound;
    int[] bars;
    int n;
    int findLeftBound(int index) {
        int h = bars[index];
        int i = index - 1;
        while (i >= 0) {
            // invariant: bars[i+1] >= h
            if (bars[i] < h) {
                return i + 1;
            } else {
                i = leftBound[i] - 1;
            }
        }
        return 0;
    }

    int findRightBound(int index) {
        // CHECK: edge case len-1
        int h = bars[index];
        int i = index + 1;
        while (i < n) {
            // invariant: bars[i-1] >= h
            if (bars[i] < h) {
                return i - 1;
            } else {
                i = rightBound[i] + 1;
            }
        }
        return n - 1;
    }

    /**
     * @param height: A list of integer
     * @return: The area of largest rectangle in the histogram
     */
    public int largestRectangleArea(int[] height) {
        if (height.length == 0) {
            return 0;
        }
        n = height.length;
        bars = height;
        leftBound = new int[n];
        rightBound = new int[n];
        for (int i = 0; i < n; i++) {
            leftBound[i] = findLeftBound(i);
        }
        for (int i = n - 1; i >= 0; i--) {
            rightBound[i] = findRightBound(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int tmp = bars[i] * (rightBound[i] - leftBound[i] + 1);
            if (tmp > ans) {
                ans = tmp;
            }
        }
        return ans;
    }
}
