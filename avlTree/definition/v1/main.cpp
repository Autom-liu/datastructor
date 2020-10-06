#include <iostream>
#include <cstdlib>

using namespace std;
#include "AvlTree.h"

int main()
{
    AvlTree<int>* avlTree = new AvlTree<int>();
    for(int i = 0; i < 10; i++) {
        int x = rand() % 100;
        cout<<x<<" ";
        avlTree->add(x);
    }
    cout<<endl;
    cout<<"contains 50? "<<avlTree->contains(50)<<endl;

    Array<int>* arr = avlTree->preOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;
    delete arr;

    arr = avlTree->midOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;
    delete arr;

    arr = avlTree->postOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;

    arr = avlTree->levelOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<" size: "<<avlTree->getSize()<<endl;

    arr = avlTree->preOrder();
    for(int i = 4; i < arr->getLength(); i++) {
        avlTree->remove(arr->get(i));
    }
    arr = avlTree->levelOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<" size: "<<avlTree->getSize()<<endl;

    delete arr;

    return 0;
}
