// 通用二叉查找树

# include <queue>
# include <stack>

using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template<class T>
class Stack : public stack<T> {
public:
    T pop(){
        T tmp = top();
        stack<T>::pop();  // 这里使用域作用符是因为与函数名重名了
        return tmp;
    }
};

template<class T>
class Queue : public queue<T> {
public:
    T dequeue(){
        T tmp = front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& e){
        push(e);
    }
};

template<class T>
class BSTNode{
public:
    BSTNode(){
        left = right = 0;
    }
    BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0){
        e = e; left = l; right = r;
    }
    T e;
    BSTNode<T> *left, *right; //直接声明为public变量了，便于从外部访问
};

template<class T>
class BST{
public:
    BST(){
        root = 0;
    }
    ~BST(){
        clear();
    }
    void clear(){
        clear(root); root = 0;
    }

    bool isEmpty() const{
        return root == 0;
    }

    void preorder(){
        
    }
} 

#endif