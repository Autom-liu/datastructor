#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

template <typename T>
class HeapSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    void shiftDown(T arr[], int n, int k) {
        for(int left = 2*k+1; left < n; left=2*k+1) {
            int j = left;
            int right = left + 1;
            int v = arr[k];
            if(right >= n || c->isGreaterThan(arr[left], arr[right])) {
                j = left;
            } else {
                j = right;
            }
            if(c->isGreaterThan(arr[j], v)) {
                swap(arr[k], arr[j]);
                k = j;
            } else {
                break;
            }
        }
    }

public:
    HeapSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = (n - 2)/2; i >= 0; i--) {
            shiftDown(a, n, i);
        }
        for(int i = n-1; i > 0; i--) {
            swap(a[0], a[i]);
            shiftDown(a, i, 0);
        }
    }
    string getSortName() {
        return "Heap Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~HeapSort() {

    }
};


template <typename T>
class FasterHeapSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    void shiftDown(T arr[], int n, int k) {
        int e = arr[k];
        for(int left = 2*k+1; left < n; left=2*k+1) {
            int j = left;
            int right = left + 1;
            if(right >= n || c->isGreaterThan(arr[left], arr[right])) {
                j = left;
            } else {
                j = right;
            }
            if(c->isGreaterThan(arr[j], e)) {
                arr[k] = arr[j];
                k = j;
            } else {
                break;
            }
        }
        arr[k] = e;
    }

public:
    FasterHeapSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = (n - 2)/2; i >= 0; i--) {
            shiftDown(a, n, i);
        }
        for(int i = n-1; i > 0; i--) {
            swap(a[0], a[i]);
            shiftDown(a, i, 0);
        }
    }
    string getSortName() {
        return "Heap Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterHeapSort() {

    }
};


#endif // HEAPSORT_H_INCLUDED
