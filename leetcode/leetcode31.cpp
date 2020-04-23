// 下一个排列

# include "leetcode.h"

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        bool can_reach = false;
        if(nums.size() < 2) return;
        for(int start = nums.size()-2; start>=0; start--){
            findNextPermutation(can_reach, nums, start);
            if(can_reach) break;
        }
        if(can_reach == false){
            // 对最大序列的处理
            int i = 0;
            for(int j = nums.size()-1; j>=i; j--){
                swap(nums, i, j);
                i++;
            }
        }
    }

    void swap(vector<int>& nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp; 
    }

    void findNextPermutation(bool &can_reach, vector<int>& nums, int start) {
        // 下一个排列， 不同的是如果已经是最大序列，则什么也不做
        if(can_reach == false  && nums[start] >= nums[start+1]){
            // 全降序排列， 没有下一个排列
            return;
        }
        else{
            // 否则出现了升序序列
            for(int i = nums.size()-1; i>=start; i--){
                if(nums[i] > nums[start]){
                    swap(nums, start, i);
                    cout << "主交换: " << start << " " << i << endl;
                    for(int j = nums.size()-1; j>=start+1; j--){
                        // 使剩下的部分升序排列
                        swap(nums, start+1, j);
                        cout << "次交换: " << start+1 << " " << j << endl;
                        start++;
                    }
                    break;
                }
            }
            can_reach = true;
            return;
        }
    }
};

int main(){
    Solution s;
    vector<int> nums = {4,3,2,1};
    s.nextPermutation(nums);
    printVector(nums);
}