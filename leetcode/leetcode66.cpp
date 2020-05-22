// 整数数组+1
/**
 *更简洁的解法

 class Solution {
    public int[] plusOne(int[] digits) {
        for (int i = digits.length - 1; i >= 0; i--) {
            digits[i]++;
            digits[i] = digits[i] % 10;
            if (digits[i] != 0) return digits;
        }
        digits = new int[digits.length + 1];
        digits[0] = 1;
        return digits;
    }
}


作者：yhhzw
链接：https://leetcode-cn.com/problems/plus-one/solution/java-shu-xue-jie-ti-by-yhhzw/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

 */


# include "leetcode.h"

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int size = digits.size();
        if (size == 0) return res;
        int c = digits[size-1] == 9 ? 1 : 0;
        if(c == 0){
            for(int i=0; i<size; i++){
                if(i<size-1) res.push_back(digits[i]);
                else res.push_back(digits[i]+1);
            }
            return res;
        }
        else{
            int c = 1;
            for(int i=size-1; i>=0; i--){
                if(digits[i] == 9 && c == 1) res.push_back(0);
                else if(digits[i] != 9 && c == 1) {
                    c = 0;
                    res.push_back(digits[i] + 1);
                }
                else{
                    res.push_back(digits[i]);
                }
            }
            if(c == 1) res.push_back(1);
            reverse(res.begin(), res.end());
            return res; 
        }
        return res;
    }
};