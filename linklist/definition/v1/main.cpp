#include <iostream>
#include <cstdlib>

using namespace std;
#include "SimpleLinkList.h"

void printLinkList(AbstractLinkList<int>* linklist) {
    AbstractLinkList<int>::iterator* it = linklist->newIterator();
    while(it->hasNext()) {
        cout<<it->next()<<" ";
    }
    cout<<endl;
    delete it;
}

int main()
{
    AbstractLinkList<int>* linklist = new SimpleLinkList<int>();


    for(int i = 0; i < 10; i++) {
        int x = rand() % 100;
        linklist->addFirst(x);
        linklist->addLast(x);
    }

    linklist->add(10, 100);
    printLinkList(linklist);

    for(int i = 0; i < 5; i++) {
        linklist->removeFirst();
        linklist->removeLast();
    }

    cout<<linklist->get(5)<<endl;
    linklist->remove(5);
    printLinkList(linklist);
    cout<<"size : "<<linklist->getSize()<<endl;
    delete linklist;
    return 0;
}
