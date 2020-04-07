// 旋转矩阵
# include "leetcode.h"


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size()==0) return;
        int size = matrix.size();
        int new_matrix[size][size];
        for(int i=0; i<size; i++){
            // 对每一行
            for(int j=0; j<size; j++){
                // 对每一个元素
                int curr = matrix[i][j];
                int target = matrix[j][size-i-1];
                new_matrix[j][size-i-1] = curr;
            }
        }
        for(int i=0; i<size; i++)
            for(int j=0; j<size; j++)
                matrix[i][j] = new_matrix[i][j];
    }
};