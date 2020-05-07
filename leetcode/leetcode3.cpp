// 无重复的最长子串
// 官解: 使用滑动窗口(左右指针)
# include "leetcode.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start = 0, i = 0, maxnum = 0;
        while(i < s.size()){
            int flag = 0;
            char c = s[i];
            for(int j=start; j<i; j++){
                if(s[j] == c){
                    start = j + 1;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) maxnum = maxnum > (i-start+1) ? maxnum : (i-start+1);
            i++;
        }
        return maxnum;
    }
};