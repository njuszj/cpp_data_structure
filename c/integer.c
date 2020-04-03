# include <stdio.h>
# include <stdlib.h>

int main(){
    int x = -1;
    unsigned u = 2147483648;
    printf("size: %d, %d\n", sizeof(int), sizeof(unsigned));
    printf("x = %u = %d\n", x, x);
    printf("u = %u = %d", u, u);
}