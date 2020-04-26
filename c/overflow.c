# include <stdio.h>
# include <stdlib.h>

int sum(int a[], unsigned len){
    int i, sum = 0;
    for(i=0; i<len-1; i++){
        sum += a[i];
    }
    return sum;
}

int main(){
    printf("错误是因为无符号数错误\n");
    int a[5] = {1,2,3,4,5};
    printf("%u", a);
}