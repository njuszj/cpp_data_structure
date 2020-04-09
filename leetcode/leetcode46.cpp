# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        

    }

    void generateVector(vector<vector<int>> res, vector<int>& nums){
        for(int i=0; i<nums.size(); i++){
            int elem = nums[i];
            vector<int> tmp(nums);
            vector<int>::iterator itor = tmp.find(tmp.begin(), tmp.end(), elem);    
            tmp.erase(itor);
            
        }
    }
};