# include "genBST.h"

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& e) const{
    while(p!=0){
        if(e == p->e) return &p->e;
        else if(e < p->e) p = p->left;
        else p = p->right;
    }
    return 0;
}

template<class T>
void BST<T>::breadthFirst(){
    // 使用队列和递归完成广度优先算法
    Queue<BSTNode<T>*> queue;
    BSTNode<T> *p = root;
    if(p != 0){
        queue.enqueue(p);
        while(!queue.empty()){
            p = queue.dequeue();
            visit(p);
            if(p->left != 0)
                queue.enqueue(p->left);
            if(p->right != 0)
                queue.enqueue(p->right);
        }
    }
}

template<class T>
void BST<T>::inorder(BSTNode<T>*p){
    if(p != 0){
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}

template<class T>
void BST<T>::preorder(BSTNode<T>*p){
    if(p != 0){
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>*p){
    if(p != 0){
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<class T>
void BST<T>::iterativePreorder(){
    // 使用非递归的方法前序遍历
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p = root;
    if(p != 0){
        travStack.push(p);
        while (!travStack.empty()){
            p = travStack.pop();
            visit(p);
            if (p->right != 0) travStack.push(p->right);
            if (p->left != 0) travStack.push(p->left);
        }
    }
}

template<class T>
void BST<T>::iterativePostorder(){
    //非递归实现的后序遍历
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root, *q = root;
    while(p != 0){
        for(; p->left != 0; p = p->left)
            travStack.push(p);  // 依次压入左节点
        while (p->right == 0 || p->right == q){
        // 因为是后序遍历，所以在没有右节点或者右节点已经被访问过的情况下才访问下一个节点
            visit(p);
            q = p;
            if(travStack.empty())
                return;
            p = travStack.pop();
        }
        travStack.push(p);
        p = p->right;
    }
}

template<class T>
void BST<T>::iterativeInorder(){
    //非递归实现的中序遍历，比较难懂
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p = root;
    while(p!=0){
        while(p!=0){
            //压人所有右节点
            if(p->right) travStack.push(p->right);
            travStack.push(p);
            p = p->left;
        }
        p = travStack.pop();  // 弹出一个没有左孩子的节点
        while(!travStack.empty() && p->right == 0){
            visit(p);  // 访问所有没有右孩子的节点
            p = travStack.pop();
        }
        visit(p);  // 访问第一个有右孩子的节点
        if(!travStack.empty())
            p = travStack.pop();
        else
            p = 0;
    }
}

template<class T>
void BST<T>::MorrisInorder(){
    //Morris提出来的不用栈实现的中序遍历
    BSTNode<T> *p = root, *tmp;
    while( p != 0)
        if(p->left == 0){
            visit(p);
            p = p -> right;
        }
        else{
            tmp = p->left;
            while(tmp->right != 0 && tmp->right != p)
                tmp = tmp->right; // 前往左子树的最右节点
            if(tmp->right == 0){
                tmp->right = p;
                p = p->left;
            }
            else{
                visit(p);
                tmp->right = 0;
                p = p->right;
            }
        }
}

template<class T>
void BST<T>::insert(const T& e){
    BSTNode<T> *p = root, *prev = 0;
    while(p != 0){
        prev = p;
        if(e < p->e)
            p = p->left;
        else
            p = p->right;
    }
    if(root == 0)
        root = new BSTNode<T>(e);
    else if(e < prev->e)
        prev->left = new BSTNode<T>(e);
    else
        prev->right = new BSTNode<T>(e);
}