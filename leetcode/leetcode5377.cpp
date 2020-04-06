// 将二进制表示减到 1 的步骤数
// 不需要真的右移,只要把表示最后一位的指针向前移动即可

# include "leetcode.h"
# include <unistd.h>

class Solution {
public:
    int numSteps(string s) {
        if (s=="1") return 0;
        int tail = s.size() - 1;
        int cnt=0;
        while(tail > 0){
            if(s[tail] == '0'){
                // 如果是偶数
                cnt++;
                tail--;  // 左移tail即可,不需要真的拷贝移位
            }
            else{
                // 如果是奇数
                cnt += 1;
                while(tail>=0 && s[tail]=='1') {
                    tail--;
                    cnt++;
                }
                if(tail>=0 && s[tail]=='0') s[tail] = '1';
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    int step = s.numSteps("1101010");
    cout << step << endl;
}