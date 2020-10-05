#include <iostream>

#include "Array.h"

using namespace std;

void printArr(Array<int>* arr) {
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
        if(i % 10 == 0) {
            cout<<endl;
        }
    }
}

void printInterator(Array<int>* arr) {

    Array<int>::iterator* it = arr->newIterator();
    int i = 0;
    while(it->hasNext()) {
        cout<<it->next()<<" ";
        i++;
        if(i % 10 == 0) {
            cout<<endl;
        }
    }
    delete it;

}

int main()
{
    Array<int>* arr = new Array<int>();
    for(int i = 0; i < 100; i++) {
        arr->add(i);
        arr->prepend(i*10);
    }

    arr->insert(10, -1);
    printArr(arr);

    for(int i = 0; i < 80; i++) {
        arr->removeFirst();
        arr->removeLast();
    }
    arr->remove(10);
    printInterator(arr);
    return 0;
}
