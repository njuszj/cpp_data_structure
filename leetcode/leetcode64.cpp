// 最小路径和
/*
给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。
*/
// 不会写...毫无头绪
// 使用动态规划!
// 使用dp(i,j) 表示从坐标 (i,j) 到右下角的最小路径权值
// 递推公式 dp(i,j) = grid(i,j) + min(dp(i+1,j),dp(i,j+1))
// 很好地帮助自己理解动态规划

#include "leetcode.h"

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        if(rows == 0) return 0;
        int cols = grid[0].size();
        vector<int> sub_dp(cols);
        vector<vector<int>> dp(rows, sub_dp);
        dp[rows-1][cols-1] = grid[rows-1][cols-1];
        for(int i=rows-2; i>=0; i--)
            dp[i][cols-1] = grid[i][cols-1] + dp[i+1][cols-1];
            // 初始化最后一列
        for(int j=cols-2; j>=0; j--)
            dp[rows-1][j] = grid[rows-1][j] + dp[rows-1][j+1];
            // 初始化最后一行
        for(int i=rows-2; i>=0; i--)
            for(int j=cols-2; j>=0; j--)
                dp[i][j] = grid[i][j] + min(dp[i+1][j], dp[i][j+1]);
        return dp[0][0];
    }
};