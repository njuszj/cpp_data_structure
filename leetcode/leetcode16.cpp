// 最接近的三数之和
// 想到的第一个办法: 二分查找，找最接近target-n1-n2之间的元素
// 失败，还是双指针吧
# include <iostream>
# include <vector>
# include <algorithm>
# include<numeric>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int sum, sub;
        if(nums.size() < 3) return accumulate(nums.begin(), nums.end(), 0);
        int res = accumulate(nums.begin(), nums.begin()+3, 0);
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size()-2;i++){
            int k = nums.size()-1, j=i+1;
            while(k>j){
                // cout << i << j << k << endl;
                sum = nums[i]+nums[j]+nums[k];
                if(sum == target) return sum;
                else if(sum < target) j++;
                else k--;
                sub = abs(sum - target);
                if(sub < abs(res-target))
                    res = sum;
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums = {1,2,3,4,5,6};
    Solution s;
    int a = s.threeSumClosest(nums, 99);
    cout << a << endl;
}