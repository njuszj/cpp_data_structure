// 下雨问题
# include <iostream>
# include <vector>

using namespace std;

int main(){
    vector<int> nums;
    int elem, max, min, sum=0, res=0;
    while(cin>>elem){
        nums.push_back(elem);
    }
    if(nums.size() < 3) return 0;
    for(int i=0; i<nums.size()-1; i++){
        // 假设i的位置为合理的水位开始
        if(nums[i] <= nums[i+1]) continue;
        int j = i+1;
        max = i+1;   // 记录最大值位置
        while(j<nums.size() && nums[j] <= nums[i]){
            if(nums[j] >= nums[max])
                max = j;
            j++;
        }  // 一直找到比i位置大的j
        if(nums[j] >= nums[max]) max = j;
        sum = 0;
        min = nums[i] < nums[max] ? nums[i] : nums[max];
        // cout << "max: " << max << " i:" << i << " min" << min << endl;
        for(int k=i+1; k<max; k++)
            sum += min - nums[k];
        res += sum;
        i = max; // 移位
        i--;
    }
    cout << res << endl;
}