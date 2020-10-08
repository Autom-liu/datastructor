#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "TreeSet.h"
#include "RBTreeMap.h"

int main()
{
    RBTreeMap<string, int>* treeMap1 = new RBTreeMap<string, int>();
    TreeMap<string, int>* treeMap = new TreeMap<string, int>();
    for(int i = 0; i < 30; i++) {
        int x = rand() % 100;
        char c[3];
        sprintf(c, "t%d", x);
        treeMap->put(c, x);
    }
    if(treeMap->contains("t62")) {
        cout<<treeMap->get("t62")<<endl;
    }

    for(int i = 0; i < 30; i++) {
        int x = rand() % 100;
        char c[3];
        sprintf(c, "t%d", x);
        treeMap1->put(c, x);
    }

    if(treeMap->contains("t78")) {
        cout<<treeMap->get("t78")<<endl;
    }

    delete treeMap;
    delete treeMap1;

    TreeSet<int>* treeSet = new TreeSet<int>();
    for(int i = 0; i < 30; i++) {
        int x = rand() % 100;
        treeSet->add(x);
    }

    delete treeSet;

    return 0;
}
