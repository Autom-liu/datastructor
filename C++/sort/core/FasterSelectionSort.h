#ifndef FASTERSELECTIONSORT_H_INCLUDED
#define FASTERSELECTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"

/**
* 对选择排序的一种优化
* 此优化重点在于，可以同时找出未处理元素的最大值和最小值
* 放在合适的位置
**/
template <typename T>
class FasterSelectionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
public:
    FasterSelectionSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        int left = 0;
        int right = n - 1;
        while(left < right) {
            int minIndex = left;
            int maxIndex = right;

            if(c->isGreaterThan(a[minIndex], a[maxIndex])) {
                swap(a[minIndex], a[maxIndex]);
            }

            for(int i = left + 1; i < right; i ++) {
                if(c->isLessThan(a[i], a[minIndex])) {
                    minIndex = i;
                } else if(c->isGreaterThan(a[i], a[maxIndex])){
                    maxIndex = i;
                }
            }
            swap(a[left], a[minIndex]);
            swap(a[right], a[maxIndex]);
            left++;
            right--;
        }
    }
    string getSortName() {
        return "Faster Selection sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterSelectionSort() {
    }
};

#endif // FASTERSELECTIONSORT_H_INCLUDED
