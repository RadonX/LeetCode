#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

// segment tree
class NumArray {

    struct TreeNode {
        int i, j, mid, sum;
        TreeNode *left, *right;
        TreeNode(int i, int j, int sum, TreeNode *left = NULL, TreeNode *right = NULL)
            : i(i), j(j), mid((i+j)/2), sum(sum), left(left), right(right) {}
    };

    TreeNode* buildTree(int i, int j) {
        // make sure that in external call, i <= j and both i and j are valid indexes
        if (i == j) {
            return new TreeNode(i, j, nums[i]);
        }
        TreeNode *left = buildTree(i, (i+j)/2);
        TreeNode *right = buildTree((i+j)/2 + 1, j);
        return new TreeNode(i, j, left->sum + right->sum, left, right);
    }

    TreeNode *root;

    void updateTree(TreeNode *node, int i, int delta) {
        // external call guarantees that i in the range of node
        node->sum += delta;
        if (node->i == node->j) return;

        if (i <= node->mid) {
            updateTree(node->left, i, delta);
        } else {
            updateTree(node->right, i, delta);
        }
    }

    vector<int> nums;

    int getSum(TreeNode *node, int i, int j) {
        if ((i == node->i) && (j == node->j)) return node->sum;

        // external call guarantees that i and j in the range of node
        if (j <= node->mid) {
            return getSum(node->left, i, j);
        } else if (i <= node->mid) {
            return getSum(node->left, i, node->mid)
                    + getSum(node->right, node->mid + 1, j);
        } else {
            return getSum(node->right, i, j);
        }
    }

public:
    NumArray(vector<int> &nums) {
        if (nums.size() == 0) return;
        this->nums = nums; // copy
        root = buildTree(0, nums.size() - 1);
    }

    void update(int i, int val) {
        updateTree(root, i, val - nums[i]);
        nums[i] = val;
    }

    int sumRange(int i, int j) {
        return getSum(root, i, j);
    }
};


int main() {
    {
    vector<int> nums = {1,2,3,4};
    NumArray numArray(nums);
    cout << numArray.sumRange(0, 1) << ' ';
    numArray.update(1, 10);
    cout << numArray.sumRange(1, 2) << ' ';
    cout << endl;
    }

    vector<int> nums = {1,2,3,4,5,6,7,8};
    NumArray numArray(nums);
    cout << numArray.sumRange(1, 6) << ' ';
    numArray.update(0, 10);
    numArray.update(4, 4);
    cout << numArray.sumRange(1, 6) << ' ';
    cout << numArray.sumRange(0, 3) << ' ';
    cout << endl;

    return 0;
}
