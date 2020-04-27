// 螺旋矩阵
// 写的太乱了!!
// 看的题解也许设定四个边界会好一点，少一点边界判断
// 确实有点乱，还好最后通过了~

# include "leetcode.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.size() == 0) return res;
        int rows = matrix.size();
        int cols = matrix[0].size();
        int c_layer = 0, r_layer = 0;
        while(2 * r_layer <= rows  && 2 * c_layer <= cols){
            for(int i = c_layer; i < cols-c_layer-1; i++){
                res.push_back(matrix[r_layer][i]);
            }
            for(int i = r_layer; i < rows-r_layer-1; i++){
                res.push_back(matrix[i][cols-c_layer-1]);
            }
            if(2 * r_layer < rows - 1)
                for(int i = cols-c_layer-1; i > c_layer; i--){
                    res.push_back(matrix[rows-r_layer-1][i]);
                }
            if(2 * c_layer < cols - 1)
                for(int i = rows-r_layer-1; i > r_layer; i--){
                    res.push_back(matrix[i][c_layer]);
                }
            if(2 * r_layer == rows - 1 && 2 * c_layer == cols - 1)
                res.push_back(matrix[r_layer][c_layer]);
            if(2 * r_layer == rows - 1 && 2 * c_layer < cols - 1)
                res.push_back(matrix[r_layer][cols-c_layer-1]);
            if(2 * c_layer == cols - 1 && 2 * r_layer < rows - 1)
                res.push_back(matrix[rows-r_layer-1][c_layer]);
            r_layer ++;
            c_layer ++;
        }
        return res;
    }
};