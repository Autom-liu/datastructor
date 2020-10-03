#include <iostream>

using namespace std;

#include "Stack.h"

int main()
{
    Stack<string>* st = new Stack<string>();

    st->push("ss");
    st->push("tt");

    cout<<st->pop()<<endl;
    if(!st->isEmpty()) {
        cout<<st->top()<<endl;
    }
    cout<<"getSize: "<<st->size()<<endl;
    delete st;
    return 0;
}
