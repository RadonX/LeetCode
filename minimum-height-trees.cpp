#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;



// Comment: actually there's only 1 or 2 nodes in ans.
// https://discuss.leetcode.com/topic/54677/super-simple-and-clear-recursive-solution-in-c-with-explanation
// And the nodes will exist in all longest paths.
// I failed to see this, and worked hard to find out all.
// A similar solution:
// https://discuss.leetcode.com/topic/44175/two-pass-dfs-c-solution-by-finding-longest-path-in-the-graph-very-easy
// I also failed to use two-pass to make my solution easier. 

// My solution is not good given this problem, but there is something else precious
class Solution {

    vector<vector<int> > graph; // adjacent list
    int maxPathLen;
    vector<int> ans;
    vector<int> commonAncestors;
    int rootNode = 0;

    struct MaxTwoPaths {
        int h1; // #node perspective. but the actual def is, the height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
        int h1node;
        int h2;
        int h2node;
    };
    /**
     * If there are >=2 top 1, then the mid must fall on the commonAncestor.
     * If there are one top 1 and >=2 top 2, and one of the top-2 paths is part of the
     * longest path, then the top-1 path must also be part of the path. Hence the mid falls on the top-1 path.
     * Therefore it's sufficient to record any two top 2 children in order to get the mid
     */
    vector<MaxTwoPaths> downpath;

    // Find all longest paths, whose ends are leaves
    // Set node 0 as root.
    // There is a youngest common ancestor on the path of any two leaves
    int dfs(int node, int parent) {
        // base: a leaf node,

        for (const auto &child: graph[node]) {
            if (child != parent) {
                int height = dfs(child, node);
                if (height > downpath[node].h1) {
                    downpath[node].h2 = downpath[node].h1;
                    downpath[node].h2node = downpath[node].h1node;
                    downpath[node].h1 = height;
                    downpath[node].h1node = child;
                } else if (height > downpath[node].h2) {
                    downpath[node].h2 = height;
                    downpath[node].h2node = child;
                }
            }
        }

        // Set the longest path given that current node is the common ancestor
        if (downpath[node].h2 != 0) {
            int pathLen = downpath[node].h1 + downpath[node].h2 + 1;
            if (pathLen >= maxPathLen) {
                if (pathLen > maxPathLen) {
                    maxPathLen = pathLen;
                    commonAncestors.assign({node});
                } else commonAncestors.push_back(node);
            }
        } else if (node == rootNode){
            // The common ancestor is the root when the path is between a leaf and the root.
            int pathLen = downpath[node].h1 + downpath[node].h2 + 1;
            if (pathLen > maxPathLen) {
                maxPathLen = pathLen;
                commonAncestors.assign({node});
            }
        }

        return downpath[node].h1 + 1;
    }

    inline int getKthDescendant(int node, int k) {
        // make sure that node has that many descendant
        while (k > 0) {
            node = downpath[node].h1node;
            --k;
        }
        return node;
    }

    void findMidOfLongestPaths(int n) {
        vector<bool> isMid(n, false);
        int halfLen = maxPathLen / 2;
        if (maxPathLen % 2 != 0) {
            for (auto ancestor: commonAncestors) {
                isMid[getKthDescendant(ancestor, downpath[ancestor].h1 - halfLen)] = true;
            }
        } else {
            for (auto ancestor: commonAncestors) {
                int firstMid = getKthDescendant(ancestor, downpath[ancestor].h1 - halfLen);
                isMid[firstMid] = true;
                isMid[downpath[firstMid].h1node] = true;
            }
        }

        ans.clear();
        for (int i = 0; i < n; ++i)
            if (isMid[i]) ans.push_back(i);
    }

    void buildGraph(int n, vector<pair<int, int>>& edges) {
        graph.clear();
        graph.resize(n, vector<int> {});
        for (const auto &edge: edges) {
            graph[edge.first].push_back(edge.second);
            graph[edge.second].push_back(edge.first);
        }
    }

public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n <= 0) return vector<int> {};

        // init
        buildGraph(n, edges);
        maxPathLen = 0;
        commonAncestors.clear();
        downpath.resize(n, (struct MaxTwoPaths) {0, -1, 0, -1});

        dfs(rootNode, rootNode);
        // for (auto &a: downpath)
        //     cout << a.h1node << ':' << a.h1 << ' ' << a.h2node << ':' << a.h2 << ',';
        // cout << endl;
        findMidOfLongestPaths(n);

        return ans;
    }
};

int main() {
    Solution solution;
    // vector<pair<int, int> > edges {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}}; //6
    // vector<pair<int, int> > edges {{1, 0}, {1, 2}, {1, 3}}; //4
    // vector<pair<int, int> > edges {}; // 1
    // vector<pair<int, int> > edges {{0,1},{0,2},{2,3},{0,4},{2,5},{5,6},{3,7},{0,8}}; //9
    vector<pair<int, int> > edges {{0,1},{0,2},{0,3},{2,4},{0,5},{5,6},{6,7},{2,8},{7,9}}; //10
    for (auto &a: solution.findMinHeightTrees(10, edges))
        cout << a << ' ';

    return 0;
}
