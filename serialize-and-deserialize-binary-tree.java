// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }


 21345
 21543
 23145
 23154
 23415
 23451
 23541
 ...
 25431

preorder but with leaf node (null)
1 [2 [3 [n n] 4] n  ] n
 */
public class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {

    }

    private static class ReturnNode {
        TreeNode node;
        int size; // includes null leave nodes
    }

    private String IntegerArrayToString(Integer[] values) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        for(int i=0; i < values.length; ++i)
        {
             dos.writeInt(values[i]);
        }

        return baos.toByteArray();
    }

    private Integer[] stringToIntegerArray(String data) {
        byte[] bytes = data.getBytes();
        int byteSize = bytes.length;
        Integer[] values = new Integer[byteSize];
        int j = 0;
        for (int i = 0; i < byteSize; ) {
            if (byte[i] == 0) {
                values[j++] = null;
                i++;
            } else {
                int baseIndex = i+1;
                values[j++] = ((bytes[baseIndex] & 0xFF) << 24) |
                    ((bytes[baseIndex+1] & 0xFF) << 16) |
                    ((bytes[baseIndex+2] & 0xFF) << 8 ) |
                    ((bytes[baseIndex+3] & 0xFF) << 0 );
                i += 5;
            }
        }
        values = Arrays.copyOf(values, j);
        return values;
    }

    private ReturnNode buildTree(Integer[] values, int rootIndex) {
        if (values[rootIndex] == null) {
            ReturnNode rootNode = new ReturnNode();
            rootNode.size = 1;
            return rootNode;
        }
        TreeNode root = new TreeNode(values[rootIndex]);
        ReturnNode leftNode = buildTree(values, rootIndex + 1);
        root.left = leftNode.node;
        ReturnNode rightNode = buildTree(values, rootIndex + 1 + leftNode.size);
        root.right = rightNode.node;
        ReturnNode rootNode = new ReturnNode();
        rootNode.node = root;
        rootNode.size = 1 + leftNode.size + rightNode.size;
        return rootNode;
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        Integer[] values = stringToIntegerArray(data);
        ReturnNode rootNode = buildTree(values, 0);
        return rootNode.node;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
