// 被围绕的区域
// 给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）
// 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充
// 思路 先把所有没被围住的O转化为F, 最后再转回来
// 通过!

# include "leetcode.h"

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() <= 2 || board[0].size() <= 2) return;
        rows = board.size(), cols = board[0].size();
        for(int i = 0; i < cols; i++){
            // 将边界的O全部换成F
            if(board[0][i] == 'O') {
                board[0][i] = 'F';
                transfer(board, 1, i);
            }
            if(board[rows-1][i] == 'O') {
                board[rows-1][i] = 'F';
                transfer(board, rows-2, i);
            }
        }
        for(int i = 0; i < rows; i++){
            if(board[i][0] == 'O') {
                board[i][0] = 'F';
                transfer(board, i, 1);
            }
            if(board[i][cols-1] == 'O') {
                board[i][cols-1] = 'F';
                transfer(board, i, cols-2);
            }
        }
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++){
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == 'F') board[i][j] = 'O';
            }
    }
private:
    int cols = 0, rows = 0;
    void transfer(vector<vector<char>>& board, int i, int j){
        if(i == 0 || j == 0 || i == rows-1 || j == cols-1) return;
        if(board[i][j] == 'X') return;
        board[i][j] = 'F';
        if(board[i+1][j] == 'O') transfer(board, i+1, j);
        if(board[i-1][j] == 'O') transfer(board, i-1, j);
        if(board[i][j+1] == 'O') transfer(board, i, j+1);
        if(board[i][j-1] == 'O') transfer(board, i, j-1);
    }
};