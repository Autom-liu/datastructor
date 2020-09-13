#ifndef BINARYSEARCH_H_INCLUDED
#define BINARYSEARCH_H_INCLUDED

#include "../entity/Comparator.h"

namespace BinarySearch {

template<typename T>
int doSearch(T arr[], int l, int r, T target, Comparator<T>* c);

template<typename T>
int doSearch(T arr[], int n, T target, Comparator<T>* c) {
    return doSearch(arr, 0, n, target, c);
}

/// [l, r)
template<typename T>
int doSearch(T arr[], int l, int r, T target, Comparator<T>* c) {
    while (l < r) {

        int mid = (r + l) / 2;
        if(c->equals(arr[mid], target)) {
            return mid;
        } else if(c->isLessThan(target, arr[mid])) {
            r = mid;
        } else if(c->isGreaterThan(target, arr[mid])) {
            l = mid + 1;
        }
    }
    return -1;
}
}


#endif // BINARYSEARCH_H_INCLUDED
