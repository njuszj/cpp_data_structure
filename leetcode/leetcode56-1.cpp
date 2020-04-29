// 数组中出现一次的两个数字
// 本来打算是用异或
// 现在使用map实现

// 官方解法巧妙的使用异或

/*

如果我们可以把所有数字分成两组，使得：

1.    两个只出现一次的数字在不同的组中；

2.    相同的数字会被分到相同的组中。

那么对两个组分别进行异或操作，即可得到答案的两个数字。这是解决这个问题的关键。

那么如何实现这样的分组呢？

记这两个只出现了一次的数字为 aaa 和 bbb，那么所有数字抑或的结果就等于 
aaa 和 bbb 抑或的结果，我们记为 xxx。如果我们把 xxx 写成二进制的形式 xkxk−1⋯x2x1x0x_k x_{k - 1} \cdots x_2 x_1 x_0xk​xk−1​⋯x2​x1​x0​，其中 xi∈{0,1}x_i \in \{ 0, 1 \}xi​∈{0,1}，我们考虑一下 xi=0x_i = 0xi​=0 和 xi=1x_i = 1xi​=1 的含义是什么？它意味着如果我们把 aaa 和 bbb 写成二进制的形式，aia_iai​ 和 bib_ibi​ 的关系——xi=1x_i = 1xi​=1 表示 aia_iai​ 和 bib_ibi​ 不等，xi=0x_i = 0xi​=0 表示 aia_iai​ 和 bib_ibi​ 相等。假如我们任选一个不为 000 的 xix_ixi​，
按照第 iii 位给原来的序列分组，如果该位为 000 就分到第一组，否则就分到第二组，
这样就能满足以上两个条件

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/solution/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        map<int, int> mCount;
        vector<int> res;
        int val = 0, tmp = 0;
        for(int i=0; i<nums.size(); i++){
            mCount[nums[i]] = 0;
        }
        for(int i=0; i<nums.size(); i++){
            mCount[nums[i]] ++;
        }
        map<int, int>::iterator iter = mCount.begin();
        for(;iter != mCount.end(); iter++){
            if(iter->second == 1) res.push_back(iter->first);
        } 
        return res;
    }
};