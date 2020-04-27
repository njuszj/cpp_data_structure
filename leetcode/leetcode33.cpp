// 搜索旋转排序数组
// 要求时间复杂度log n级别
// 既然要求log n 那想必应该要用到二分查找
// 不会写。。。
// 忽略了关键的一点: 如果nums[0] < nums[mid]， 那么左边肯定是有序的!
// 官解的思路很好...还要多加学习!


/*

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        if (!n) return -1;
        if (n == 1) return nums[0] == target ? 0 : -1;
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            if (nums[0] <= nums[mid]) {
                if (nums[0] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};


作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/sou-suo-xuan-zhuan-pai-xu-shu-zu-by-leetcode-solut/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size(), max_index = 0;
        // 首先找到nums中的最大值所在
        if(size < 2) {
            for(int i = 0; i < size; i++){
                if(nums[i] == target) return i;
            }
            return -1;
        }
        int head = 0, tail = size-1;
        if(nums[0] > nums[1]) max_index = 0;
        else if(nums[size-1] > nums[size-2]) max_index = size-1;
        else{
            int mid = (head + tail) / 2;
            if(nums[mid] < nums[tail])
        }
        }
    }
};