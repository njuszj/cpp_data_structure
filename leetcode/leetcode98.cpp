// 验证二叉搜索树
// 二叉搜索树的中序遍历应该是一个升序数组
// 官方解答确认了我的想法是正确的，通过!
// 给出的另一种使用递归的解法

/*

class Solution {
public:
    bool helper(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) return true;
        if (root -> val <= lower || root -> val >= upper) return false;
        return helper(root -> left, lower, root -> val) && helper(root -> right, root -> val, upper);
    }
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/validate-binary-search-tree/solution/yan-zheng-er-cha-sou-suo-shu-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        while(!sVal.empty()) sVal.pop();
        inOrderVisit(root);
        int prev=0, curr=0;
        if(sVal.size() <= 1) return true;
        prev = sVal.top();
        sVal.pop();
        while(!sVal.empty()){
            curr = sVal.top();
            sVal.pop();
            if(prev <= curr) return false;
            prev = curr;
        }
        return true;
    }
private:
    stack<int> sVal;
    void inOrderVisit(TreeNode* root){
        if(root != NULL){
            inOrderVisit(root->left);
            sVal.push(root->val);
            inOrderVisit(root->right);
        }
        else return;
    }
};
