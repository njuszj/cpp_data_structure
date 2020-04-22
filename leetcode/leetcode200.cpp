// 岛屿数量
// 错了! 没考虑遍历顺序
// 明天再想想吧^^
// 过了

# include "leetcode.h"

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nums = 0;
        if(grid.size() == 0) return 0;
        vector<bool> sub_used(grid[0].size()+2, false);
        vector<vector<bool>> used(grid.size()+2, sub_used);  // used数组记录哪些方块被使用
        vector<char> sub_grid(grid[0].size()+2, '0');
        vector<vector<char>> expand_grid(grid.size()+2, sub_grid);
        for(int i=0; i<grid.size(); i++){
            // 构造一个0包围的扩展结构
            for(int j=0; j<grid[i].size(); j++){
                expand_grid[i+1][j+1] = grid[i][j];
            }
        }
        for(int i=1; i<grid.size()+1; i++){
            for(int j=1; j<grid[i-1].size()+1; j++){
                if(expand_grid[i][j] == '1'){
                    if(used[i-1][j] == false 
                        && used[i+1][j] == false && used[i][j+1] == false
                        && used[i][j-1] == false){
                            nums++;
                        }
                    setUsed(used, expand_grid, i, j);
                }
            }
        }
        return nums;
    }

    void setUsed(vector<vector<bool>> &used, vector<vector<char>> &expand_grid, int i, int j){
        if(expand_grid[i][j] == '1' && used[i][j] == false) {
            used[i][j] = true;
            setUsed(used, expand_grid, i-1, j);
            setUsed(used, expand_grid, i+1, j);
            setUsed(used, expand_grid, i, j-1);
            setUsed(used, expand_grid, i, j+1);
        } 
        else return;
    }
};