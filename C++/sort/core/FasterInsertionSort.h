#ifndef FASTERINSERTIONSORT_H_INCLUDED
#define FASTERINSERTIONSORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

/**
* 针对插入排序的优化
* 此优化可以减少大量的交换操作
**/
template <typename T>
class FasterInsertionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    /**
    * 获取arr[i] 在[0, i)范围内适合的位置
    **/
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

#endif // FASTERINSERTIONSORT_H_INCLUDED
