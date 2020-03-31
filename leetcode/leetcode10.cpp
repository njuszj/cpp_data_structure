/*
[s]: "aaa"
[p]: "ab*a*c*a"
[o]: true
*/

# include <iostream>
# include <string>
# include <stack>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int pi=0, si=0;
        char pc, sc, pc_next;
        stack<char> star;
        while(true){
            if(pi >= p.size())
                break;
            pc = p[pi];
            if(pc == '*')
                continue;
            if(pi+1 >= p.size()){
                if(s[si] == pc)
                    si++;
                else
            }
        }
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