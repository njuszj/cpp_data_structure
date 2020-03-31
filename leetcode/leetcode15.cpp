// 15.三数之和　a+b+c=0
// 原方法总是超时!!!
// 看了题解尝试使用双指针法

# include <iostream>
# include <vector>
# include <map>
# include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums){
        vector<vector<int>> res;
        if(nums.size() < 3) return res;
        int start=0, tail=nums.size()-1, mid=start+1, elemMid, elemTail;
        sort(nums.begin(), nums.end());  // 排序
        for(;start<nums.size()-2;start++){
            if(start>0 && nums[start]==nums[start-1]) continue;
            mid = start + 1;
            tail = nums.size() - 1;
            while(1) {
                elemMid = nums[mid];
                elemTail = nums[tail];
                if(nums[start]+nums[mid]+nums[tail] == 0){
                    vector<int> res_pair = {nums[start],elemMid,elemTail};
                    res.push_back(res_pair);
                    for(;mid<tail && nums[++mid]==elemMid;);
                    for(;mid<tail && nums[--tail]==elemTail;);
                }
                else if(nums[start]+nums[mid]+nums[tail] > 0){
                    for(;mid<tail && nums[--tail]==elemTail;);
                }
                else
                {
                    for(;mid<tail && nums[++mid]==elemMid;);
                }
                if(mid>=tail) break;
            }
        }
    return res;
    }

    vector<vector<int>> threeSumHash(vector<int>& nums) {
        // 原来采用的哈希表做法， 超时了
        int len = nums.size();
        int num, cnt, previ, prevj;
        sort(nums.begin(), nums.end());  // 排序为去重做准备
        vector<vector<int>> res;
        multimap<int, int> mNums;
        multimap<int, int>::iterator index;
        for(int i=0; i<len; i++){
            pair<int, int> p(-1*nums[i], i);
            mNums.insert(p);
        }
        for(int i=0; i<len; i++){
            // 这样做下来顺序应该是 index, j, i
            if(nums[i] < 0) continue;
            if(i+1<len && nums[i]==nums[i+1]) continue; // 重复控制
            for(int j=0; j<i; j++){
                if(j+1<i && nums[j]==nums[j+1]) continue; // 重复控制
                num = nums[i] + nums[j];
                if((index = mNums.find(num)) != mNums.end()){
                    vector<int> res_pair = {nums[j],nums[i],nums[(*index).second]};
                    if((*index).second < j)
                        res.push_back(res_pair);
                    }
                }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> nums = {0,0,0};
    vector<vector<int>> res = s.threeSum(nums);
    for(auto k:res)
        for(auto m:k)
            cout << m << " ";   
}

