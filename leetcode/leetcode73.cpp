// 矩阵置0
// 空间复杂度1的做法
// 遍历整个矩阵，如果 cell[i][j] == 0 就将第 i 行和第 j 列的第一个元素标记  

# include "leetcode.h"

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        set<int> rZero;
        set<int> cZero;
        int rows = matrix.size();
        int cols = matrix[0].size();
        if (rows == 0) return;
        int r = 0;
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if(matrix[i][j] == 0){
                    rZero.insert(i);
                    cZero.insert(j);
                }
            }
        }
        set<int>::iterator iter;
        for(iter = rZero.begin(); iter != rZero.end(); iter++){
            int r = *iter;
            for(int i=0; i<cols; i++) matrix[r][i] = 0;
        }
        for(iter = cZero.begin(); iter != cZero.end(); iter++){
            int c = *iter;
            for(int i=0; i<rows; i++) matrix[i][c] = 0;
        }
    }        
};