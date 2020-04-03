// 合并k个有序链表

# include "leetcode.h"
# define NULL 0

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = NULL, *prev = NULL;
        int min = INT32_MAX, elem, flag = lists.size(), turn=0, index;
        if(lists.size()==0) return head;
        while(flag){
            min = INT32_MAX;
            flag = lists.size();  // 保存实际运算的次数
            for(int i=0; i<lists.size(); i++){
                if(!lists[i]) {
                    flag--;
                    continue;
                }
                elem = lists[i]->val;
                if(elem <= min){
                    min = elem;
                    index = i;  // 保存下标 
                }
            }
            lists[index] = lists[index]->next;
            ListNode node(min);
            if(turn == 0){
                head = &node;
                prev = &node;
            }
            else{
                prev->next = &node;
                prev = &node;
            }
            turn++;
        }
        return head;
    }
};