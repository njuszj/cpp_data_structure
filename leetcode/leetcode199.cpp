// 二叉树的右视图
// 用bfs想法是对的，就是没有考虑怎么记录层数


# include "leetcode.h"


class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        bfs(root, res);
    }
    void bfs(TreeNode* root, vector<int> res){
        // 使用广度优先遍历解决问题
        queue<TreeNode*> qVal;
        TreeNode* curr = root;
        if(curr != NULL){
            qVal.push(curr);
            res.push_back(curr->val);
        }
        while(qVal.empty() == 0){ 
            curr = qVal.front();
            qVal.pop();
            if(curr->left != NULL) qVal.push(curr->left);
            if(curr->right != NULL) qVal.push(curr->right);
        }
    }
};