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

template <typename T>
class FasterBubbleSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
public:
    FasterBubbleSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        int newn = 0;
        do {
            newn = 0;
            for(int i = 1; i < n; i++) {
                if(c->isLessThan(a[i], a[i-1])) {
                    swap(a[i], a[i-1]);
                    newn = i;
                }
            }
            n = newn;
        } while(newn > 0);
    }
    string getSortName() {
        return "Faster Bubble Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterBubbleSort() {

    }
};


#endif // BUBBLESORT_H_INCLUDED
