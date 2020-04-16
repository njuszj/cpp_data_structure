// 组合总和II
// 每个数字在每个组合中只能使用一次
# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> res;
    int size, target;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        this->size = candidates.size();
        this->target = target;
        sort(candidates.begin(), candidates.end());
        vector<int> trace;
        vector<bool> used(size, false);
        dfs(candidates, 0, 0, trace, used);
        return res;
    }
    void dfs(vector<int> &nums, int start, int curr_sum, vector<int> trace, vector<bool> used){
        for(int i=start; i<size; i++){
            if(i>0 && nums[i]==nums[i-1] && used[i-1]==false){
                continue;
            }
            trace.push_back(nums[i]);
            if(nums[i]+curr_sum == target){
                res.push_back(trace);
                return; 
            }
            else if(nums[i] + curr_sum > target){
                return;
            }
            used[i] = true;
            dfs(nums, i+1, nums[i]+curr_sum, trace, used);  // 把i改成i+1就是本题
            trace.pop_back();
            used[i] = false;
        }
    }
};

int main(){
    Solution s;
    vector<int> nums = {3,1,5,3,1,1};
    vector<vector<int>> res = s.combinationSum2(nums, 8);
    printDoubleVector(res);
}