/*
小Q在周末的时候和他的小伙伴来到大城市逛街，一条步行街上有很多高楼，共有n座高楼排成一行。
小Q从第一栋一直走到了最后一栋，小Q从来都没有见到这么多的楼，
所以他想知道他在每栋楼的位置处能看到多少栋楼呢？（当前面的楼的高度大于等于后面的楼时，后面的楼将被挡住）  

输入第一行将包含一个数字n，代表楼的栋数，接下来的一行将包含n个数字wi(1<=i<=n)，代表每一栋楼的高度。
1<=n<=100000;
1<=wi<=100000;
输出一行，包含空格分割的n个数字vi，分别代表小Q在第i栋楼时能看到的楼的数量。

[IN]: 
6
5 3 8 3 2 5
[OUT]:
3 3 5 4 4 4
*/


// 看答案知道本题涉及一个数据结构: 单调栈
# include <iostream>
# include <vector>

using namespace std;

int func1(){
    // 该方法测试时超过时间,90%通过
    int N;
    cin >> N;
    vector<int> nums(N), res(N), back(N), ahead(N);
    for(int i=0; i<N; i++)
        cin >> nums[i];
    if(N==0) return 0;
    if(N==1) {cout << "1" << endl; return 0;}
    for(int i=0; i<N; i++){
        if(i == 0) ahead[i] = 1;  // 初始化，用ahead数组表示i位置的楼向前可以看见的数目
        else if(nums[i] == nums[i-1]) ahead[i] = ahead[i-1];  // 不变
        else if(nums[i] < nums[i-1]) ahead[i] = ahead[i-1] + 1;  // 加1
        else{
            // 如果新的i比上一个元素要大，那么就要一直回退直到找到一个比i大的
            int tmp = i;
            while(tmp>=0 && nums[tmp] <= nums[i]) tmp--;
            if(tmp < 0) ahead[i] = 1;
            else ahead[i] = ahead[tmp] + 1;
        }
    }
    for(int i=N-1; i>=0; i--){
        if(i == N-1) back[i] = 1;  // 用同样的方法构造后向数组
        else if(nums[i] == nums[i+1]) back[i] = back[i+1];  // 不变
        else if(nums[i] < nums[i+1]) back[i] = back[i+1] + 1;  // 加1
        else{
            // 如果新的i比下一个元素要大，那么就要一直前进直到找到一个比i大的
            int tmp = i;
            while(tmp<N && nums[tmp] <= nums[i]) tmp++;
            if(tmp >= N) back[i] = 1;
            else back[i] = back[tmp] + 1;
        }
    }
    for(int i=0; i<N; i++){
        if(i == 0) res[i] = 1 + back[1];
        else if(i == N-1) res[i] = 1 + ahead[N-2];
        else res[i] = ahead[i-1] + back[i+1] + 1 ;
    }
    for(int elem : res)
        cout << elem << " ";
}

int func2(){
    // 这个方法也超时了，更暴力所以只通过了50%
    int N, cnt, max;
    cin >> N;
    vector<int> nums(N), res(N), back(N), ahead(N);
    for(int i=0; i<N; i++)
        cin >> nums[i];
    if(N==0) return 0;
    if(N==1) {cout << "1" << endl; return 0;}
    cnt = 1;
    max = INT32_MIN;
    for(int j=N-2; j>=0; j--){
        if(nums[j] > max){
            max = nums[j];
            cnt++;
        }    
    }
    res[N-1] = cnt;
    cnt = 1;
    max = INT32_MIN;
    for(int j=1; j<N; j++){
        if(nums[j] > max){
            max = nums[j];
            cnt++;
        }    
    }
    res[0] = cnt;
    for(int i=1; i<N-1; i++){
        cnt = 1;
        max = INT32_MIN;
        for(int j=i-1; j>=0; j--){
            if(nums[j] > max){
                max = nums[j];
                cnt++;
            }    
        }
        max = INT32_MIN;
        for(int j=i+1; j<N; j++){
            if(nums[j] > max){
                max = nums[j];
                cnt++;
            }
        }
        res[i] = cnt;
    }
    for(int elem : res)
        cout << elem << " ";
}