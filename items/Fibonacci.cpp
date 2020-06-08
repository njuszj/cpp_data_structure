#include<math.h>
#include<iostream>
#include<ctime>

/*
为了说明递归算法的浪费
*/


// 递归版本
unsigned int Fib(unsigned int n){
    if(n<2) return n;
    else return Fib(n-2) + Fib(n-1);
}

// 不使用递归的优化版本
unsigned int iterativeFib(unsigned int n){
    if(n<2) return n;
    else{
        register int i = 2, tmp, current = 1, last = 0;
        for(;i<=n;++i){
            tmp = current;
            current += last;
            last = tmp;
        }
    return current;
    }
}

//公式法
unsigned int deMoivreFib(unsigned int n){
    return ceil(exp(n*log(1.6180339897)) - log(2.2360679775) - 0.5);
}

int main(){
    unsigned int n;
    unsigned long res;
    clock_t startTime, endTime;
    std::cout << "输入变量n " << std::endl;
    std::cin >> n;

    startTime = clock();
    res = Fib(n);
    endTime = clock();
    std::cout << "递归算法耗时: " << double(endTime-startTime)/CLOCKS_PER_SEC << " 结果: " << res << std::endl;

    startTime = clock();
    res = iterativeFib(n);
    endTime = clock();
    std::cout << "非递归算法耗时: " << double(endTime-startTime)/CLOCKS_PER_SEC << " 结果: " << res << std::endl;

    startTime = clock();
    res = deMoivreFib(n);
    endTime = clock();
    std::cout << "公式算法耗时: " << double(endTime-startTime)/CLOCKS_PER_SEC << " 结果: " << res << std::endl;

}
