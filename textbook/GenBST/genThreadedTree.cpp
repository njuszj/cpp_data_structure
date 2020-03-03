#include "genThreadedTree.h"

template<class T>
void ThreadedTree<T>::inorder(){
    // 线索树的中序遍历
    ThreadedNode<T> *prev, *p = root;
    if(p != 0){
        while(p->left != 0)
            p = p->left;  // 到最左边的节点
        while(p != 0){
            visit(p);
            prev = p;
            p = p->right;  // 右节点应该是中序后继
            if(p !=0 && prev->successor == 0) // 条件: p非空且正常指向后代
                while(p->left != 0)
                    p = p->left;
        }
    }
}

