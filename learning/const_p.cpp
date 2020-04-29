# include <iostream>

using namespace std;

class constBase{
private:
    int x;
    int y;
public:
    constBase(): x(9), y(10) {}
    constBase(int a, int b): x(a), y(b) {}
    void print() const{
        cout << x + y << endl;
    }
    void pp() const{
        x = 1;
    }
};

int main(){
    const constBase c;
    c.print();
    c.pp();
}