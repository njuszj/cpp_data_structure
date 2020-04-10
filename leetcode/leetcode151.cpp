// 反转单词
# include "leetcode.h"

class Solution {
public:
    string reverseWords(string s) {
        // 使用了栈，速度较慢，只击败了18%的C++选手
        stack<char> sWord;
        string res;
        for(int i=s.size()-1; i>=0; i--){
            if(s[i] != ' '){
                sWord.push(s[i]);
            }
            else{
                // 当前字符是空格
                if(sWord.size() == 0) continue;// 没有可以处理的内容
                else{
                    // 否则向res中添加栈里的内容
                    while(sWord.size()>0){
                        char elem = sWord.top();
                        res += elem;
                        sWord.pop();
                    }
                    res += ' ';  // 添加空格
                }
            }
        }
        if(sWord.size() >= 1){
            // 处理没有被空格触发的第一个单词
            while(sWord.size()>0){
                char elem = sWord.top();
                res += elem;
                sWord.pop();
            }
        }
        if (res.size()>0 && res[res.size()-1] == ' ') 
            res[res.size()-1] = '\0';  // 去除末尾的空格
        return res;
    }
};

int main(){
    string str_in = "fdk kxfvdf asd yh zlfgl  slkdflk";
    Solution s;
    string str_out = s.reverseWords(str_in);
    cout << str_out << endl;
}