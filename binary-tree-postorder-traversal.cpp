#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

stack<TreeNode*> Stack;

public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        // order: mid, right, left
        TreeNode *ptr = root; // node not yet output or pushed to stack
        while (!Stack.empty() || ptr) {
            if (ptr) {
                ans.push_back(ptr->val); // each node can only be visited once
                Stack.push(ptr->left); // all left children will be popped after mid/right visited
                ptr = ptr->right;
            } else {
                ptr = Stack.top(); // a left child
                Stack.pop();
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution solution;

    return 0;
}
