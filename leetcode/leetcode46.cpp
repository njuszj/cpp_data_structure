// 全排列问题

# include "leetcode.h"


/*

class Solution {
public:
    vector<vector<int>> result;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> track;
        backtrack(nums, track);
        return result;
    }
    void backtrack(vector<int> nums, vector<int> track) {
        if(track.size() == nums.size()) {
            result.push_back(track);
            return;
        }
        int nums_size = nums.size();
        for(int i = 0; i < nums_size; ++ i) {
            //如果nums[i]没有出现在track中，即可供选择
            if(find(track.begin(), track.end(), nums[i]) == track.end()) {
                track.push_back(nums[i]);
                backtrack(nums, track);
                track.pop_back();
            }
        }
    }
};


作者：chen-fu-14
链接：https://leetcode-cn.com/problems/permutations/solution/cpp-hui-su-bi-jiao-qing-xi-by-chen-fu-14/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/



class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // 使用回溯解法，DFS+剪枝
        vector<vector<int>> res;

    }

    vector<vector<int>> permuteRecursion(vector<int>& nums) {
        // 暴力递归，太慢了!  内存占用也大
        // 回溯法
        vector<vector<int>> res;
        if(nums.size() == 1){
            vector<vector<int>> res = {{nums[0]}};
            return res;
        }
        for(int i=0; i<nums.size(); i++){
            int elem = nums[i];
            vector<int> tmp(nums);
            vector<int>::iterator itor = find(tmp.begin(), tmp.end(), elem);    
            tmp.erase(itor);
            vector<vector<int>> tmp_res = permute(tmp);
            for(int i=0; i<tmp_res.size(); i++){
                vector<int> tmp_sub_res(tmp_res[i]);                
                tmp_sub_res.insert(tmp_sub_res.begin(), elem);
                res.push_back(tmp_sub_res);
            }
        }
        return res;
    }   
};

int main(){
    vector<int> a = {1,2,3,4,5,6,7,8,9,0};
    Solution s;
    vector<vector<int>> res = s.permute(a);
    printDoubleVector(res);
}