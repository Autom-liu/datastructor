#ifndef KSELECTION_H_INCLUDED
#define KSELECTION_H_INCLUDED

#include "../entity/Comparator.h"

template <typename T>
class Kselection {
private:
    Comparator<T>* c;
    int __partition(T arr[], int l, int r) {
        T v = arr[l];
        int i = l + 1, j = r-1;
        while(i != j) {
            while(i < j && c->isGreaterOrEqual(arr[j], v)) {
                j--;
            }
            while(i < j && c->isLessOrEqual(arr[i], v)) {
                i++;
            }
            if(i < j) {
                swap(arr[i], arr[j]);
            }
        }
        arr[l] = arr[i];
        arr[i] = v;
        return i;

    }
public:
    Kselection(Comparator<T>* c) {
        this->c = c;
    }
    T doSelect(T arr[], int l, int r, int k) {
        if(l >= r-1) {
            return arr[r-1];
        }
        int p = __partition(arr, l, r);
        if(p == k) {
            return arr[p];
        } else if(k < p) {
            return doSelect(arr, l, p, k);
        } else {
            return doSelect(arr, p+1, r, k);
        }

    }
    T doSearch(T arr[], int n, int k) {
        return doSelect(arr, 0, n, k-1);
    }
};

#endif // KSELECTION_H_INCLUDED
