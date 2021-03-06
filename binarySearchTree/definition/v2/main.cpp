#include <iostream>
#include <cstdlib>
using namespace std;

#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int>* bst = new BinarySearchTree<int>();
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

    arr = bst->preOrder();
    for(int i = 4; i < arr->getLength(); i++) {
        bst->remove(arr->get(i));
    }
    arr = bst->preOrder();
    for(int i = 0; i < arr->getLength(); i++) {
        cout<<arr->get(i)<<" ";
    }
    cout<<endl;
    cout<<"size: "<<bst->getSize()<<endl;


    delete arr;
    delete bst;

    return 0;
}
