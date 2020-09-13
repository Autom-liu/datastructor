#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"
#include "../entity/Comparator.h"

/**
* 插入排序：
* 核心原理：设[0, i)已经有序，将第i个元素插入到已经有序的序列中
* 实现原理：从第i个开始往前遍历，若前一个元素较大，则进行交换，否则可以提前结束本轮。
* 性能比较：插入排序在平方级别的排序总体性能是最好的
* 情况比较：在重复序列和近乎有序的序列上表现出极致的性能，因为近乎有序的序列上提前结束使得复杂度接近线性级别
*           但是在完全逆序的情况下，表现出最差的情况（比选择排序还要差）
**/
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

/**
* 插入排序的一种优化
* 优化策略：替代多次交换为一次赋值操作。
* 实现原理：在需要交换的地方不进行交换，而只是前一个元素往后移，最后再把原第i个元素放置在结束一轮后的位置上。
* 情况比较：优化后比优化前均有质的提升，是平方级别的王者，在小规模的序列以及近乎有序的序列上被广泛应用。
**/
template <typename T>
class FasterInsertionSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    void insertProperIndex(T arr[], int i) {
        T e = arr[i];
        int j = i;
        for(j = i; j > 0 && c->isLessThan(e, arr[j-1]); j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
public:
    FasterInsertionSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int i = 1; i < n; i++) {
            insertProperIndex(a, i);
        }
    }
    string getSortName() {
        return "Faster Insertion Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterInsertionSort() {

    }
};

template <typename T>
class BinaryInsertSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
public:
    BinaryInsertSort<T>(Comparator<T>* c) {
        this->c = c;
    }
    void sort(T arr[], int n) {
        for(int i = 1; i < n; i++) {
            T target = arr[i];
            int index = binarySearch(arr, 0, i, target);
            int j = i;
            for(j = i; j > index; j--) {
                arr[j] = arr[j-1];
            }
            arr[j] = target;
        }
    }
    /// [l, r)
    int binarySearch(T arr[], int l, int r, T target) {
        while(l < r) {
            int mid = (r + l)/2;
            if(c->equals(arr[mid], target)) {
                return mid;
            } else if(c->isLessThan(target, arr[mid])) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
    string getSortName() {
        return "Binary Insertion Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~BinaryInsertSort() {

    }

};

#endif // INSERTIONSORT_H_INCLUDED
