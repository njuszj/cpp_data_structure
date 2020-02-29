// 跳跃链表实现
// 1/2节点只有一个指针，1/4节点有两个指针, 1/8节点有三个指针，..., maxLevel = floor(lg n) + 1

const int maxLevel = 4;

template<class T>
class SkipListNode{
public:
    SkipListNode(){}
    T key;
    SkipListNode **next;
};

template<class T>
class SkipList{
public:
    SkipList();
    bool isEmpty() const;
    void choosePowers();
    int chooseLevel();
    T* skipListSearch(const T&);
    void skipListInsert(const T&);
private:
    typedef SkipListNode<T> *nodePtr;
    nodePtr root[maxLevel];
    int powers[maxLevel];
};
