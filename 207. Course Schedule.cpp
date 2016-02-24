//https://leetcode.com/problems/course-schedule/
// 284ms, 13.53%, 83.54%

//already good, STL cost time I suppose

class Solution {
public:
    bool topo(int i, vector<int> &visited, vector<vector<int> >  &preAdj){
        //visited[i] == 0
        visited[i] = 1;
        bool flag = 0;

        for (auto& j: preAdj[i]){
            if (visited[j] == 0){
                if (topo(j, visited, preAdj))
                    return 1;
            }else if (visited[j] == 1)
                return 1;
        }

        //Stack.push(i);
        visited[i] = 2;
        return 0;
    }

    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<vector<int> > preAdj(numCourses, vector<int>() ) ;
        for (auto& pre: prerequisites){
            preAdj[pre.second].push_back(pre.first);
        }

        vector<int> visited(numCourses, 0);
        for (int i = 0; i < numCourses; i++) {
            if (visited[i] == 0)
                if (topo(i, visited, preAdj))
                    return false;
        }

        return true;

    }
};
