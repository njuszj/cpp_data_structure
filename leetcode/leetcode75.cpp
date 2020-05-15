// 颜色分类
// 扫描到0就和头指针交换
// 扫描到2就和尾指针交换

# include "leetcode.h"

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int head = 0, tail = nums.size()-1;
        int index = 0;
        while(index <= tail){
            if(nums[index] == 0){
                if(index == head) {
                    // 其实不用担心head 超过 index 的问题
                    // 因为head在index之前已经扫描过了!!
                    ++head;
                    ++index;
                    continue;
                }
                int tmp = nums[head];
                nums[head++] = 0;
                nums[index] = tmp;
            }
            else if(nums[index] == 2){
                if(index == tail) break;
                int tmp = nums[tail];
                nums[tail--] = 2;
                nums[index] = tmp;
            }
            else{
                ++index;
            }
        }
    }
};

int main(){
    vector<int> a = {2,0,1,2,2,2,2,2};
    Solution s;
    s.sortColors(a);
    printVector(a);
}