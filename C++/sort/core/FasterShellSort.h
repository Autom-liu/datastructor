#ifndef FASTERSHELLSORT_H_INCLUDED
#define FASTERSHELLSORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

template <typename T>
class FasterShellSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    int getMaxGap(int n) {
        int gap = 1;
        while(gap < n / 3) {
            gap = 3 * gap + 1;
        }
        return gap;
    }

public:
    FasterShellSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int gap = getMaxGap(n); gap >= 1; gap /= 3) {
            for(int i = gap; i < n; i++) {
                /// 间隔为gap序列进行插入排序
                T e = a[i];
                int j = i;
                for(j = i; j >= gap && c->isLessThan(e, a[j-gap]); j -= gap) {
                    a[j] = a[j-gap];
                }
                a[j] = e;
            }
        }
    }
    string getSortName() {
        return "Faster Shell Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterShellSort() {
    }
};

#endif // FASTERSHELLSORT_H_INCLUDED
