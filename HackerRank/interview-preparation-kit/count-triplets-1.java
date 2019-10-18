// https://www.hackerrank.com/challenges/count-triplets-1/problem
// Time: O(n); Memory: O(n)

// My first submission is wrong because I thought all elements in the triplets
// must be in the form of r^k

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

public class Solution {

    static void updateCount(long j, long r, Map<Long, Long> f, Map<Long, Long> g) {
        if (j % r == 0) {
            long j1 = j / r;
            long count = g.getOrDefault(j, 0L) + f.getOrDefault(j1, 0L);
            if (count != 0L) {
                g.put(j, count);
            }
        }
    }

    static Map<Long, Long> calcTupleCount(List<Long> arr, long r) {
        Long[] a = arr.toArray(new Long[arr.size()]);
        /*
            i: 0..len-1
            j: no limit , sparse

            h[i, j]:    ...    ele j ...
            f[i, j]: num of doublets (j/r, j) in arr[0..i] (i is inclusive)
            g[i, j]: ...    triplets ..

            g[i, j] =
                g[i-1, j] + (j == A[i]? f[i-1, A[i]/r]: 0)
        */
        /*
            f'[j]: num of doublets (j/r, j)
            i-1 -> i
                A[i] == j:
                    g'[j,i] += f'[j/r,i-1]
                    f'[j,i] += h'[j/r,i-1]
                    h'[j] = h'[j]+1
                A[i] != j: inherit (no need to update f[i, j])
            O(n)

        */
        List<Map<Long, Long>> counts = Arrays.asList(
            null, new HashMap<Long, Long>(), new HashMap<Long, Long>(), new HashMap<Long, Long>());
        for (int i = 0; i < a.length; i++) {
            long j = a[i];
            updateCount(j, r, counts.get(2), counts.get(3));
            updateCount(j, r, counts.get(1), counts.get(2));
            counts.get(1).merge(j, 1L, (old, y) -> old + 1);
            // System.out.printf("%d %d %d\n", counts.get(1).getOrDefault(j, 0L), counts.get(2).getOrDefault(j, 0L), counts.get(3).getOrDefault(j, 0L));
        }
        return counts.get(3);
    }
    /*
        f'[i]: num of doublets at indices (*, i)
        g'[i] = sum{f'[k]}, where k A[k] == A[i]/r
        ans = sum {g'[k]}
        O(n^2)
    */

    // Complete the countTriplets function below.
    static long countTriplets(List<Long> arr, long r) {
        Map<Long, Long> f = calcTupleCount(arr, r);

        long ans = f.values().stream()
        .mapToLong(Long::longValue)
        .sum();

        return ans;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] nr = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(nr[0]);

        long r = Long.parseLong(nr[1]);

        List<Long> arr = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Long::parseLong)
            .collect(toList());

        long ans = countTriplets(arr, r);

        bufferedWriter.write(String.valueOf(ans));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
