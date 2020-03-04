#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

template <typename T>
class BubbleSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
public:
    BubbleSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        bool hasSwap = false;
        do {
            hasSwap = false;
            for(int i = 1; i < n; i++) {
                if(c->isLessThan(a[i], a[i-1])) {
                    swap(a[i], a[i-1]);
                    hasSwap = true;
                }
            }
            n--;
        } while(hasSwap);

    }
    string getSortName() {
        return "Bubble Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~BubbleSort() {

    }
};

#endif // BUBBLESORT_H_INCLUDED
