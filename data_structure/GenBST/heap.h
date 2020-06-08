/*

template<class T>
void moveDown(T data[], int first, int last){
    // 下降算法，用以解决堆的删除问题
    int lagrgest = 2*first + 1;
    while(largest <= last){
        if(largest < last && data[largest] < data[largest + 1])
        // 根节点的两个子节点存在，且为2n+1和2n+2
            largest++;
        if(data[first] < data[largest]){ // 如果必要，进行节点交换，即节点下降
            swap(data[first], data[largest]);
            first = largest;
            largest = 2*first + 1;
        }
        else largest = last + 1;
    }
}

*/