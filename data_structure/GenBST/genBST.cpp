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

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>*& node){
    // 合并删除法，可能导致树的高度增加
    // *&表指针引用，为了可以改变指针的地址
    BSTNode<T> *tmp = node;
    if(node != 0){
        if(node->right == 0)
            node = node -> left; //如果没有右节点，那么直接替换为左节点
        else if(node->left == 0)
            node = node->right;  //如果没有左节点，那么直接替换为右节点
        else{
            // 既有左节点又有右节点
            tmp = node -> left;
            while(tmp->right != 0){
                // 前往左子树的最右节点,即左边最大节点
                tmp = tmp->right;
            }
            tmp->right = node->right;  //将原节点的右边转移给tmp
            tmp = node;
            node = node->left; //用原节点的左边替代原节点
        }
        delete tmp;
    }
}


template<class T>
void BST<T>::findAndDeleteByMerging(const T& e){
    // 通过值查找的方式删除节点，调用了上面的函数
    // 代码看似冗余，因为上面的search函数返回的是值(可是为什么不返回节点呢???)
    BSTNode<T> *node = root, *prev = 0;
    while(node!=0){
        if(node->key == e) break;
        prev = node;
        if(node->key < e)
            node = node->right;
        else
        {
            node = node->left;
        }
    }
    if(node != 0 && node->key == e){
        if(node == root)
            deleteByMerging(root);
        else if(prev->left == node)
            deleteByMerging(prev->left);  //为什么不直接传入node???
        else
        {
            deleteByMerging(prev->right);
        }
    else if(root != 0)
        cout << "key" << e << "is not found" << endl;
    else cout << "the tree is empty" << endl;
    }
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node){
    // 复制删除法，一般不会增加树的高度
    BSTNode<T> *prev, *tmp = node;
    if(node->right == 0)
        node = node->left;
    else if(node->left == 0)
        node = node->right;
    else{
        tmp = node -> left;
        prev = node;
        while(tmp->right !=0 ){
            prev = tmp;
            tmp = tmp -> right;
        }
        node->e = tmp->e;  //直接进行值的替换
        if(prev == node){
            prev->left = tmp->left;  // 如果左子树最大节点为第一个节点(即没有右节点)，需要转移
        }
        else
            prev->right = tmp->left; // 否则，也要对最大节点的左子树进行转移
    }
    delete tmp;  // 把左子树最大的节点删除
}


// 二叉树借助排序数组平衡
// 算法存在缺陷: 必须将数据放在数组中，还需要排序
template<class T>
void BST<T>::balance(T data[], int first, int last){
    if(first <= last){
        int middle = (first + last) / 2;
        insert(data[middle]);
        balance(data, first, middle-1);
        balance(data, middle+1, last);
    }
}

