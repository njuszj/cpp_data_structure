// 爬楼梯
// 经典问题，使用递归求解
// 但是，就如同斐波那契数列一样， 直接使用递归的时间复杂度太高了， 还是迭代吧

# include "leetcode.h"

class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        if(n > 2) {
            int cnt = 3, res = 0, curr = 2, prev = 1;
            while(cnt <= n){
                res = curr + prev;
                prev = curr;
                curr = res;
                cnt++;
            }
            return res;
        }
        return 0;
    }
};