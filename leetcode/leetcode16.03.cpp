// 计算两条线段的交点
// 要求浮点误差不超过10^-6
# include "leetcode.h"

class Solution {
public:
    double min(double x, double y){
        return x < y ? x : y;
    }
    double max(double x, double y){
        return x > y ? x : y;
    }
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        double x1 = start1[0], y1 = start1[1];
        double x2 = end1[0], y2 = end1[1];
        double x3 = start2[0], y3 = start2[1];
        double x4 = end2[0], y4 = end2[1];

        vector<double> res;
        if(x1 == x2 && x3 != x4){
            double k2 = (y3-y4)/(x3-x4);  // 第二条线段的斜率
            double value = k2 * (x1 - x3) + y3;  // 第二条线段计算值
            if(x1 < min(x3, x4) || x1 > max(x3, x4)) return res;
            if(value >= min(y1, y2) && value <= max(y1, y2)){
                res.push_back(x1);
                res.push_back(value);
                return res;
            }
            else return res;
        }
        if(x1 != x2 && x3 == x4){
            double k1 = (y1-y2)/(x1-x2);  // 第一条线段的斜率
            if(x3 < min(x1, x2) || x3 > max(x1, x2)) return res;
            double value = k1 * (x3 - x1) + y1;  // 第一条线段计算值
            if(value >= min(y3, y4) && value <= max(y3, y4)){
                res.push_back(x3);
                res.push_back(value);
                return res;
            }
            else return res;
        }
        if(x1 == x2 && x3 == x4){
            if(x1 != x3) return res;
            if(min(y1, y2) > max(y3, y4) || max(y1,y2) < min(y3, y4)) return res;
            else{
                res.push_back(x1);
                res.push_back(max(min(y1,y2), min(y3,y4)));
                return res;  // 返回端点较小值的最大值
            }
        }
        double k1 = (y1-y2)/(x1-x2);
        double k2 = (y3-y4)/(x3-x4);
        if(k1 == k2){
            // 斜率相同，可能重合，可能不相交
            if(y1-k1*x1 == y3-k2*x3){
                // 截距相同，是重合的
                if(min(y1, y2) > max(y3, y4) || max(y1,y2) < min(y3, y4)) return res;
                else{
                    double x = max(min(x1,x2), min(x3,x4)); // 返回端点较小值的最大值
                    res.push_back(x);
                    res.push_back(k1 * x + y1);
                    return res;  
                }
            }
            else{
                // 不相交
                return res;
            }
        return res;
        }
        double x = (x1 * k1 - x3 * k2 + y3 - y1) / (k1 - k2);
        double value = k1 * (x - x1) + y1;
        if(x>=min(x1, x2) && x<=max(x1, x2) && x>=min(x3, x4) && x<=max(x3, x4)){
            res.push_back(x);
            res.push_back(value);
            return res;
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> start1 = {0,0};
    vector<int> end1 = {1, 1};
    vector<int> start2 = {0, 0};
    vector<int> end2 = {-1, -1};
    vector<double> res = s.intersection(start1, end1, start2, end2);
    printVector(res);
}