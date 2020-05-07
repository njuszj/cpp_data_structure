// 跳跃游戏II
// 贪心! 
// 非常巧妙的贪心

# include "leetcode.h"

class Solution {
public:
    int jump(vector<int>& nums) {
        int max_index = 0, i=0, next_i=0, cnt=0;
        int size = nums.size();
        while(i < size){
            next_i = i;
            for(int j=i+1; j<=nums[i]+i; j++){
                if(j >= size-1) return ++cnt;   // 已经可以到达了
                next_i = j+nums[j] > max_index ? j : next_i;   // 下一个i的位置， 是下一个能达到最远位置的位置
                max_index = max(j+nums[j], max_index);
            }
            i = next_i;
            cnt++;
        }
        return cnt;
    }
};