#!/bin/python3
__author__ = 'radon'

'''
    https://leetcode.com/problems/median-of-two-sorted-arrays/
    There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
'''
# solution:
# https://leetcode.com/discuss/78288/9-lines-o-log-min-m-n-python
# https://leetcode.com/discuss/30807/o-lg-m-n-c-solution-using-kth-smallest-number
# https://leetcode.com/discuss/74981/java-easy-version-to-understand

# my idea is quite simple--compare the median of both arrays
# what I don't expect is that there are so many cases,
# so that the program gets buggy and long



class Solution:
    """
    @param A: An integer array.
    @param B: An integer array.
    @return: a double whose format is *.5 or *.0
    """
    def findMedianSortedArrays(self, A, B):


        def findMedian(A, sA, tA, B, sB, tB):
            # len > 0

            #print(A[sA:tA+1], B[sB:tB+1])
            lenA = tA - sA + 1
            lenB = tB - sB + 1
            if lenA + lenB <= 4:
                C = sorted(A[sA:tA+1] + B[sB:tB+1])
                return C[len(C)//2] if len(C) % 2 == 1 else (C[len(C)//2 - 1] + C[len(C)//2])/2.0
            if lenA > lenB: return findMedian(B, sB, tB, A, sA, tA)

            # lenA <= lenB
            hlenA = lenA // 2
            hlenB = lenB // 2
            medA = A[sA + hlenA] if lenA % 2 == 1 else (A[sA+hlenA-1] + A[sA+hlenA])/2.0
            medB = B[sB + hlenB] if lenB % 2 == 1 else (B[sB+hlenB-1] + B[sB+hlenB])/2.0
            if lenA % 2 == 0 and lenB % 2 == 0:
                flag = 1
                if lenA == 2:
                    if A[sA] < B[sB+hlenB-1]:
                        if A[tA] >= B[sB+hlenB]:
                            return medB
                        return findMedian(A, tA, tA, B, sB, tB-1)
                    else:
                        if A[tA] <= B[sB+hlenB]: return medA
                        else: return findMedian(A, sA, sA, B, sB+1, tB)
            else: flag = 0


            if medA == medB: return medA
            if lenA == 1:
                if lenB == 1: return (medA+medB)/2.0
                if lenB % 2 == 0:
                    if medA < medB: return max(medA, B[sB + hlenB-1])
                    else: return min(medA, B[sB + hlenB] )
                else:
                    if medA < medB:
                        return (medB + max(medA, B[sB + hlenB-1]) )/2.0
                    else: return (medB + min(medA, B[sB+hlenB+1])  )/2.0
            else:
                if medA < medB:
                    return findMedian(A, sA + hlenA - flag, tA, B, sB, tB - hlenA + flag)
                else: return findMedian(A, sA, tA - hlenA + flag, B, sB + hlenA - flag, tB)


        # extreme case
        if len(A) == 0 or len(B) == 0:
            if len(A) == 0:
                if len(B) == 0:
                    return
                else:
                    mid = len(B) // 2
                    return B[mid] if len(B) % 2 == 1 else (B[mid-1]+B[mid])/2.0
            else:
                mid = len(A) // 2
                return A[mid] if len(A) % 2 == 1 else (A[mid-1]+A[mid])/2.0
        return findMedian(A, 0, len(A)-1, B, 0, len(B)-1)




sol = Solution()
A=[1,4]
B=[2,3]
print(sol.findMedianSortedArrays(A,B))