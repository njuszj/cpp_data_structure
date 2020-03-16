#ifndef SPLAYING
#define SPLAYING

// 在二叉树中使用张开策略构建的词频统计

template<class T> class SplayTree;

template<class T>
class SplayingNode{
public:
    SplayingNode(){
        left = right = parent = 0;
    }
    SplayingNode(const T& e, SplayingNode *l = 0, SplayingNode *r = 0,
    SplayingNode *p = 0){
        info = e; left = l; right = r;parent = p;
    }
    T info;
    SplayingNode *left, *right, *parent;
};

template<class T>
class SplayTree{
public:
    SplayTree(){root=0}
    void inorder(){
        inorder(root);
    }
    T* search(const T&);
    void insert(const T&);
protected:
    SplayingNode<T> *root;
    void rotateR(SplayingNode<T>*);
    void rotateL(SplayingNode<T>*);
    void continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
            SplayingNode<T>* ch, SplayingNode<T>* desc);
    void semisplay(SplayingNode<T>*);
    void inorder(SplayingNode<T>*);
    void virtual visit(SplayingNode<T>*){}
};

#endif