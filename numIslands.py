#!/bin/python3
__author__ = 'radon'

# https://leetcode.com/problems/number-of-islands/


class Solution(object):
    def init(self, grid):
        self.m = len(grid)+2 # m * n
        if self.m == 2:
            self.n = 0
            return
        n = len(grid[0])+2
        self.grid = [ ['0']*n ] + [['0']+x+['0'] for x in grid] + [ ['0']*n ]
        self.n = n
        self.d = [[-1,0],[0,-1],[1,0],[0,1]]

    def dfs(self, i, j):
        # dfs is easy, but many redundant attempt!!!!!
        self.grid[i][j] = '-'
        for d in self.d:
            di = d[0]+i
            dj = d[1]+j
            if self.grid[di][dj] == '1':
                self.dfs(di,dj)


    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        self.init(grid)
        count = 0
        for i in range(1,self.m-1):
            for j in range(1,self.n-1):
                if self.grid[i][j] == '1':
                    count = count + 1
                    self.dfs(i,j)

        return count



_arr_cnt = int(input()) # number of lines
_arr_i=0
_arr = []
while _arr_i < _arr_cnt:
    _arr_item = input() 
    tmp = [x for x in _arr_item]
    _arr.append(tmp)
    _arr_i+=1


res = Solution()
print(res.numIslands(_arr))
