// 单词搜索
// 给定一个二维网格和一个单词，找出该单词是否存在于网格中
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
// 暂时还没有通过，不过已经很接近了...
// 思路似乎没问题，可是总是少了点什么...
# include "leetcode.h"


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.length() == 0) return true;
        int rows = board.size();
        if(rows == 0) return false;
        int cols = board[0].size();
        vector<vector<int>> path;  // 储存路径
        for(int i=0; i<word.size(); i++){
            char c = word[i];
            for(int j=0; j<rows; j++){
                for(int k=0; k<cols; k++){
                    if(board[j][k] == c){
                        if(i == 0){
                            // 初始化
                            vector<int> sub_path;
                            sub_path.push_back(j*cols + k + 1);
                            path.push_back(sub_path);
                        }
                        else{
                            // 对每一条路径检验是否可以添加
                            for(int m=0; m<path.size(); m++){
                                vector<int> tmp = path[m];
                                if(tmp.size() < i) continue;
                                int curr_loc = j*cols + k + 1;
                                int last_loc = tmp[tmp.size()-1];
                                if(abs(last_loc - curr_loc) == cols || (abs(curr_loc - last_loc)==1 && ((curr_loc+1)/cols == (last_loc+1)/cols))){
                                    // 如果与最后一个节点相邻
                                    cout << "比较" << curr_loc << "curr<-->last" << last_loc << endl;
                                    if(find(tmp.begin(), tmp.end(), curr_loc) == tmp.end()){
                                        // 不能重复使用节点
                                        for(int kk = 0; kk<tmp.size(); kk++)
                                            cout << tmp[kk] << " ";
                                        cout << endl;
                                        cout << " 成功加入" << endl;
                                        tmp.push_back(curr_loc);
                                        path.push_back(tmp);
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int n=0; n<path.size(); n++){
            // 如果有一条路径与word等长
            cout << "长度: " << path[n].size() << endl;
            if(path[n].size() == word.size()) return true;
        }
        return false;
    }
};