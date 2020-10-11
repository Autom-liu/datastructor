#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "HashMap.h"

template<typename K, typename V>
void printMap(HashMap<K, V>* hmap) {
    typename HashMap<K, V>::iterator* it = hmap->newIterator();
    int cnt = 0;
    while(it->hasNext()) {
        Entry<K, V> entry = it->next();
        cout<<"key = "<<entry.key<<" value = "<<entry.value<<" cnt = "<<cnt++<<endl;
    }
    delete it;
}

int main()
{
    HashMap<string, int>* hmap = new HashMap<string, int>(new StringHashed());
    for(int i = 0; i < 30; i++) {
        int x = rand() % 100;
        char c[3];
        string ss(c);
        sprintf(c, "t%d", x);
        hmap->put(c, x * 10);
    }
    printMap(hmap);
    delete hmap;
    return 0;
}
