// 搜索二维矩阵
// 算是二分法的变形
// 位置与行数列数一一对应

# include "leetcode.h"

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        if(rows == 0) return 0;
        int cols = matrix[0].size();
        int size = rows * cols;
        int left=1, right=size, mid;
        int x, y;
        while(left <= right){
            mid = (left + right) / 2;
            x = mid / cols;
            y = (mid % cols - 1 + cols) % cols;
            if(y == cols - 1) x--;
            cout << "访问: " << x << "  " << y << endl;
            if(matrix[x][y] == target) return true;
            else if(matrix[x][y] > target)
                right = mid - 1;
            else left = mid + 1;
        }
        return false;
    }
};