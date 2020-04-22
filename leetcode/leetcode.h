# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
# include <numeric>
# include <map>
# include <stack>
# include <queue>
# include <set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

ListNode* initList(vector<int> nums){
    ListNode* head = new ListNode(nums[0]);
    ListNode* prev = head;
    for(int i=1; i<nums.size(); i++){
        ListNode* node = new ListNode(nums[i]);
        prev->next = node;
        prev = node;
    }
    return head;
}

void printList(ListNode* node){
    while(node != NULL){
        cout << node->val;
        node = node->next;
    }
}

void printDoubleVector(vector<vector<int>> a){
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<a[i].size(); j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

template<class T>
void printVector(vector<T> nums){
    for(T k : nums)
        cout << k << " ";
    cout << endl;
}