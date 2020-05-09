// 对称二叉树
// 是镜像对称不是相同!
// 先交换各个节点，再判断相同即可

/*
更简单的迭代解法（JAVA）
public boolean isSymmetric(TreeNode root) {
    return isMirror(root, root);
}

public boolean isMirror(TreeNode t1, TreeNode t2) {
    if (t1 == null && t2 == null) return true;
    if (t1 == null || t2 == null) return false;
    return (t1.val == t2.val)
        && isMirror(t1.right, t2.left)
        && isMirror(t1.left, t2.right);
}


作者：LeetCode
链接：https://leetcode-cn.com/problems/symmetric-tree/solution/dui-cheng-er-cha-shu-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

# include "leetcode.h"

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        TreeNode* tmp = root->left;
        swap(tmp);
        return isSame(tmp, root->right);
    }
private:
    bool isSame(TreeNode* node1, TreeNode* node2){
        if(node1 == NULL && node2 == NULL) return true;
        if(node1 == NULL || node2 == NULL) return false;
        if(node1->val != node2->val) return false;
        else return isSame(node1->left, node2->left) && 
                isSame(node1->right, node2->right);
    }
    void swap(TreeNode* node){
        if(node == NULL) return;
        TreeNode* tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        swap(node->left);
        swap(node->right);
    }
};