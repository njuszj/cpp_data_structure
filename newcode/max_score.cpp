# include <iostream>
# include <map>
# include <vector>
# include <set>

using namespace std;

int main(){
    int N, M, flag, even;
    long long res=0;
    cin >> N >> M;
    vector<int> vScore(N), vFlag(N), vIndex;
    map<int, vector<int>> mFlagIndex;
    set<int> sFlag;
    for(int i=0; i<N; i++)
        cin >> vScore[i];
    for(int i=0; i<N; i++){
        cin >> flag;
        vFlag[i] = flag;
        sFlag.insert(flag);
        mFlagIndex[flag].push_back(i);
    }
    
    set<int>::iterator itor = sFlag.begin();
    while(itor != sFlag.end()){
        flag = *itor;
        vIndex = mFlagIndex[flag];
        if(vIndex.size() < 2){
            itor++;
            continue;
        }
        for(int i=0; i<vIndex.size(); i++){
            int even = vIndex[i] % 2;
            for(int j=i+1; j<vIndex.size(); j++){
                if(vIndex[j]%2 == even)
                    res += (static_cast<long long>(vIndex[i]) + 
                            static_cast<long long>(vIndex[j]) + 
                            static_cast<long long>(2)) * (
                    static_cast<long long>(vScore[vIndex[i]]) + static_cast<long long>(vScore[vIndex[j]]));
            }
        }
        itor++;
    }
    cout << res % 10007;
    return 0;    
}