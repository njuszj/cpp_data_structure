// 字符串相乘
// 一开始的思路错了! 纯加法太耗时了，明天再想想吧
// 使用加法和补零代替乘法，通过! 但是只击败了8%的C++选手，还能优化
// 直接使用竖式乘法模拟效率更高

# include "leetcode.h"

class Solution {
public:
    string multiply(string num1, string num2) {
        string res = "0";
        if(num1 == "0" or num2 == "0") return res;
        int len1 = num1.size(), len2 = num2.size();
        if(len1 < len2) return multiply(num2, num1);   // 妙啊，可惜提升有限
        for(int i=0; i<len2; i++){
            int zero_num = (len2 - i -1);
            string tmp = "0";
            for(int j=0; j<(num2[i] - 48); j++){
                tmp = add(tmp, num1);
            }
            for(int j=0; j<zero_num; j++)
                tmp.push_back('0');
            res = add(res, tmp);
        }
    return res;
    }
private:
    string add(string num1, string num2) {
        string res;
        int len1 = num1.size(), len2 = num2.size(), c = 0, s = 0;
        int index = 1;
        int minlen = min(len1, len2);
        while(index <= minlen){
            s = (num1[len1-index] + num2[len2-index] + c - 96) % 10;
            c = (num1[len1-index] + num2[len2-index] + c - 96) / 10;
            res.push_back(static_cast<char>(s+48));
            index ++;
        }
        index--;
        if(len1 > len2){
            for(int i = len1 - index -1; i>=0; i--){
                s = (num1[i] + c - 48) % 10;
                c = (num1[i] + c - 48) / 10;
                res.push_back(static_cast<char>(s+48));
            }
        }
        else{
            for(int i = len2 - index -1; i>=0; i--){
                s = (num2[i] + c - 48) % 10;
                c = (num2[i] + c - 48) / 10;
                res.push_back(static_cast<char>(s+48));
            }
        }
        if(c == 1)
            res.push_back(static_cast<char>(c+48));
        reverse(res.begin(), res.end());
        return res;
    }
};

int main(){
    Solution s;
    string st = s.multiply("17865434567842342", "112431243232");
    cout << st << endl;
}

/*
cout << "add: " << num1[len1-index] << " and " 
                << num2[len2-index] << " res: "  << s << " c: " << c 
                << endl;
*/