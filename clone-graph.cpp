#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;


// Definition for undirected graph.
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {

    unordered_map<int, UndirectedGraphNode*> graphNodeFinder; // or unordered_map<UndirectedGraphNode*,UndirectedGraphNode*>

    // return copy of `node`
    UndirectedGraphNode * dfs(UndirectedGraphNode *node) {
        // requirement: node != NULL

        UndirectedGraphNode *nodeCopy;
        if (graphNodeFinder.find(node->label) != graphNodeFinder.end()) {
            nodeCopy = graphNodeFinder[node->label];
        } else {
            nodeCopy = new UndirectedGraphNode(node->label);
            graphNodeFinder[node->label] = nodeCopy;
            for (auto & neighbor: node->neighbors) {
                nodeCopy->neighbors.push_back(dfs(neighbor)); // ()
            }
        }
        return nodeCopy;
    }


public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return NULL;
        UndirectedGraphNode *graphNode = dfs(node);
        graphNodeFinder.clear();
        return graphNode;
    }
};

int main() {
    Solution solution;

    return 0;
}
