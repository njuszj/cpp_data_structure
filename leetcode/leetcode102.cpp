// 二叉树层次遍历
// 感觉就是BFS
// 区别就是，要注意层次切换的界限

/*
我们可以想到最朴素的方法是用一个二元组 (node, level) 来表示状态，
它表示某个节点和它所在的层数，每个新进队列的节点的 level 值都是父亲节点的 level 值加一。
最后根据每个点的 level 对点进行分类，分类的时候我们可以利用哈希表，维护一个以 level 为键，
对应节点值组成的数组为值，宽度优先搜索结束以后按键 level 从小到大取出所有值，组成答案返回即可

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal/solution/er-cha-shu-de-ceng-xu-bian-li-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> curr;
        queue<TreeNode*> nxt;
        vector<vector<int>> res;
        if(root == NULL) return res;
        curr.push(root);
        while(curr.empty() != 1){
            vector<int> sub_res;
            while(curr.empty() != 1){
                TreeNode* curr_node = curr.front();
                curr.pop();
                if(curr_node->left != NULL){
                    nxt.push(curr_node->left);
                    cout << "左压入: " << curr_node->left->val << endl;
                }
                if(curr_node->right != NULL){
                    nxt.push(curr_node->right);
                    cout << "右压入: " << curr_node->right->val << endl;
                }
                sub_res.push_back(curr_node->val);
            }
            while(nxt.empty() != 1){
                curr.push(nxt.front());
                nxt.pop();
            }
            res.push_back(sub_res);
        }
        return res;
    }
};