// 解压字符串
// 通过
/*
小Q想要给他的朋友发送一个神秘字符串，但是他发现字符串的过于长了，
于是小Q发明了一种压缩算法对字符串中重复的部分进行了压缩，
对于字符串中连续的m个相同字符串S将会压缩为[m|S](m为一个整数且1<=m<=100)，
例如字符串ABCABCABC将会被压缩为[3|ABC]，
现在小Q的同学收到了小Q发送过来的字符串，你能帮助他进行解压缩么？ 

输入第一行包含一个字符串s，代表压缩后的字符串。
S的长度<=1000;
S仅包含大写字母、[、]、|;
解压后的字符串长度不超过100000;
压缩递归层数不超过10层;

INPUT: HG[3|B[2|CA]]F
OUTPUT: HGBCACABCACABCACAF
*/


# include <iostream>
# include <string>
# include <stack>

using namespace std;

int main(){
    string s, res="", tmp="";
    stack<int> sIndex;  // 使用栈保存中括号的位置
    stack<int> sLine;   // 使用栈保存竖线的位置
    cin >> s;
    int i = 0;
    while(s[i] != '\0'){
        if(s[i]=='[')
            sIndex.push(i);
        else if(s[i] == '|')
            sLine.push(i);
        else if(s[i]==']'){
            int left = sIndex.top();
            sIndex.pop();  // 获得对应的左括号位置
            int mid = sLine.top();   // 获得竖线位置
            sLine.pop();
            int right = mid;
            tmp = s.substr(mid+1, i-mid-1);
            int times = stoi(s.substr(left+1 ,mid-left-1));
            string tmpc = tmp;
            for(int j=0; j<times-1; j++)
                tmp = tmp + tmpc;  // 构造重复times次的字符串
            s.erase(left, i-left+1);
            s.insert(left, tmp);  // 展开替换
            i = left + tmp.size() - 1;
        }
        i++;
    }
    
    cout << s << endl;    

}