#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"

template <typename T>
class SelectionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;

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

#endif // SELECTIONSORT_H_INCLUDED
