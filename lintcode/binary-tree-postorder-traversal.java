// https://www.jiuzhang.com/solution/binary-tree-postorder-traversal/#tag-highlight-lang-cpp
// 81.8%, 4.8%

/**
 * Definition of TreeNode:
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left, right;
 *     public TreeNode(int val) {
 *         this.val = val;
 *         this.left = this.right = null;
 *     }
 * }
 */

public class Solution {

    List<TreeNode> stack;

    private TreeNode stackTop() {
        return stack.get(stack.size()-1);
    }

    private void stackPop() {
        stack.remove(stack.size()-1);
    }

    /**
     * @param root: A Tree
     * @return: Postorder in ArrayList which contains node values.
     */
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList();
        if (root == null) {
            return ans;
        }
        TreeNode p = null;
        stack = new ArrayList<>();
        stack.add(root);
        while (!stack.isEmpty()) {
            TreeNode node = stackTop();
            if (hasVisited(node, p)) {
                ans.add(node.val);
                p = node;
                stackPop();
            } else {
                if (node.right != null) {
                    stack.add(node.right);
                }
                if (node.left != null) {
                    stack.add(node.left);
                }
            }
        }
        return ans;
    }

    private boolean hasVisited(TreeNode node, TreeNode prev) {
        if (node.right != null) {
            return (node.right == prev);
        } else {
            if (node.left != null) {
                return (node.left == prev);
            } else {
                return true;
            }
        }
    }

}
