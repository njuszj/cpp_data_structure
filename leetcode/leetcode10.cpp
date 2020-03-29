/*
[s]: "aaa"
[p]: "ab*a*c*a"
[o]: true
*/

# include <iostream>
# include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        if(s.size()==0&&p.size()>0) return false;
        if(s.size()==0&&p.size()==0) return true;
        char pc, pc_next, sc;  // 取字符
    int pi=0, si=0, scnt=0, pcnt=0; // 下标

        while(pi<p.size()){
            pc = p[pi];
            if(si >= s.size())
                return false; // 如果s数组已经完成了但是p仍有元素，直接返回false
            if(pc == '*') continue;
            if(pi+1 < p.size()){
                // 当有下一个元素时
                pc_next = p[pi+1];  // 取下一个元素
                if(pc=='.'){
                    // 如果当前元素是通配.
                    if(pc_next=='*'){
                        if(pi+2 >= p.size()) return true;
                        else{
                            char pc_next_next = p[pi+2];
                            while(si<s.size() && (s[si] != pc_next_next))
                                si++;
                        }
                    }
                    else{
                        if(si<s.size()) si++; 
                    }           
                }
                else{
                    if(pc_next=='*'){
                        scnt=0;
                        pcnt=0;
                        while((si<s.size())&&(s[si]==pc)){
                            // 计算s中有多少个连续的pc
                            si++;
                            scnt++;
                        }
                        pi += 2;
                        while((pi<p.size())&&(p[pi]==pc)){
                            // 计算*号后面还有多少个字符与pc相同
                            pi++;
                            pcnt++;
                        }
                        if (scnt < pcnt) return false;
                        pi--; //因为最底下还有pi++, 这里先--
                    }
                    else if(s[si]==pc) si++;
                    else return false;
                }
            }
            else{
                //当已经是最后一个元素
                if(pc=='.')        
                    si++;
                else if(s[si]==pc) si++;
                else return false;
            }
            pi++;
        }
        if(si==s.size()) return true;
        else return false;
    }
};

int main(int argc, char** argv){
    Solution s;
    for(int i=0; i<argc; i++){
        cout << argv[i] << " ";
    }
    bool b = s.isMatch(argv[1], argv[2]);
    if(b)
        cout << "匹配成功" << endl;
    else
    {
        cout << "匹配失败" << endl;
    }
}