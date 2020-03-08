#ifndef SELECTIONSORT_H_INCLUDED
#define SELECTIONSORT_H_INCLUDED

#include "SortAlgorithm.h"

/**
* 选择排序
* 简单概述：找到最小的元素，与第一个交换，剩下部分也不断进行即可。
* 实现原理：从[i,n)中找最小的元素，与第i个交换完成一轮。i++进行下一轮。
* 性能比较：比较和交换次数都比较平均，整体性能都比较平均，优于冒泡，次于插入
* 情况比较：整体性能比较平均，最好最坏情况差距不大。
**/
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

/**
* 选择排序的一种优化
* 优化策略：可以在一轮中同时找出最大元素和最小元素，进行前后交换
* 实现原理：可以使用双头指针往中间靠的方式，同时记录最大元素和最小元素所在的索引。初始条件不满足时可以进行对比交换操作。
* 情况比较：总体情况比优化前性能略有提升，但提升效果并不算太明显，总体仍次于插入排序。
**/
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
