#include "genSkipList.h"

template<class T>
SkipList<T>::SkipList(){
    for(int i=0;i<maxLevel;i++) root[i] = 0;    
}

template<class T>
bool SkipList<T>::isEmpty() const{
    return root[0] == 0;
}

template<class T>
void SkipList<T>::choosePowers(){
    powers[maxLevel-1] = (2 << (maxLevel - 1)) - 1;
    for(int i = maxLevel-2, j=0; i>=0 ;i--, j++)
        powers[i] = powers[i+1] - (2<<j);
}

template<class T>
int SkipList<T>::chooseLevel(){
    int i, r = rand() % powers[maxLevel-1] + 1;
    for(int i=1;i<maxLevel;i++)
        if(r<powers[i])
            return i - 1;
    return i-1; 
}

