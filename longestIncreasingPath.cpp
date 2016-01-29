#include<vector>
#include<stdio.h>
using namespace std;

class Solution {
private:
    //int dx[4], dy[4];// = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    int m, n, *dx, *dy;
    void dfs(int x, int y, vector<vector<int> >& matrix);
    vector<vector<int> > *len;

public:

    Solution(){
        dx = new int[4];
        dx[0] = 1; dx[1] = -1; dx[2] = 0; dx[3] = 0;
        dy = new int[4];
        dy[0] = 0; dy[1] = 0; dy[2] = 1; dy[3] = -1;
    }

    int longestIncreasingPath(vector<vector<int> >& matrix) {
        if (!matrix.size()) return 0;
        m = matrix.size();
        n = matrix[0].size();
        len = new vector<vector<int> >(m, vector<int>(n,0)) ; //st
        //printf("%d", len);

        int i, j, ans = 0;

        for (i = 0; i < m; i++){
            for (j = 0; j < n; j++){
                if ( (*len)[i][j] == 0){
                    dfs(i, j, matrix);
                }
                ans = max(ans, (*len)[i][j]);
            }
        }

        return ans;
    }
};

void Solution::dfs(int x, int y, vector<vector<int> >& matrix){
    int d, nx, ny;
    for (d = 0; d < 4; d++){
        nx = x + dx[d];
        ny = y + dy[d];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n
                && matrix[nx][ny] > matrix[x][y]){
            if( (*len)[nx][ny] == 0) dfs(nx,ny,matrix);
            (*len)[x][y] = max((*len)[x][y], (*len)[nx][ny]);
        }
    }
    (*len)[x][y]++;
    //printf("%d,%d:%d\n", x, y, (*len)[x][y]);
}

int main(){
    Solution solution;
    vector<vector<int> > matrix;

    int nums[][3] = {
  {3,4,5},
  {3,2,6},
  {2,2,1}
};
    for(int i = 0; i < 3; i++){
        matrix.push_back(vector<int>(3));
        for(int j = 0; j < 3; j++){
            matrix[i][j] = nums[i][j];
        }
    }

    printf("%d\n",solution.longestIncreasingPath(matrix) );

    return 0;

}
