// 二叉树的中序遍历
// 原来我连中序遍历都不会

/*

public class Solution {
    public List < Integer > inorderTraversal(TreeNode root) {
        List < Integer > res = new ArrayList < > ();
        Stack < TreeNode > stack = new Stack < > ();
        TreeNode curr = root;
        while (curr != null || !stack.isEmpty()) {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }
            curr = stack.pop();
            res.add(curr.val);
            curr = curr.right;
        }
        return res;
    }
}


作者：LeetCode
链接：https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/er-cha-shu-de-zhong-xu-bian-li-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> sTrace;
        TreeNode* curr = root;
        while(curr != NULL || !sTrace.empty()){
            while(curr != NULL){
                sTrace.push(curr);
                curr = curr->left;
            }
            curr = sTrace.top();
            sTrace.pop();
            res.push_back(curr->val);
            curr = curr->right;
        }
        return res;
    }
};