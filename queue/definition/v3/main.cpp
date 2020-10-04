#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "Queue.h"

int main()
{
    DQueue<string>* qq = new DQueue<string>();
    for(int i = 0; i < 30; i++) {
        int x = rand() % 100;
        char c[3];
        sprintf(c, "t%d", x);
        qq->pushBack(string(c));
        char d[3];
        sprintf(d, "t%d", x);
        qq->pushTop(string(d));
        qq->popBack();
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"top: "<<qq->top()<<endl;
    cout<<"back: "<<qq->back()<<endl;
    cout<<"capacity: "<<qq->getCapacity()<<endl;
    int sz = qq->getSize() - 1;
    for(int i = 0; i < sz; i++) {
        cout<<qq->popTop()<<" ";
    }
    cout<<endl;
    if(!qq->isEmpty()) {
        cout<<"top: "<<qq->top()<<endl;
        cout<<"back: "<<qq->back()<<endl;
        cout<<"size: "<<qq->getSize()<<endl;
    }
    return 0;
}
