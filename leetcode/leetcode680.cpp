// 验证回文字符串
// 给定一个非空字符串 s， 最多删除一个字符。判断是否能成为回文字符串
// 我使用了左右指针法，通过移动指针模拟删除

/*



*/

# include "leetcode.h"

class Solution {
public:
    bool validPalindrome(string s) {
        int right = s.size() - 1, left = 0;
        while(left < right){
            if(s[left] == s[right]){
                left++;
                right--;
                continue;
            }
            else{
                break;
            }
        }
        if(left >= right) return true;
        int bleft = left, bright = right;  // 保存当时的指针
        left++;  // 删除左边的元素
        int flag = 1;
        while(left < right){
            if(s[left] == s[right]){
                left++;
                right--;
                continue;
            }
            else{
                flag = 0;
                break;
            }
        }
        if(flag == 1) return true;  // 删除后达成回文
        else{
            left = bleft;
            right = bright;
            right --;   // 删除右边的元素
            while(left < right){
                if(s[left] == s[right]){
                    left++;
                    right--;
                    continue;
                }
                else{
                    return false;
                }
            }
            return true;
        }
        return true;
    }
};