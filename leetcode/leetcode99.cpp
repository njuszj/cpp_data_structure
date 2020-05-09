// 恢复二叉搜索树
// 理解错了...这两个节点未必是相邻的
/* 解决方案1
1. 按中序遍历树。遍历后的数组应该是几乎排序的列表，其中只有两个元素被交换。
2. 在线性时间内确定几乎排序数组中的两个交换元素 x 和 y。
3. 再次遍历树，将值 x 的节点改为 y，将值 y 的节点改为 x。

作者：LeetCode
链接：https://leetcode-cn.com/problems/recover-binary-search-tree/solution/hui-fu-er-cha-sou-suo-shu-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
# include "leetcode.h"

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if(root == NULL) return;
        if(root->left != NULL){
            if(root->left->val <= root->val) recoverTree(root->left);
            else swap(root, root->left);
            return;
        }
        if(root->right != NULL){
            if(root->right->val >= root->val) recoverTree(root->right);
            else swap(root, root->right);
            return;
        }
    }
private:
    void swap(TreeNode* node1, TreeNode* node2){
        int tmp = node1->val;
        node1->val = node2->val;
        node2->val = tmp;
    }
};