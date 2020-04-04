/*
链接：https://www.nowcoder.com/questionTerminal/6f0d16fc06274f44af8913d182668037
来源：牛客网

小明最近在做病毒自动检测，他发现，在某些library 的代码段的二进制表示中，如果包含子串并且恰好有k个1，就有可能有潜在的病毒。library的二进制表示可能很大，并且子串可能很多，人工分析不可能，于是他想写个程序来先算算到底有多少个子串满足条件。如果子串内容相同，但是开始或者结束位置不一样，则被认为是不同的子串。
注：子串一定是连续的。例如"010"有6个子串，分别是 "0, "1", "0", "01", "10", "010"

输入描述:

第一行是一个整数k，表示子串中有k个1就有可能是病毒。其中 0 <= k <= 1 000 000
第二行是一个字符串，就是library的代码部分的二进制表示。字符串长度 <= 1 000 000。并且字符串中只包含"0"或"1".

示例:
输入
1
1010
输出
6
说明
满足条件的子串有："1", "1", "10", "01", "10", "010".
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int k, zero_cnt = 0;
    long long res = 0;
    string s;
    char ch;
    cin >> k;
    cin >> s;
    vector<int> keys, zeros;  //分别记录1的位置和1前面的0的个数
    for(int i=0;i<s.length();i++){
        ch = s[i];
        if(ch == '1') {
            keys.push_back(i);
            zeros.push_back(zero_cnt);
            zero_cnt = 0;  //计数归零
        }
        else if(ch == '0') zero_cnt += 1;
    }
    if(ch == '0') zeros.push_back(zero_cnt);
    else zeros.push_back(0);

    if(k == 0){
        long long num;
        for(int i=0;i<zeros.size();i++){
            num = zeros[i];
            res += num * (num + 1) / 2;
        }
    }
    else if(keys.size() < k) res = 0;
    else{
        int i = 0, j = k-1;
        while(j < keys.size()){
            res += (zeros[i] + 1) * (zeros[j+1] + 1);
            i++; j++;
        }
    }
    cout << res;
    return 0;
}