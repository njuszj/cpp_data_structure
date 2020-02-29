// 跳跃链表用于解决查找特定值困难的问题，是有序链表的扩展, 可以类比于平衡树
// 1/2节点只有一个指针，1/4节点有两个指针, 1/8节点有三个指针，..., maxLevel = floor(lg n) + 1

const int maxLevel = 4;  //设置最大级别数

template<class T>
class SkipListNode{
public:
    SkipListNode(){}
    T key;
    SkipListNode **next;  //两个指针，一个指向下一个(>)，一个指向同一层(<)
};

template<class T>
class SkipList{
public:
    SkipList();
    bool isEmpty() const;
    void choosePowers();  // 乘方
    int chooseLevel();  // 随机选层
    T* skipListSearch(const T&);
    void skipListInsert(const T&);
private:
    typedef SkipListNode<T> *nodePtr;
    nodePtr root[maxLevel];
    int powers[maxLevel];
};
