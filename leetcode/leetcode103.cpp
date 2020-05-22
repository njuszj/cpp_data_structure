// 二叉树锯齿形层次遍历
// 即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行
// 使用一个遍历队列，一个数据队列，数据队列随着层次变化决定是否转置

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> qTrace, qDataTrace;
        vector<vector<int>> res;
        int layer = 1;    //　层数，用于判断是否倒置
        if(root == NULL) return res;
        qTrace.push(root);
        qDataTrace.push(root);
        while(!qTrace.empty()){
            vector<int> sub_res;
            queue<TreeNode*> subQTrace;
            while(!qTrace.empty()){
                // 依次弹出结点，并压入子节点
                TreeNode* curr = qTrace.front();
                qTrace.pop();
                TreeNode* curr_data = qDataTrace.front();
                qDataTrace.pop();
                sub_res.push_back(curr_data->val);
                if(curr->left != NULL) subQTrace.push(curr->left);
                if(curr->right != NULL) subQTrace.push(curr->right);
            }
            qTrace = subQTrace;
            res.push_back(sub_res);
            if(layer % 2 == 1) {
                // 对于奇数层实行倒置
                stack<TreeNode*> tmp;
                while(!subQTrace.empty()){
                    tmp.push(subQTrace.front());
                    subQTrace.pop();
                }
                while(!tmp.empty()){
                    qDataTrace.push(tmp.top());
                    tmp.pop();
                }
            }
            else{
                // 偶数层按原顺序
                qDataTrace = subQTrace;
            }
            layer++;
        }
        return res;
    }
};