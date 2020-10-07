#include <iostream>
#include <cstdlib>
using namespace std;

#include "RBTree.h"

int main()
{
    RBTree<int>* bst = new RBTree<int>();
    for(int i = 0; i < 100; i++) {
        int x = rand() % 100;
        bst->add(x);
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"contains 50? "<<bst->contains(50)<<endl;

    Array<int>* arr = bst->preOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;
    delete arr;

    arr = bst->midOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;
    delete arr;

    arr = bst->postOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;

    arr = bst->levelOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<" size: "<<bst->getSize()<<endl;

    delete arr;

    arr = bst->preOrder();
    for(int i = 10; i < arr->getLength(); i++) {
        bst->remove(arr->get(i));
    }
    arr = bst->levelOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<" size: "<<bst->getSize()<<endl;

    delete arr;
    delete bst;

    return 0;
}
