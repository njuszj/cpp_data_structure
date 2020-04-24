// 最大连续子序列和
// 动态规划，通过

# include "leetcode.h"

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return 0;
        int max = nums[0];
        vector<int> d(size);  // d[j] 表示前j个元以最右边为结尾的最大子序和
        d[0] = nums[0];
        for(int j=1; j<size; j++){
            if(d[j-1] > 0)
                d[j] = d[j-1] + nums[j];
            else
            {
                d[j] = nums[j];
            }
            if(d[j] > max)
                max = d[j];
        }
        return max;
    }
};

int main(){
    vector<int> nums = {1,2,3,-1,-2,4,5,6};
    Solution s;
    int r = s.maxSubArray(nums);
    cout << r << endl;
}