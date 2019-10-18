// https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
// My solution times out. Didn't realize I can use counting sort. 

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class Solution {

    static void swap(int[] arr, int x, int y) {
        int cache = arr[x];
        arr[x] = arr[y];
        arr[y] = cache;
    }
    static int findKth(int[] window, int h, int t, int k, boolean findKK) {
        int p = h;
        int pivot = window[p];
        int i = h + 1;
        int j = t;

        while (i <= j) {
            while (i <= j && window[i] <= pivot) i++;
            while (i <= j && pivot <= window[j]) j--;
            if (i < j) swap(window, i, j);
        }
        swap(window, p, j);
        p = j;
        if (!findKK) {
            if (p == k) return pivot;
            if (p < k) return findKth(window, p + 1, t, k, false);
            if (p > k) return findKth(window, h, p - 1, k, false);
        } else {
            if (p == k) return pivot + findKth(window, p + 1, t, k + 1, false);
            if (p < k) return findKth(window, p + 1, t, k, true);
            if (p > k) {
                if (p == k+1) {
                    return findKth(window, h, p - 1, k, false) + pivot;
                } else {
                    return findKth(window, h, p - 1, k, true);
                }
            }
        }
        return 0;
    }

    static int findTwoTimesMedian(int[] window) {
        int d = window.length;
        if (d % 2 == 1) {
            return findKth(window, 0, d-1, d/2, false) * 2;
        } else {
            return findKth(window, 0, d-1, d/2-1, true);
        }
    }

    // Complete the activityNotifications function below.
    static int activityNotifications(int[] expenditure, int d) {

        /*
        1. maintain the median in a moving window
        2. median: k-th large (partition)
        O(nd)
        */
        int n = expenditure.length;
        int count = 0;
        for (int i = d; i < n; i++) {
            int[] window = Arrays.copyOfRange(expenditure, i-d, i);
            int threshold = findTwoTimesMedian(window);
            System.out.println(threshold);
            if (expenditure[i] >= threshold) {
                count++;
            }
        }
        return count;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] nd = scanner.nextLine().split(" ");

        int n = Integer.parseInt(nd[0]);

        int d = Integer.parseInt(nd[1]);

        int[] expenditure = new int[n];

        String[] expenditureItems = scanner.nextLine().split(" ");
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int i = 0; i < n; i++) {
            int expenditureItem = Integer.parseInt(expenditureItems[i]);
            expenditure[i] = expenditureItem;
        }

        int result = activityNotifications(expenditure, d);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}
