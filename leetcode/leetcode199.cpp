// 二叉树的右视图
// 用bfs想法是对的，就是没有考虑怎么记录层数
// 通过了，看一下别人是怎么记录每层节点数量的
/*

while (!queue.isEmpty()) {
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            TreeNode node = queue.poll();
            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
            if (i == size - 1) {  //将当前层的最后一个节点放入结果列表
                res.add(node.val);
            }
        }
    }

作者：sweetiee
链接：https://leetcode-cn.com/problems/binary-tree-right-side-view/solution/jian-dan-bfsdfs-bi-xu-miao-dong-by-sweetiee/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"


class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        bfs(root, res);
        return res;
    }
    void bfs(TreeNode* root, vector<int>& res){
        // 使用广度优先遍历解决问题
        queue<int> qLayer;  // 需要用另一个队列来记录节点所在的层数
        int layer=1, prev_layer=0;
        queue<TreeNode*> qVal;
        TreeNode *curr = root, *prev = NULL;
        if(curr != NULL){
            qVal.push(curr);
            qLayer.push(layer);
            prev_layer = layer;
            prev = curr;
        }
        else return;
        while(qVal.empty() == 0){ 
            curr = qVal.front();
            qVal.pop();
            layer = qLayer.front();
            qLayer.pop();
            if(curr->left != NULL) {
                qLayer.push(layer+1);
                qVal.push(curr->left);
            }
            if(curr->right != NULL) {
                qLayer.push(layer+1);
                qVal.push(curr->right);
            }
            if(layer > prev_layer){
                // 如果换层了，即到达下一层最左边
                res.push_back(prev->val);
            }
            prev = curr;
            prev_layer = layer;
        }
        res.push_back(curr->val);
    }
};