// 螺旋矩阵II
// 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
/*
// 答案区的简洁做法
class Solution {
    public int[][] generateMatrix(int n) {
        int l = 0, r = n - 1, t = 0, b = n - 1;
        int[][] mat = new int[n][n];
        int num = 1, tar = n * n;
        while(num <= tar){
            for(int i = l; i <= r; i++) mat[t][i] = num++; // left to right.
            t++;
            for(int i = t; i <= b; i++) mat[i][r] = num++; // top to bottom.
            r--;
            for(int i = r; i >= l; i--) mat[b][i] = num++; // right to left.
            b--;
            for(int i = b; i >= t; i--) mat[i][l] = num++; // bottom to top.
            l++;
        }
        return mat;
    }
}


作者：jyd
链接：https://leetcode-cn.com/problems/spiral-matrix-ii/solution/spiral-matrix-ii-mo-ni-fa-she-ding-bian-jie-qing-x/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int cnt=1;
        int i, j, k;
        vector<int> R(n, 0);
        vector<vector<int>> matrix(n, R);
        if(n % 2 == 1) matrix[(n-1)/2][(n-1)/2] = n * n;
        for(int i=0; i<=(n-1)/2; i++){
            cout << "i :" << i << endl;
            for(j=i; i+j<n-1; j++){
                matrix[i][j] = cnt++;
            }
            for(k=i; i+k<n-1; k++){
                matrix[k][n-i-1] = cnt++;
            }
            for(;j>i; j--){
                matrix[n-i-1][j] = cnt++;
            }
            for(;k>i; k--){
                matrix[k][i] = cnt++;
            }
        }
        return matrix;
    }
};

int main(){
    Solution s;
    vector<vector<int>> r = s.generateMatrix(5);
    printDoubleVector(r);
}

