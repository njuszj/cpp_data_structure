# include "leetcode.h"

// 使用C++提供的set方法,set的背后是平衡二叉树
// 难点: 访问时间,直接用时钟时间
// 自建Node结构, 定义比较方法

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        map<int, int>::iterator itor;
        itor = mValue.find(key);
        if(itor != mValue.end()) {
            mScore[itor->first]++;
            return itor->first;
        }
        else return -1;
    }
    
    void put(int key, int value) {
        if(mValue.size() < capacity){
            if(get(key) == -1){
                mValue[key] = value;
                mScore[key] = 1;
            }
            else mValue[key] = value;     // 更新值,注意权值已经在get中更新过了
        }
        else{

        }
    }
private:
    int capacity;
    map<int, int> mValue;  // 储存值
    map<int, int>  mScore;  // 储存权重,用于容量不够时删除
};


int main(){
    
}