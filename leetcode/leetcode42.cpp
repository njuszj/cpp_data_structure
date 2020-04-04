// 下雨问题
/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
Example:
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

// leetcode 题解思路: 每一格储水量等于左边最大值和右边最大值的较小者
// 基于这个思路进一步优化，采用双指针完成一次遍历
# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int elem, max, min, sum=0, res=0;
        if(height.size() < 3) return 0;
        for(int i=0; i<height.size()-1; i++){
            // 假设i的位置为合理的水位开始
            if(height[i] <= height[i+1]) continue;
            int j = i+1;
            max = i+1;   // 记录最大值位置
            while(j<height.size() && height[j] < height[i]){
                if(height[j] >= height[max])
                    max = j;
                j++;
            }  // 一直找到比i位置大的j
            if(j<height.size() && height[j] >= height[max]) max = j;
            sum = 0;
            min = height[i] < height[max] ? height[i] : height[max];
            // cout << "max: " << max << " i:" << i << " min" << min << endl;
            for(int k=i+1; k<max; k++)
                sum += min - height[k];
            res += sum;
            i = max; // 移位
            i--;
        }
        return res;
    }
};

int main(){
    vector<int> nums = {5,4,1,2};
    Solution s;
    int res = s.trap(nums);
    cout << res << endl;    
}