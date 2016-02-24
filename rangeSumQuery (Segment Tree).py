#!/bin/python3
__author__ = 'radon'

# 37.97%
# I write Python worse than CPP somehow
# if implement tree in array rather than nodes, will be much faster

class NumArray(object):
    def buildSegTree(self, start, end):
        if (start > end): return None
        if (start == end):
            node = {"left": None, "right": None, "start": start, "end": end, "sum": self.nums[start] }
            return node
        mid = (start + end)//2
        nodeLeft = self.buildSegTree(start, mid)
        nodeRight = self.buildSegTree(mid+1, end)
        sumLeft = 0 if not nodeLeft else nodeLeft["sum"]
        sumRight = 0 if not nodeRight else nodeRight["sum"]
        node = {"left": nodeLeft, "right": nodeRight, "start": start, "end": end, "sum": sumLeft+sumRight}
        return node

    def __init__(self, nums):
        self.nums = nums
        if len(nums) == 0:
            self.segTree = None
        else:
            self.segTree = self.buildSegTree(0, len(self.nums)-1)

    def treeUpdate(self, node, i):
        if node["start"] == node["end"]:
            # i is the only ele
            delta = self.nums[i] - node["sum"]
            node["sum"] = self.nums[i]
            return delta
            # so that we don’t have to refer to another child during update
        mid = (node["start"]+node["end"])//2
        if i <= mid:
            delta = self.treeUpdate(node["left"], i)
        else:
            delta = self.treeUpdate(node["right"], i)
        node["sum"] = node["sum"] + delta
        return delta

    def update(self, i, val):
        """
        :type i: int
        :type val: int
        :rtype: int
        """
        if i < 0 or i >= len(self.nums): return None
        self.nums[i] = val
        self.treeUpdate(self.segTree, i)

    def querySegtree(self, node, i, j):
        # https://wxx5433.gitbooks.io/interview-preparation/content/part_ii_leetcode_lintcode/segment_tree/interval_sum_ii.html
        # does better than me
        if node["start"] == node["end"]:
            # i == j
            return node["sum"]
        if node["start"] == i and node["end"] == j:
            return node["sum"]
        mid = (node["start"]+node["end"])//2
        if j <= mid:
            return self.querySegtree(node["left"], i, j)
        elif i > mid:
            return self.querySegtree(node["right"], i, j)
        else:
            return self.querySegtree(node["left"], i, mid) + self.querySegtree(node["right"], mid+1, j)

    def sumRange(self, i, j):
        """
        sum of elements nums[i..j], inclusive.
        :type i: int
        :type j: int
        :rtype: int
        """
        if self.segTree is None: return 0 #err

        #it's more wise to put the following check in procedures
        if i > j: return None
        if i < 0: i = 0
        if j >= len(self.nums): j = len(self.nums) - 1

        return self.querySegtree(self.segTree, i, j)
    
numArray = NumArray([1,3,5])
print(numArray.sumRange(0, 2))
numArray.update(1, 2)
print(numArray.sumRange(0, 2))