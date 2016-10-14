
public int binarySearch(int[] nums, int target){
    while(left <= right) {
        mid = left + (right-­left)/2;
        midVal = getIthVal(matrix, mid);
        if(midVal == target)
            return true;
        else if(midVal > target)
            right = mid­-1;
        else
            left = mid+1;
    }
    return false;
}


// partition
private static int partition(Comparable[] elements, int start, int end) {
  int i = start + 1;
  int j = end;
  while (i <= j) {
    while (i <= j && less(elements[i], elements[start])) i++;
    while (i <= j && lessEqual(elements[start], elements[j])) j--;
    if (i < j) swap(elements, i, j);
  }
  swap(elements, start, j);
  return j;
}

// better partition
int partition(vector<int>& nums,int p,int r){
    pivot = nums[r];
    i = p - 1;
    for(j = p; j <= r; j++){
        if(nums[j] <= pivot){
            i++;
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }
    return i;
}

// tree traversal

TreeNode cur = root;
// 1. preorder
while (cur != null || !stack.isEmpty()) {
  if (cur == null) {
    cur = stack.pop();
  }
  result.add(cur.val);
  if (cur.right != null) {
    stack.add(cur.right);
  }
  cur = cur.left;
}
// 2. inorder
TreeNode cur = root;
while (cur != null || !stack.isEmpty()) {
    while (cur != null) {
      stack.push(cur);
      cur = cur.left;
    }
    cur = stack.pop();
    result.add(cur.val);
    cur = cur.right;
 }
// 3. postorder
if (root != null) {
    TreeNode prev = null;
    while (root != null || !stack.isEmpty()) {
      while (root != null) {
        stack.push(root);
        if (root.right != null) {
          stack.push(root.right);
        }
        root = root.left;
      }
      root = stack.pop();
      if ((root.left == null && root.right == null)
          || (prev != null && (prev == root.left || prev == root.right))) {
        result.add(root.val);
        prev = root;
        root = null;
      }
    }
}
