// 括号生成
// DFS + 剪枝


# include <iostream>
# include <vector>
# include <string>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backTrack(res, "", n, 0, 0);
        return res;
    }

    void backTrack(vector<string> &res, string s, int n, int left, int right){
        // 回溯法
        if (right > left) return;
        if(s.size() == n * 2){
            res.push_back(s);
            return;
        }
        if(left < n){
            backTrack(res, s+"(", n, left+1, right);
        } 
        if(right < n){
            backTrack(res, s+")", n, left, right+1);
        }
    }
};

int main(){
    Solution s;
    vector<string> res = s.generateParenthesis(2);
    for(string elem : res)
        cout << elem << " ";
}