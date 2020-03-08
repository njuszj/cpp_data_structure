#include<iostream>
using namespace std;

struct A{
    char a;
    int b;
    char* c;
};

int main(){
    const char *p = "ashdihu";
    int a = 8;
    const int* int_p = &a;
    cout << sizeof(int_p) << endl;
    cout << int_p << endl;
    cout << sizeof(A) << endl;
}