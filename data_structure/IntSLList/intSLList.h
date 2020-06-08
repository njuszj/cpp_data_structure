#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

// 单向链表

class IntSLLNode{
    //链表节点结构
public:
    IntSLLNode(){
        next = 0;
    }
    IntSLLNode(int e, IntSLLNode *ptr=0){
        info = e;
        next = ptr;
    }
    int info;
    IntSLLNode *next;
};

class IntSLList{
public:
    IntSLList(){
        head = tail = 0;
    }
    ~IntSLList();
    int isEmpty(){
        return head == 0;
    }
    void addToHead(int);
    void addToTail(int);
    int deleteFromHead();
    int deleteFromTail();
    void deleteNode(int);
    bool isInList(int) const;
private:
    IntSLLNode *head, *tail;
};

#endif