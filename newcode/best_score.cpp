#include <iostream>
#include <vector>

using namespace std;

int max(unsigned int a,unsigned int b,unsigned int c ,unsigned int d, unsigned e){
    int max = 0;
    max = max >= a ? max : a;
    max = max >= b ? max : b;
    max = max >= c ? max : c;
    max = max >= d ? max : d;
    max = max >= e ? max : e;
    return max;
}

int main(){
    unsigned int n, m, sc_in;
    char ch;
    string s_in;
    long long res = 0;
    cin >> n >> m;
    vector<string> answer(n);
    for(int i=0;i<n;i++){
        cin >> s_in;
        answer[i] = s_in;
    }
    vector<int> score(m);
    for(int i=0;i<m;i++) {
        cin >> sc_in;
        score[i] = sc_in;
    }
    
    for(int i=0;i<m;i++){
        unsigned int a=0,b=0,c=0,d=0,e=0;
        for(int j=0;j<n;j++){
            ch = answer[j][i];
            if(ch=='A') a += 1;
            else if(ch=='B') b += 1;
            else if(ch=='C') c += 1;
            else if(ch=='D') d += 1;
            else if(ch=='E') e += 1;
        }
        int r = max(a,b,c,d,e);
        res += r * score[i];
    }
    cout << res;
    return 0;
}