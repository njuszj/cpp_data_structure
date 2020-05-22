// 组合
// 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合
// dfs解法，回溯+剪枝
# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> nums(n+1);
        for(int i=1; i<=n; i++) nums[i] = i;
        vector<int> emp;
        dfs(res, nums, emp, 1, k);
        return res;
    }
private:
    void dfs(vector<vector<int>>& res, vector<int>& nums, 
                vector<int> tmp,int index, int k){
        if(tmp.size() == k) {
            res.push_back(tmp);
            return;
        }
        if(nums.size() - index + 1 < k - tmp.size()) return;
        for(int i=index; i<nums.size(); i++){
            tmp.push_back(nums[i]);
            dfs(res, nums, tmp, i+1, k);
            tmp.pop_back();
        }
    }
};

int main(){
    Solution s;
    vector<vector<int>> r = s.combine(10,5);
    printDoubleVector(r);
}