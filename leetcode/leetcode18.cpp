// 四数之和
// 最后一个出问题的测试
// [-1,0,-5,-2,-2,-4,0,1,-2] -9
// [[-5,-4,-1,1],[-5,-4,0,0],[-5,-2,-2,0],[-4,-2,-2,-1]]

# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res, tmp;
        if(nums.size() < 4) return res;   // 边界条件
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size()-3; i++){
            if( i>0 && (nums[i]==nums[i-1])) continue;
            for(int j=i+1; j<nums.size()-2;j++){
                if(j>i+1 && nums[j]==nums[j-1]) continue;
                int head = j+1, tail = nums.size()-1;
                while(1){
                    if(nums[head]+nums[tail]+nums[i]+nums[j]==target){
                        // cout << "找到了" << endl;
                        vector<int> res_pair = {nums[i], nums[j], nums[head], nums[tail]};
                        res.push_back(res_pair);
                        tail--;
                        while((tail > 0) && (nums[tail-1] == nums[tail])) tail--;
                        head++;
                        while((head<nums.size()-1) && (nums[head+1] == nums[head])) head++;
                    }
                    else if(nums[head]+nums[tail]+nums[i]+nums[j] > target){
                        tail--;
                    }
                    else{
                        head++;
                    }
                    if(head >= tail) break;
                    // cout << "i: " << i << " j: " << j << " head: " 
                    //    << head << " tail:" << tail << endl; 
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> a = {1,23,3,4,5,5,6,7,78,8,9,9};
    vector<vector<int>> b = s.fourSum(a, 31);
    for(vector<int> c : b){
        for(int d : c)
            cout << d << " ";
        cout << endl;
    }
}