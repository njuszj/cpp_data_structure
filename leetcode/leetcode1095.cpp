// 山脉数组查找
// 可以先找峰值!

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int target, size;
    MountainArray &m;
    int halfSearch(int start, int end){
        int mid = (start + end) / 2;
        while(start < end){
            int val = m.get(mid);
            if (val == target) return mid;
            else if(val < target)
                start = mid + 1;
            else if(val > target)
                end = mid - 1;
        }
        return -1;
    }

    int findInMountainArray(int target, MountainArray &mountainArr){
        size = mountainArr.length();
        m = mountainArr;
        if(m.get(0) == target) return 0;
        int start = 1, end = size-1;
        int val;
        val = func(start, end);
        return val;
    }

    int func(int start, int end) {
        int mid = (start + end) / 2;
        int val1, val2, res;
        val1 = m.get(mid);
        val2 = m.get(mid-1);
        if(val1 == target) return mid;
        else{
            if(start == end) return -1;
        }
        if(val1 > val2){
            if(val1 > target){
                res = halfSearch(start, mid-1);
                if(res != -1) return res;
                else res = func(mid+1, end);
            }
            else{
                res = func(mid+1, end);
            }
        }
        else if(val1 < val2){
            if(val1 > target){
                res = halfSearch(mid+1, end);
                if(res != -1) return res;
                else res = func(start, mid-1);
            }
            else{
                res = func(start, mid-1);
            }
        }
    }
};