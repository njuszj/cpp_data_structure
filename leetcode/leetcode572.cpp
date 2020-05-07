// 另一个树的子树
// 检测s中是否包含和t相同的子树

# include "leetcode.h"

class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(s == NULL) return false;
        bool res = false;
        if(s->val == t->val){
            res = func(s, t);
            if(res) return true;
        }
        res = isSubtree(s->left, t) || isSubtree(s->right, t);
        return res;
    }
private:
    bool func(TreeNode *s, TreeNode* t){
        if(t == NULL && s == NULL) return true;
        else if((t == NULL && s != NULL) || (t != NULL && s == NULL)) return false;
        if(s->val == t->val)
            return func(s->left, t->left) && func(s->right, t->right);
        else return false;
    }
};