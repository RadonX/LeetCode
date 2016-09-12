#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

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
    void getMaxVal(TreeNode* node, int &f, int &g) {
        if (!node){
            f = 0;
            g = 0;
            return;
        }
        int fLeft, fRight, gLeft, gRight;
        getMaxVal(node->left, fLeft, gLeft);
        getMaxVal(node->right, fRight, gRight);
        f = node->val + gLeft + gRight;
        g = max(fLeft, gLeft) + max(fRight, gRight);
    }

public:
    int rob(TreeNode* root) {
        // f(node) =  node.val + g(node.left) + g(node.right)// with node
        // g(node) =  max(f(node.left),g(node.left)) + max(f(node.right),g(node.right)) // without node
        int f, g;
        getMaxVal(root, f, g);
        return max(f, g);
    }
};


int main() {
    Solution solution;

    return 0;
}
