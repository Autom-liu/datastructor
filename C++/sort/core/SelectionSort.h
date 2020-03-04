#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"

template <typename T>
class SelectionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;

    /**
    * 找到数组[l, r)元素中最小的元素，返回索引值
    **/
    int findMin(T a[], int l, int r) {
        int minIndex = l;
        for(int i = l + 1; i < r; i++) {
            if(c->isGreaterThan(a[minIndex], a[i])) {
                minIndex = i;
            }
        }
        return minIndex;
    }

public:
    SelectionSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = 0; i < n; i++) {
            int minIndex = findMin(a, i, n);
            swap(a[i], a[minIndex]);
        }
    }
    string getSortName() {
        return "selection sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~SelectionSort() {
    }
};

#endif // SELECTIONSORT_H_INCLUDED
