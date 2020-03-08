#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

/**
* 归并排序
* 核心原理：数组平分为两段，对每一段进行归并排序，最后将两段有序数组合并为一段有序数组。
* 实现原理：核心算法在于合并两段数组，定好区间是关键，在本例中使用的区间均是前闭后开，合并函数定义的是
            将[l, mid) 和 [mid, r)两段序列进行合并。每一次合并需要另开空间，另开的空间长度为r-l，因此注意【偏移量的计算】
            对于合并操作，先判断一段有一段无的情况，在说两段都有的情况，注意排序结果的稳定性，相等时前一段的元素优先排在前面。
* 情况比较： 优于递归层次问题，随机情况下仅仅比希尔排序好一点点，但归并排序性能在其他情况都是稳定的，在未优化前各情况表现均不太好。
**/
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

/**
* 归并排序的一种优化：
* 优化策略一： 几乎对于所有排序的通用优化方案是：在数组规模相对小的情况下直接使用插入排序。
* 优化策略二： 一次申请空间，直接赋值，在归并过程中也就可以不用再计算偏移量了。
* 优化策略三： 在两段递归完成后，如果后一段第一个元素arr[mid]>=前一段最后一个元素arr[mid-1]则不需要合并，也就是说arr[mid]<arr[mid-1]时才需要合并
**/
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
