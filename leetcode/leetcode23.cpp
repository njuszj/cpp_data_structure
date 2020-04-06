// 合并k个有序链表
// 通过,但是只击败了5%的选手,所以还要继续优化
// 考虑优先队列和分治法

# include "leetcode.h"

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
                    cout << elem << " " << i << endl;
                    min = elem;
                    index = i;  // 保存下标 
                }
            }
            if(!flag) continue;
            lists[index] = lists[index]->next;
            ListNode* node = new ListNode(min);
            if(turn == 0){
                head = node;
                prev = node;
            }
            else{
                prev->next = node;
                prev = node;
            }
            turn++;
        }
        return head;
    }
};

int main(){
    Solution s;
    vector<int> nums1 = {1,2,3,4,5,6};
    vector<int> nums2 = {2,3,4,5,6};
    ListNode* list1 = initList(nums1);
    ListNode* list2 = initList(nums2);
    vector<ListNode*> lists;
    lists.push_back(list1);
    lists.push_back(list2);
    ListNode* node = s.mergeKLists(lists);
    printList(node);
}