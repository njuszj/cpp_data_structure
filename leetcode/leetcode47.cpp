// 全排列II
// 画出示意图，思考剪枝条件

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> res;
    int size = 0;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        size = nums.size();
        vector<int> used(size, 0);
        vector<int> trace;
        dfs(nums, trace, used);
        return res;
    }

    void dfs(vector<int>& nums, vector<int> trace, vector<int> used){
        if(trace.size() == size){
            res.push_back(trace);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            if(i>0 && nums[i] == nums[i-1] && used[i-1]==0){
                // 剪枝
                continue;
            }
            if(used[i]) continue;
            used[i]=1;
            trace.push_back(nums[i]);
            dfs(nums, trace, used);
            used[i]=0;
            trace.pop_back();
        }
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,2,2,3,5,4};
    vector<vector<int>> res = s.permuteUnique(nums);
    printDoubleVector(res);
}