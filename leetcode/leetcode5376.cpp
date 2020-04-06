// 非递增顺序的最小子序列

# include "leetcode.h"

class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        vector<int> res;
        if(nums.size() == 0) return res;
        sort(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int i = nums.size()-1, tmp=0;
        while(i >= 0){
            tmp += nums[i];
            res.push_back(nums[i]);
            if(tmp > sum - tmp){
                return res;
            }
            else{
                i--;
            }
        }
        return res;
    }
};