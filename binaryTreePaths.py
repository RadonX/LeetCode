#!/bin/python3
__author__ = 'radon'

"""
Definition of TreeNode:
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None
"""
class Solution:
    # @param {TreeNode} root the root of the binary tree
    # @return {List[str]} all root-to-leaf paths
    def dfs(self, node, foo):
        # node is not None
        foo = foo + '->'+str(node.val)
        if node.left or node.right:
            if node.left: self.dfs(node.left, foo)
            if node.right: self.dfs(node.right, foo)
        else: self.ans.append(foo)

    def binaryTreePaths(self, root):
        if root is None: return []
        self.ans = []
        foo = str(root.val)
        if root.left or root.right:
            if root.left: self.dfs(root.left, foo)
            if root.right: self.dfs(root.right, foo)
        else: self.ans.append(foo)
        return self.ans

# ----------------------------

# from: https://leetcode.com/discuss/52020/5-lines-recursive-python
def binaryTreePaths(self, root):
    if not root:
        return []
    return [str(root.val) + '->' + path
            for kid in (root.left, root.right) if kid
            for path in self.binaryTreePaths(kid)] or [str(root.val)]


# ----------------------------

#test

class obj(object):
    def __init__(self, d):
        for key, value in d.items():
            if isinstance(value, (list, tuple)):
               setattr(self, key, [obj(x) if isinstance(x, dict) else x for x in value])
            else:
               setattr(self, key, obj(value) if isinstance(value, dict) else value)

root = {
    'val':1,
    'left': {
        'val': 2,
        'left':None,
        'right':{
            'val': 5,
            'left':None,
            'right':None
        }
    },
    'right':{
        'val': 3,
        'left':None,
        'right':None
    }
}

sol = Solution()
sol.binaryTreePaths(obj(root))
