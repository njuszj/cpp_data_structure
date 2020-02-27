#include<iostream>
#include "intSLList.h"

IntSLList::~IntSLList(){
    for(IntSLLNode *p;!isEmpty();){
        p = head -> next;
        delete head;
        head = p;
    }
}

void IntSLList::addToHead(int e){
    head = new IntSLLNode(e, head);
    if(tail==0) tail = head;
}

void IntSLList::addToTail(int e){
    if(tail != 0){
        tail->next = new IntSLLNode(e);
        tail = tail->next;
    }
    else head = tail = new IntSLLNode(e);
}

int IntSLList::deleteFromHead(){
    int e = head -> info;
    IntSLLNode *temp = head;
    if (head==tail) head = tail = 0;
    else head = head -> next;
    delete temp;
    return e;
}

int IntSLList::deleteFromTail(){
    int e = tail -> info;
    if(head==tail) {
        delete head;
        head = tail = 0;
    }
    else{
        IntSLLNode *temp;
        for(temp=head;temp->next!=tail;temp=temp->next);
        delete tail;
        tail = temp;
        tail->next = 0;
    }
    return e;
}

void IntSLList::deleteNode(int e){
    if(head != 0){
        if(head==tail && e==head->info){
            delete head;
            head = tail = 0;
        }
        else if (e==head->info){
            IntSLLNode *temp = head;
            head = head -> next;
            delete temp;
        }
        else{
            IntSLLNode *pred, *temp;
            for(pred=head,temp=head->next;temp!=0&&!(temp->info==e);pred=pred->next,temp=temp->next);
            if(temp !=0 ){
                pred -> next = temp -> next;
                if (temp == tail) tail = pred;
                delete temp;
            }
        }
    }
}

bool IntSLList::isInList(int e) const {
    IntSLLNode *temp;
    for(temp=head;temp!=0 && !(temp->info==e);temp=temp->next);
    return temp != 0;
}