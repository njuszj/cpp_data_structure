// 最接近的三数之和
// 想到的第一个办法: 二分查找，找最接近target-n1-n2之间的元素
// 失败，还是双指针吧
# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        vector<int>::iterator tail = nums.end() - 1, head=nums.begin();    
        vector<int>::iterator mid;
        int sum;
        for(; head != nums.end()-2; head++){
            sum = *head + *tail;
            mid = closestHalfSearch(nums, head, tail, target-sum);
        }
    }
    vector<int>::iterator closestHalfSearch(vector<int>& nums, vector<int>::iterator head, 
            vector<int>::iterator tail, int target){
        // 最接近的二分查找
        vector<int>::iterator head = nums.begin(), tail = nums.end()-1,
            mid = nums.begin() + static_cast<int>(nums.size()/2);
        while(head != tail){
            if(*mid == target) return mid;
            else if(*mid > target)
                tail = mid - 1;
            else
            {
                head = mid + 1;
            }
            int d = distance(head, tail);
            mid = head + d / 2;
        }
        return tail;
    }
};