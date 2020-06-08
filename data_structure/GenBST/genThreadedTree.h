// 二叉线索树
// 这里只需要一个指向中序后继的线索就足够了，所以也只需要一个标志位 successor

#ifndef THREADED_TREE
#define THREADED_TREE

template<class T>
class ThreadedNode{
public:
    ThreadedNode(){
        left = right = 0;
    }
    ThreadedNode(const T& e, ThreadNode *l = 0, ThreadedNode *r = 0){
        e = e; left = l; right = r; successor = 0;
    }
    T e;
    ThreadedNode *left, *right;
    unsigned int successor : 1;  // 标志是正常的指向后代还是一个线索
};

template<class T>
class ThreadedTree{
public:
    ThreadedTree(){
        root = 0;
    }
    void insert(const T&);
    void inorder();
protected:
    ThreadedNode<Node>* root;
};

#endif