# include <iostream>
# include <vector>

using namespace std;

int find_first_of(vector<int>& nums, int target){
    // 使用二分查找在最多log(n)的时间复杂度下找到第一个符合条件的下标
    int cnt = 1;
    if(nums.size()==0) return -1;
    int head=0, tail=nums.size()-1;
    int mid = (head + tail) / 2;
    while(tail > head){
        cout << "第" << cnt << "次查询, " << "head=" << head 
        << " mid=" << mid << " tail=" << tail << endl;
        if(nums[mid] > target)
            tail = mid - 1;
        else
        {
            head = mid + 1;
        }
        mid = (head + tail) / 2;
        ++cnt;
    }
    cout << "循环结束,第" << cnt << "次查询, " << "head=" << head 
        << " mid=" << mid << " tail=" << tail << endl;
}

int main(){
    vector<int> nums = {1,2,3,4,5,6,6,6,6,6,6,6,6,7,8,9,10};
    find_first_of(nums, 6);
}