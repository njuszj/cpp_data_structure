// 字母异位词分组
// 排序后做哈希索引，一遍成功
// 但是时间复杂度有待优化

# include "leetcode.h"

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> res;
        vector<string> empty_v;
        vector<vector<string>> ret;
        for(int i=0; i<strs.size(); i++){
            string s = strs[i];
            string s_sort = s;
            sort(s_sort.begin(), s_sort.end());
            if(res.find(s_sort) == res.end()) res[s_sort] = empty_v;
            res[s_sort].push_back(s);
        }
        map<string, vector<string>>::iterator iter = res.begin();
        for(; iter!=res.end(); iter++) ret.push_back(iter->second);
        return ret;
    }
};

int main(){
    vector<string> strs;
    strs.push_back("kjsfda");
    Solution s;
    s.groupAnagrams(strs);
}