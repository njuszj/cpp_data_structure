// 插入区间
// 竟然通过了! 要考虑的情形实在有点多! 只能跟着提交结果反馈进行修改
// 可以试试贪心算法:
/*
在区间 newInterval 之前开始的区间全部添加到输出中。
将 newInterval 添加到输出中，如果与输出中的最后一个区间重合则合并它们
然后一个个添加后续的区间，如果重合则合并它们

JAVA

class Solution {
  public int[][] insert(int[][] intervals, int[] newInterval) {
    // init data
    int newStart = newInterval[0], newEnd = newInterval[1];
    int idx = 0, n = intervals.length;
    LinkedList<int[]> output = new LinkedList<int[]>();

    // add all intervals starting before newInterval
    while (idx < n && newStart > intervals[idx][0])
      output.add(intervals[idx++]);

    // add newInterval
    int[] interval = new int[2];
    // if there is no overlap, just add the interval
    if (output.isEmpty() || output.getLast()[1] < newStart)
      output.add(newInterval);
    // if there is an overlap, merge with the last interval
    else {
      interval = output.removeLast();
      interval[1] = Math.max(interval[1], newEnd);
      output.add(interval);
    }

    
    // add next intervals, merge with newInterval if needed
    while (idx < n) {
      interval = intervals[idx++];
      int start = interval[0], end = interval[1];
      // if there is no overlap, just add an interval
      if (output.getLast()[1] < start) output.add(interval);
      // if there is an overlap, merge with the last interval
      else {
        interval = output.removeLast();
        interval[1] = Math.max(interval[1], end);
        output.add(interval);
      }
    }
    return output.toArray(new int[output.size()][2]);
  }
}


作者：LeetCode
链接：https://leetcode-cn.com/problems/insert-interval/solution/cha-ru-qu-jian-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        vector<int> tmp;
        int new_start = newInterval[0];
        int new_end = newInterval[1];
        int i = 0, size=intervals.size();
        if(size == 0) {
            res.push_back(newInterval);
            return res; 
        }
        while(i < size){
            int start = intervals[i][0];
            int end = intervals[i][1];
            if(end < new_start){
                res.push_back(intervals[i]);
                if(i == size - 1 || intervals[i+1][0] > new_end){
                    res.push_back(newInterval);
                }
                i++;
            }
            else if(start > new_end){
                if(i == 0){
                    res.push_back(newInterval);
                }
                res.push_back(intervals[i]);
                i++;
            }
            else{
                int val = new_start > start ? start : new_start;
                tmp.push_back(val);
                while(i < size && intervals[i][0] <= new_end){
                    i++;
                }
                val = new_end > intervals[i-1][1] ? new_end : intervals[i-1][1];
                tmp.push_back(val);
                res.push_back(tmp);
            }
        }
        return res;
    }
};


int main(){
    vector<int> a = {1,5};
    vector<int> b = {3,5};
    vector<int> c = {6,7};
    vector<int> d = {8,10};
    vector<int> e = {12,16};
    vector<int> i = {0, 3};
    vector<vector<int>> vs = {a};
    Solution s;
    vector<vector<int>> r = s.insert(vs, i);
    printDoubleVector(r);
}