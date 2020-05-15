// 最小栈
// 每次pop若删除了最小元素，则重新寻找

// 官方解法

/*

class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;      // 了解:  min_stack 中储存的是前k个元素中最小的元
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x)); // 这一步感觉有点意思
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/min-stack/solution/zui-xiao-zhan-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/

# include "leetcode.h"

const int MAX_SIZE = 100;
class MinStack {
public:
    MinStack() {
        array = new int[MAX_SIZE];
        thetop = 0;
        themin = INT32_MAX;
    }
    
    ~MinStack(){
        delete[] array;
    }

    void push(int x) {
        if(thetop < MAX_SIZE){
            array[thetop] = x;
            thetop++;
            if(x < themin) themin = x;
        }
    }
    
    void pop() {
        if(thetop > 0) {
            int thedel = array[thetop-1];
            thetop--;
            if(thedel == themin){
                // 删掉了最小元素后进行重新选取
                themin = INT32_MAX;
                for(int i=0; i<thetop; i++){
                    if(array[i] < themin) themin = array[i];
                }
            }
        }
    }
    
    int top() {
        if(thetop > 0)
            return array[thetop-1];
        else return 0;
    }
    
    int getMin() {
        return themin;
    }
private:
    int* array;class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }
    
    void pop() {
        x_stack.pop();
        min_stack.pop();
    }
    
    int top() {
        return x_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};