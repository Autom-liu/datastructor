#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

template <typename T>
class QuickSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    int __partition(T arr[], int l, int r) {
        swap(arr[l], arr[rand() % (r - l) + l]);
        T e = arr[l];
        int j = l;
        /// [l, j] < v  [j+1, i] >= v
        for(int i = j+1; i < r; i++) {
            if(c->isLessThan(arr[i], e)) {
                swap(arr[++j], arr[i]);
            }
        }
        swap(arr[l], arr[j]);
        return j;
    }
public:
    QuickSort(Comparator<T>* c) {
        this->c = c;
    }
    /// [l, r)
    void __quickSort(T arr[], int l, int r) {
        if( r <= l) {
            return ;
        }
        int p = __partition(arr, l, r);
        __quickSort(arr, l, p);
        __quickSort(arr, p+1, r);
    }
    void sort(T arr[], int n) {
        __quickSort(arr, 0, n);
    }
    string getSortName() {
        return "Quick Sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~QuickSort() {

    }
};

template <typename T>
class FasterQuickSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
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
    int* __partition(T arr[], int l, int r) {
        swap(arr[l], arr[rand() % (r - l) + l]);
        int* ret = new int[2];
        T v = arr[l];
        int lt = l, gt = lt;
        /// [l, lt) < v  [lt, gt) == v  [gt, i) > v
        for(int i = gt; i < r; i++) {
            if(c->isLessThan(arr[i], v)) {
                T e = arr[i];
                arr[i] = arr[gt];
                arr[gt++] = arr[lt];
                arr[lt++] = e;
            } else if(c->equals(arr[i], v)) {
                swap(arr[gt++], arr[i]);
            }
        }
        ret[0] = lt;
        ret[1] = gt;
        return ret;
    }
public:
    FasterQuickSort(Comparator<T>* c) {
        this->c = c;
    }
    /// [l, r)
    void __quickSort(T arr[], int l, int r) {
        if( r - l < 16) {
            return rangeInsertSort(arr, l, r);
        }
        int* p = __partition(arr, l, r);
        __quickSort(arr, l, p[0] + 1);
        __quickSort(arr, p[1], r);
        delete[] p;
    }
    void sort(T arr[], int n) {
        __quickSort(arr, 0, n);
    }
    string getSortName() {
        return "Faster Quick Sort";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterQuickSort() {

    }
};

template <typename T>
class QuickSort2 : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
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
    int __partition(T arr[], int l, int r) {
        swap(arr[l], arr[rand() % (r - l) + l]);
        T e = arr[l];
        int i = l + 1, j = r - 1;
        while(i < j) {
            /// [l+1, i] < v  [j, r) >= v
            if(c->isGreaterOrEqual(arr[i], e)) {
                swap(arr[i], arr[j--]);
            } else {
                i++;
            }
            if(c->isLessThan(arr[j], e)) {
                swap(arr[i++], arr[j]);
            } else {
                j--;
            }
        }
        if(arr[j] < e) {
            swap(arr[j], arr[l]);
        } else if(j > l) {
            swap(arr[--j], arr[l]);
        }
        return j;
    }
public:
    QuickSort2(Comparator<T>* c) {
        this->c = c;
    }
    /// [l, r)
    void __quickSort(T arr[], int l, int r) {
        if( r - l < 16) {
            return rangeInsertSort(arr, l, r);
        }
        int p = __partition(arr, l, r);
        __quickSort(arr, l, p);
        __quickSort(arr, p+1, r);
    }
    void sort(T arr[], int n) {
        __quickSort(arr, 0, n);
    }
    int testPartition(T arr[], int n) {
        return __partition(arr, 0, n);
    }
    string getSortName() {
        return "Quick Sort2";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~QuickSort2() {

    }
};


template <typename T>
class QuickSort3 : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
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
    int __partition(T arr[], int l, int r) {
        swap(arr[l], arr[rand() % (r - l) + l]);
        T e = arr[l];
        int i = l, j = r - 1;
        while(i != j) {
            while(c->isGreaterOrEqual(arr[j], e) && j > i) {
                j--;
            }
            while(c->isLessOrEqual(arr[i], e) && i < j) {
                i++;
            }
            if(i < j) {
                swap(arr[i], arr[j]);
            }
        }
        arr[l] = arr[i];
        arr[i] = e;
        return i;
    }
public:
    QuickSort3(Comparator<T>* c) {
        this->c = c;
    }
    /// [l, r)
    void __quickSort(T arr[], int l, int r) {
        if( r - l < 16) {
            return rangeInsertSort(arr, l, r);
        }
        int p = __partition(arr, l, r);
        __quickSort(arr, l, p);
        __quickSort(arr, p+1, r);
    }
    void sort(T arr[], int n) {
        __quickSort(arr, 0, n);
    }
    int testPartition(T arr[], int n) {
        return __partition(arr, 0, n);
    }
    string getSortName() {
        return "Quick Sort3";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~QuickSort3() {

    }
};

template <typename T>
class FasterQuickSort2 : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
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
    int* __partition(T arr[], int l, int r) {
        swap(arr[l], arr[rand() % (r - l) + l]);
        int* ret = new int[2];
        T v = arr[l];
        int lt = l, gt = r, i = lt + 1;
        /// [l, lt) < v  [lt, i) == v  [gt, r) > v
        while(i < gt) {
            if(c->isLessThan(arr[i], v)) {
                swap(arr[lt++], arr[i++]);
            } else if(c->isGreaterThan(arr[i], v)) {
                swap(arr[--gt], arr[i]);
            } else {
                i++;
            }
        }
        ret[0] = lt;
        ret[1] = gt;
        return ret;
    }
public:
    FasterQuickSort2(Comparator<T>* c) {
        this->c = c;
    }
    /// [l, r)
    void __quickSort(T arr[], int l, int r) {
        if( r - l < 16) {
            return rangeInsertSort(arr, l, r);
        }
        int* p = __partition(arr, l, r);
        __quickSort(arr, l, p[0] + 1);
        __quickSort(arr, p[1], r);
        delete[] p;
    }
    void sort(T arr[], int n) {
        __quickSort(arr, 0, n);
    }
    string getSortName() {
        return "Faster Quick Sort2";
    }
    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterQuickSort2() {

    }
};


#endif // QUICKSORT_H_INCLUDED
