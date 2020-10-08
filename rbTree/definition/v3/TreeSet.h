#ifndef TREESET_H_INCLUDED
#define TREESET_H_INCLUDED

#include "TreeMap.h"

template <typename K>
class TreeSet {
private:
    TreeMap<K, int>* treeMap;
public:
    TreeSet() {
        treeMap = new TreeMap<K, int>();
    }

    int getSize() {
        return treeMap->getSize();
    }

    bool isEmpty() {
        return treeMap->isEmpty();
    }

    bool contains(K key) {
        return treeMap->contains(key);
    }

    void add(K key){
        treeMap->put(key, 0);
    }

    void remove(K key) {
        treeMap->remove(key);
    }

    ~TreeSet() {
        delete treeMap;
    }
};


#endif // TREESET_H_INCLUDED
