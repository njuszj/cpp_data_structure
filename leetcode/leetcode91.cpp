// 解码方法
// 不会写...还没考虑0这种情况
// 用...动态规划！
// 这是一个约束版的肥波数列

# include "leetcode.h"

class Solution {
public:
    int numDecodings(string s) {
        int res = 1, curr = 0, size=s.size();
        while(1){
            while(curr < size && s[curr] > '2') curr++;
            if(curr == size) break;
            int next = curr;
            while(next < size && s[next] <= '2') next++;

        }
        
    }
};