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
            /// Ñ°ÕÒarr[i] ·ÅÖÃµÄÎ»ÖÃ
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

#endif // INSERTIONSORT_H_INCLUDED
