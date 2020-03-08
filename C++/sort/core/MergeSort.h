#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

template <typename T>
class MergeSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;

    /// [l, mid) [mid, r)
    void __merge(T arr[], int l, int mid, int r) {
        T* aux = new T[r-l];

        for(int i = l; i < r; i++) {
            aux[i-l] = arr[i];
        }

        int i = l, j = mid;
        for(int k = l; k < r; k++) {
            if(i >= mid) {
                arr[k] = aux[j-l];
                j++;
            } else if(j >= r) {
                arr[k] = aux[i-l];
                i++;
            } else if(c->isLessOrEqual(aux[i-l], aux[j-l])) {
                arr[k] = aux[i-l];
                i++;
            } else {
                arr[k] = aux[j-l];
                j++;
            }
        }
        delete[] aux;
    }
    /// [l, r)
    void __mergeSort(T arr[], int l, int r) {
        if(l >= r-1) {
            return ;
        }
        int mid = (l + r) / 2;
        __mergeSort(arr, l, mid);
        __mergeSort(arr, mid, r);
        __merge(arr, l, mid, r);
    }

public:
    MergeSort(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T arr[], int n) {
        __mergeSort(arr, 0, n);
    }
    string getSortName() {
        return "Merge Sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~MergeSort() {

    }
};

template <typename T>
class FasterMergeSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    T* aux;

    /// [l, mid) [mid, r)
    void __merge(T arr[], int l, int mid, int r) {

        for(int i = l; i < r; i++) {
            aux[i] = arr[i];
        }

        int i = l, j = mid;
        for(int k = l; k < r; k++) {
            if(i >= mid) {
                arr[k] = aux[j++];
            } else if(j >= r) {
                arr[k] = aux[i++];
            } else if(c->isLessOrEqual(aux[i], aux[j])) {
                arr[k] = aux[i++];
            } else {
                arr[k] = aux[j++];
            }
        }
    }
    /// [l, r)
    void __mergeSort(T arr[], int l, int r) {
        if(r - l <= 16) {
            return rangeInsertSort(arr, l, r);
        }
        int mid = (l + r) / 2;
        __mergeSort(arr, l, mid);
        __mergeSort(arr, mid, r);
        if(c->isLessThan(arr[mid], arr[mid-1])) {
            __merge(arr, l, mid, r);
        }
    }
    /// [l, r)
    void rangeInsertSort(T arr[], int l, int r) {
        for(int i = l; i < r; i++) {
            T e = arr[i];
            int j = i;
            for(j = i; j > l && c->isLessThan(e, arr[j-1]); j--) {
                arr[j] = arr[j-1];
            }
            arr[j] = e;
        }
    }
public:
    FasterMergeSort(Comparator<T>* c, int n) {
        this->c = c;
        this->aux = new int[n];
    }
    void sort(T arr[], int n) {
        __mergeSort(arr, 0, n);
    }
    string getSortName() {
        return "Faster Merge Sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterMergeSort() {
        delete[] aux;
    }
};


template <typename T>
class FasterMergeSortBU : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    T* aux;

    /// [l, mid) [mid, r)
    void __merge(T arr[], int l, int mid, int r) {

        for(int i = l; i < r; i++) {
            aux[i] = arr[i];
        }

        int i = l, j = mid;
        for(int k = l; k < r; k++) {
            if(i >= mid) {
                arr[k] = aux[j++];
            } else if(j >= r) {
                arr[k] = aux[i++];
            } else if(c->isLessOrEqual(aux[i], aux[j])) {
                arr[k] = aux[i++];
            } else {
                arr[k] = aux[j++];
            }
        }
    }
    /// [l, r)
    void __mergeSort(T arr[], int n, int minsz = 16) {
        for(int i = 0; i < n; i+=minsz) {
            rangeInsertSort(arr, i, min(i+minsz, n));
        }

        for(int k = minsz; k < n; k+=k) {
            for(int i=0; i < n-k; i+=k*2) {
                int mid = i + k;
                __merge(arr, i, mid, min(i+k*2, n));
            }
        }

    }
    /// [l, r)
    void rangeInsertSort(T arr[], int l, int r) {
        for(int i = l; i < r; i++) {
            T e = arr[i];
            int j = i;
            for(j = i; j > l && c->isLessThan(e, arr[j-1]); j--) {
                arr[j] = arr[j-1];
            }
            arr[j] = e;
        }
    }
public:
    FasterMergeSortBU(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T arr[], int n) {
        this->aux = new int[n];
        __mergeSort(arr, n);
        delete[] aux;
    }
    string getSortName() {
        return "BubbleUp Merge Sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterMergeSortBU() {
    }
};

#endif // MERGESORT_H_INCLUDED
