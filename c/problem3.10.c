# include <stdio.h>

void main(){
    unsigned int a = 1;
    unsigned short b = 1;
    char c = -1;
    int d;
    d = a > c ? 1 : 0;
    printf("%d\n", d);
    d = b > c ? 1 : 0;  // short和char比较两者都提升到int
    printf("%d\n", d);
}