//https://leetcode.com/problems/course-schedule-ii
// 484ms, - , 86.94%

class Solution {
public:
    bool topo(int i, vector<int> &visited, vector<vector<int> >  &preAdj, vector<int> &ans){
        //visited[i] == 0
        visited[i] = 1;
        bool flag = 0;

        for (auto& j: preAdj[i]){
            if (visited[j] == 0){
                if (topo(j, visited, preAdj, ans))
                    return 1;
            }else if (visited[j] == 1)
                return 1;
        }

        ans.push_back(i);
        visited[i] = 2;
        return 0;
    }

    vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<vector<int> > preAdj(numCourses, vector<int>() ) ;
        for (auto& pre: prerequisites){
            preAdj[pre.second].push_back(pre.first);
        }

        vector<int> ans;
        vector<int> visited(numCourses, 0);
        for (int i = 0; i < numCourses; i++) {
            if (visited[i] == 0)
                if (topo(i, visited, preAdj, ans))
                    return vector<int>();
        }

        reverse(ans.begin(), ans.end());
        return ans;

    }
};
