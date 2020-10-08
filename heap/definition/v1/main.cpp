#include <iostream>
#include <cstdlib>

using namespace std;

#include "MinHeap.h"

class IntCompare : public Comparetor<int> {

    virtual int compare(int v1, int v2) {
        return v1 - v2;
    }
};

void printHeap(MinHeap<int>* heap) {
    Array<int>::iterator* it = heap->newIterator();
    while(it->hasNext()) {
        cout<<it->next()<<" ";
    }
    cout<<endl;
    delete it;
}

int main()
{
    const int length = 16;
    int* arr = new int[length];
    for(int i = 0; i < length; i++) {
        int x = rand() % 100;
        arr[i] = x;
        cout<<x<<" ";
    }
    MinHeap<int>* heap = new MinHeap<int>(new IntCompare(), arr, length);
    cout<<endl;
    printHeap(heap);
    cout<<"size: "<<heap->size()<<endl;
    for(int i = 0; i < length; i++) {
        int x = rand() % 100;
        cout<<heap->replace(x)<<" ";
    }
    cout<<endl;
    while(!heap->isEmpty()) {
        cout<<heap->pop()<<" ";
    }
    cout<<endl;
    delete heap;
    return 0;
}
