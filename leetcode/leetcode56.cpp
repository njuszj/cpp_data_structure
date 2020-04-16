// 区间去重
# include "leetcode.h"

bool compare(vector<int> a, vector<int> b){
    // 定义一个比较函数，用于排序
    return a[0] < b[0] ? true : false;
}

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());  // 去掉自己定义的compare函数后运行时间加快了100ms
        vector<vector<int>> res;
        if (intervals.size() < 2) return intervals;
        vector<int> curr_vec = intervals[0];
        vector<int> next_vec = intervals[1];
        int index = 0, size = intervals.size();
        while(++index < size){
            next_vec = intervals[index];
            if(next_vec[0] <= curr_vec[1]){
                // 合并区间, 注意还要判断一下区间尾部
                curr_vec[1] = curr_vec[1] >= next_vec[1] ? curr_vec[1] : next_vec[1];
            }  
            else{
                res.push_back(curr_vec);
                curr_vec = next_vec;
            }
        }
        res.push_back(curr_vec);
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> a;
    vector<int> b = {1,3};
    vector<int> c = {2,4};
    vector<int> d = {2,7};
    a.push_back(b);
    a.push_back(c);
    a.push_back(d);
    auto res = s.merge(a);
    printDoubleVector(res);
}