# include "genSplay.h"

template<class T>
void SplayTree<T>::continueRotation(SplayingNode<T>* gr, 
    SplayingNode<T>* par, SplayingNode<T>* ch, SplayingNode<T>* desc){
        if(gr != 0){
            //如果有一个祖父节点
            if(gr->right == ch->parent)
                //如果父节点是祖父节点的右孩子
                gr->right = ch;
            else
                gr->left = ch;
        }
        else root = ch;
        if(desc != 0)
            desc->parent = par;
        par->parent = ch;
        ch->parent = gr;
    }

template<class T>
void SplayTree<T>::rotateR(SplayingNode<T>* p){
    // 右旋
    p->parent->left = p->right;
    p->right = p->parent;
    continueRotation(p->parent->parent,p->right,p,p->right->left);
}

template<class T>
void SplayTree<T>::rotateL(SplayingNode<T>* p){
    p->parent->right = p->left;
    p->left = p->parent;
    continueRotation(p->parent->parent,p->left,p->left->right);
}

template<class T>
void SplayTree<T>::semisplay(SplayingNode<T>* p){
    while(p != root){
        if(p->parent->parent == 0)
            if(p->parent->left == p) // 如果p是根节点的左节点, 右旋
                rotateR(p);
            else
                rotateL(p);
        else if(p->parent->left == p) // 如果p是左节点
        {
            if(p->parent->parent->left == p->parent){
                //如果p的父节点是祖父的左孩子
                rotateR(p->parent);
                p = p->parent;
            }
            else{
                rotateR(p);
                rotateL(p);
            }
        }
        else{
            if(p->parent->parent->right == p->parent){
                rotateL(p->parent);
                p = p->parent;
            }
            else{
                rotateL(p);
                rotateR(p);
            }
        }
        if(root == 0)
            root = p;
    }
}

template<class T>
T* SplayTree<T>::search(const T& e){
    SplayingNode<T> *p = root;
    while(p != 0){
        if(p->info == e){
            semisplay(p); // 每次访问就更新树
            return &p->info;
        }
        else if(e < p->info)
            p = p->left;
        else
        {
            p = p->right;
        }
    }
    return 0;
}

template<class T>
void SplayTree<T>::insert(const T& e){
    SplayingNode<T> *p = root, *prev = 0, *newNode;
    while(p != 0){
        prev = p;
        if(e < p->info)
            p = p->left;
        else p = p->right;
    }
    if((newNode = new SplayingNode<T>(e, 0, 0, prev)) == 0){
        cerr << "No room for new node\n";
        exit(1);
    }
    if(root == 0)
        root = newNode;
    else if(e < prev->info)
        prev->left = newNode;
    else prev->right = newNode;
}

template<class T>
void SplayTree<T>::inorder(SplayingNode<T> *p){
    if(p!=0){
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}

