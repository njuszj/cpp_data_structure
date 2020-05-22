// 从前序与中序遍历序列构造二叉树
// 你可以假设树中没有重复的元素
// 我选择使用递归解法
// 通过! 可惜时间复杂度较高， 使用下标而不是迭代器，避免拷贝应该能提升不少效率

/*
官方解法也是用的递归解答
class Solution {
  // start from first preorder element
  int pre_idx = 0;
  int[] preorder;
  int[] inorder;
  HashMap<Integer, Integer> idx_map = new HashMap<Integer, Integer>();

  public TreeNode helper(int in_left, int in_right) {
    // if there is no elements to construct subtrees
    if (in_left == in_right)
      return null;

    // pick up pre_idx element as a root
    int root_val = preorder[pre_idx];
    TreeNode root = new TreeNode(root_val);

    // root splits inorder list
    // into left and right subtrees
    int index = idx_map.get(root_val);

    // recursion 
    pre_idx++;
    // build left subtree
    root.left = helper(in_left, index);
    // build right subtree
    root.right = helper(index + 1, in_right);
    return root;
  }

  public TreeNode buildTree(int[] preorder, int[] inorder) {
    this.preorder = preorder;
    this.inorder = inorder;

    // build a hashmap value -> its index
    int idx = 0;
    for (Integer val : inorder)
      idx_map.put(val, idx++);
    return helper(0, inorder.length);
  }
}


作者：LeetCode
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/cong-qian-xu-he-zhong-xu-bian-li-xu-lie-gou-zao-er/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0) return NULL;
        TreeNode* node = new TreeNode(preorder[0]);
        if(preorder.size() == 1) return node;
        vector<int>::iterator mid_iter = find(inorder.begin(), inorder.end(), preorder[0]);  // 根节点
        int left_len = distance(inorder.begin(), mid_iter);
        cout << "left len " << left_len << endl;
        vector<int>::iterator right_iter = preorder.begin() + left_len;
        vector<int> left_preorder(preorder.begin()+1, right_iter+1);
        vector<int> right_preorder(right_iter+1, preorder.end());
        vector<int> left_inorder(inorder.begin(), mid_iter);
        vector<int> right_inorder(mid_iter+1, inorder.end());
        cout << "左子树长度" << left_preorder.size() << endl;
        cout << "右子树长度" << right_preorder.size() << endl;
        node->left = buildTree(left_preorder, left_inorder);
        node->right = buildTree(right_preorder, right_inorder);
        
        return node;
    }
};

int main(){
    vector<int> pre = {3,9,20,15,7};
    vector<int> in = {9,3,15,20,7};
    Solution s;
    s.buildTree(pre, in);
}