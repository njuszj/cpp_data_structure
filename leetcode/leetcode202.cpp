// 快乐数
// 简单题，如果陷入一个环，则不是快乐数

# include "leetcode.h"

class Solution {
public:
    bool isHappy(int n) {
        set<int> trace;
        trace.insert(n);
        while(true){
            int r = squareSum(n);
            if(r == 1) return true;
            if(trace.find(r) == trace.end())
                trace.insert(r);
            else return false;
            n = r;
        }
    }
private:
    int squareSum(int n) {
        int res = 0;
        while(n > 0){
            int r = n % 10;
            res += r*r;
            n = n / 10;
        }
        return res;
    }
};

int main(){
    Solution s;
    bool x = s.isHappy(19);
    if(x)
        cout << "hhh" << endl;
}