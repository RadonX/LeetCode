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
    unordered_map<int, int> indInorder;

    TreeNode* makeTree(vector<int>& preorder, int preStart, vector<int>& inorder, int inStart, int len) {
        if (len == 0) return NULL;
        int parent = preorder[preStart];
        int parentInd = indInorder.find(parent)->second; 
        TreeNode *parentNode = new TreeNode(parent);
        parentNode->left = makeTree(preorder, preStart + 1, inorder, inStart, parentInd - inStart);
        parentNode->right = makeTree(preorder, preStart + 1 + parentInd - inStart, inorder, parentInd + 1, inStart + len - parentInd - 1);
        return parentNode;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        indInorder.clear();
        for (int i = 0; i < inorder.size(); ++i) {
            indInorder[inorder[i]] = i;
        }
        return makeTree(preorder, 0, inorder, 0, inorder.size());
    }
};

// class Solution {
//     // vector<int>::iterator itPreorder, itInorder;
//
//     TreeNode* getMostRightTree(vector<int>::iterator itPreMostRight, vector<int>::iterator itInMostRight) {
//         if (*itPreMostRight == *itInMostRight) { // most right node is a leaf
//             return makeNode(itPreMostRight);
//         } else {
//             return NULL; // most right node is NULL
//         }
//     }
//
//     void getTree(vector<int>::iterator itPreMostRight, vector<int>::iterator itInMostRight, int len) {
//         TreeNode *mostRightNode = getMostRightTree(itPreMostRight, itInMostRight);
//         if (mostRightNode) {
//             --len;
//             prev(itPreMostRight);
//             prev(itInMostRight);
//         }
//         // if len < 0
//         TreeNode *parent = getParent(itInMostRight);
//         prev(itInMostRight);
//         --len;
//         // parent --> right
//
//
//         getLeftSibling(next(itPreorder), itInorder, parentInd);
//     }
//
// public:
//     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//         itPreorder = preorder.begin();
//         itInorder = inorder.begin();
//
//     }
// };

int main() {
    Solution solution;

    return 0;
}
