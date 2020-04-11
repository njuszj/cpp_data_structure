// 全排列II
# include "leetcode.h"

/*

class Solution {
    //参考
private:
    vector<vector<int>> res;
    vector<int> sol;
    vector<int> nums;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        this->nums = nums;
        vector<bool> used(nums.size(), false);
        dfs(used);
        return res;
    }
private:
    void dfs(vector<bool> used){
        if(sol.size() == nums.size()){
            res.push_back(sol);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            //当前值用过了 或 
            //当前值等于前一个值： 两种情况：
            //1 nums[i-1] 没用过 说明回溯到了同一层 此时接着用num[i] 则会与 同层用num[i-1] 重复
            //2 nums[i-1] 用过了 说明此时在num[i-1]的下一层 相等不会重复
            if(used[i] || (i>0 && !used[i-1] && nums[i] == nums[i-1])){//用过了
                continue;
            }
            sol.push_back(nums[i]);
            used[i] = true;
            dfs(used);
            sol.pop_back();
            used[i] = false;
        }
    }

*/ 


class Solution {
public:
    vector<vector<int>> res;
    int size=0;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        size = 
    }
};