// N皇后问题

# include "leetcode.h"

class Solution {
public:
    vector<vector<string>> res;
    int N = 0;
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        string s(n, 'o');  // 用字符o表示可通行
        vector<string> curr(n, s);
        dfs(curr, 0);
        return res;
    }

    void dfs(vector<string> curr, int i){
        // curr 当前棋盘状态
        // i 已经放置的皇后个数 & 当前行数
        if(i == N){
            // 如果成功放置了n个皇后
            res.push_back(curr);
            return;
        }
        vector<string> curr_backup = curr;  // 备份，后面需要还原（回溯）
        for(int j=0; j<N; j++){
            if(curr[i][j] == 'o'){
                for(int row=0; row<N; row++)
                    for(int col=0; col<N; col++){
                        if(row==i || col==j || col==row+j-i || col==-row+i+j)
                            curr[row][col] = '.';  // 设置不可达
                    }
                curr[i][j] = 'Q';  // 放置一个皇后
                dfs(curr, i+1);
                curr = curr_backup;
            }
            else{
                continue;
            }
        }
    }
};


int main(){
    Solution s;
    vector<vector<string>> res = s.solveNQueens(8);
    for(auto v : res){
        for(auto s : v){
            cout << s << endl;
        }
        cout << endl << endl;
    }
    cout << res.size() << "组解" << endl;
}