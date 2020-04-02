// 电话号码的组合

# include <iostream>
# include <vector>
# include <string>
# include <map>

using namespace std;

class Solution {
public:
    Solution(){
        digitMap['2'] = "abc";
        digitMap['3'] = "def";
        digitMap['4'] = "ghi";
        digitMap['5'] = "jkl";
        digitMap['6'] = "mno";
        digitMap['7'] = "pqrs";
        digitMap['8'] = "tuv";
        digitMap['9'] = "wxyz";
    }
    vector<string> letterCombinations(string digits) {
        vector<string> res, tmp, tmp2;
        char num, extend;
        string alpha;
        if(digits.size() == 0) return res;
        alpha = digitMap[digits[0]];
        for(int j=0; j<alpha.size(); j++){
            string p(1, alpha[j]);
            res.push_back(p);
        }
        for(int i=1; i<digits.size(); i++){
            tmp = res;
            res.clear();
            num = digits[i];
            alpha = digitMap[num];
            for(int j=0; j<alpha.size(); j++){
                tmp2 = tmp;
                extend = alpha[j];
                for(int k=0; k<tmp2.size(); k++){
                    tmp2[k] += extend;
                }
                res.insert(res.begin(), tmp2.begin(), tmp2.end());
            }
        }
        return res;
    }
private:
    map<int, string> digitMap;
};

int main(){
    Solution s;
    vector<string> res = s.letterCombinations("34");
    for(auto k : res)
        cout << k << endl;
    
}