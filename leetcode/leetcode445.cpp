// 两数相加II

# include "leetcode.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int c = 0;  // 进位
        int num1, num2, num3;  // 数字
        if(l1 == NULL && l2 != NULL) return l2;
        if(l1 != NULL && l2 == NULL) return l1;
        if(l1 == NULL && l2 == NULL) return NULL;
        stack<int> s1, s2, s3;  // 用栈储存结果
        while(l1 != NULL){
            s1.push(l1->val);
            l1=l1->next;
        }
        while(l2 != NULL){
            s2.push(l2->val);
            l2=l2->next;
        }
        while(!s1.empty() || !s2.empty()){
            if(s1.empty()){
                // 如果s1用完了
                // 频繁的判断 空 可能是慢的原因
                num1 = 0;
            }
            else{
                num1 = s1.top(); 
                s1.pop();
            }
            if(s2.empty()){
                // 如果s2用完了
                num2 = 0;
            }
            else{
                num2 = s2.top();
                s2.pop();
            }
            num3 = num1 + num2 + c;
            if(num3 < 10){
                s3.push(num3);
                c = 0; // 不进位
            }
            else{
                s3.push(num3-10);
                c = 1; // 进位
            }
        }
        if(c==1) s3.push(1);
        ListNode* head = new ListNode(s3.top());
        ListNode* prev = head;
        s3.pop();
        while(!s3.empty()){
            ListNode* node = new ListNode(s3.top());
            s3.pop();
            prev->next = node;
            prev = node;
        }
        return head;
    }
};

int main(){
    Solution s;
    vector<int> nums1 = {1,2,3,4,5,6};
    ListNode* l1 = initList(nums1);
    vector<int> nums2 = {1,2,3,4,5,6};
    ListNode* l2 = initList(nums2);
    ListNode* l3 = s.addTwoNumbers(l1, l2);
    printList(l3);
}