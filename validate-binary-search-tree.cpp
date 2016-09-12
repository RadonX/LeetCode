#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // inorder
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> Stack;
        TreeNode *p = root;
        // vector<TreeNode*> inorder;
        int pre = INT_MIN, cur;
        bool first = true;
        while (p || !Stack.empty()) { // p is not in Stack
            if (p) { // -> while
                Stack.push(p);
                p = p->left;
            } else {
                p = Stack.top();
                Stack.pop();
                // inorder.push_back(p);
                cur = p->val;
                if (pre < cur || (first && pre == INT_MIN)) { // or use long
                    first = false;
                    pre = cur;
                } else return false;
                p = p->right;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;

    return 0;
}
