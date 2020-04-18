// 子集
# include "leetcode.h"


class Solution {
public:
    int size=0;
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> trace;
        size = nums.size();
        dfs(0, nums, trace);
        return res;
    }

    void dfs(int start, vector<int>& nums,vector<int> trace){
        res.push_back(trace);
        for(int i=start; i<size; i++){
            trace.push_back(nums[i]);
            dfs(i+1, nums, trace);
            trace.pop_back();
        }
    }
};

int main(){
    vector<int> nums = {1, 3, 5,7,9,0,13,15,18,56,1347,438792,23478};
    Solution s;
    auto r = s.subsets(nums);
    printDoubleVector(r);
}