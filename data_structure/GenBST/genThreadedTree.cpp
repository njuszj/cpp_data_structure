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

template<class T>
void ThreadedTree<T>::insert(const T& e){
    // 线索二叉树的插入操作
    ThreadedNode<T> *e, *prev = 0, *newNode;
    newNode = new ThreadedNode<T>(e);
    if(root == 0){
        root = newNode;
        return;
    }
    p = root;
    while(p != 0){
        prev = p;
        if(p->key > e)
            p = p->left;
        else if(p->successor == 0)
            p = p->right; // p的后继节点是正常的后代
        else baeak;
    }
    if(prev->key > e){
        prev->left  = newNode;
        newNode -> successor = 1;
        newNode -> right = prev;
    }
    else if(prev->successor == 1){
        newNode->successor = 1;
        prev->successor = 0;
        newNode->right = prev->right;
        prev->right = newNode;
    }
    else
    {
        prev->right = newNode;
    }
}

