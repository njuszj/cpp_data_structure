// 组合总和
// 元素都是正整数
// DFS + 回溯可解

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> res;
    int size, target;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        this->size = candidates.size();
        this->target = target;
        sort(candidates.begin(), candidates.end());
        vector<int> trace;
        dfs(candidates, 0, 0, trace);
        return res;
    }
    void dfs(vector<int> &nums, int start, int curr_sum, vector<int> trace){
        for(int i=start; i<size; i++){
            trace.push_back(nums[i]);
            if(nums[i]+curr_sum == target){
                res.push_back(trace);
            }
            else if(nums[i] + curr_sum > target){
                return;
            }
            dfs(nums, i, nums[i]+curr_sum, trace);
            trace.pop_back();
        }
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,2,3,4,5,6};
    vector<vector<int>> res = s.combinationSum(nums, 7);
    printDoubleVector(res);
}