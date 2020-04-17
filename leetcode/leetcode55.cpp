// 跳跃游戏
// 超时了...
// 如果所有元素都不为0， 那么一定可以跳到最后(忽略了...)
// 从后往前遍历，如果遇到nums[i] = 0，就找i前面的元素j，使得nums[j] > i - j。如果找不到，则不可能跳跃到num[i+1]，返回false

# include "leetcode.h"

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size() == 0) return false;
        if(nums.size() == 1) return true;
        if(nums[0] == 0) return false;
        int flag = 0;
        for(int i=nums.size()-2; i>=0; i--){
            if(nums[i]==0){
                flag = 0;
                for(int j=i-1; j>=0; j--){
                    if(nums[j] > i-j){
                        // 可以跳过这个０
                        flag = 1;
                        continue;
                    }
                }
                if(flag==0) return false;
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<int> nums = {2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6};
    bool r = s.canJump(nums);
    if(r){
        cout << "可以跳跃" << endl;
    }
    else
    {
        cout << "不可到达" << endl;
    }
    
}