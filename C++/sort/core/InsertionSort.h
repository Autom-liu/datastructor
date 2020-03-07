#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"
#include "../entity/Comparator.h"

template<typename T>
class InsertionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
public:
    InsertionSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = 1; i < n; i++) {
            for(int j = i; j > 0 && c->isLessThan(a[j], a[j-1]); j--) {
                swap(a[j], a[j-1]);
            }
        }
    }
    string getSortName() {
        return "Insertion Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~InsertionSort() {
    }
};


template <typename T>
class FasterInsertionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    void insertProperIndex(T arr[], int i) {
        T e = arr[i];
        int j = i;
        for(j = i; j > 0 && c->isLessThan(e, arr[j-1]); j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
public:
    FasterInsertionSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = 1; i < n; i++) {
            insertProperIndex(a, i);
        }
    }
    string getSortName() {
        return "Faster Insertion Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterInsertionSort() {

    }
};



#endif // INSERTIONSORT_H_INCLUDED
