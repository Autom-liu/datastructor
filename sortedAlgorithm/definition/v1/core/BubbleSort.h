#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED

#include "../entity/Comparator.h"
#include "SortAlgorithm.h"

/**
* 冒泡排序
* 核心原理：两两不断交换位置，使最大的元素一定冒到最后，下一轮只关注前n-1个即可。
* 实现原理：从i=1遍历整个数组，与前一个元素对比，前一个大的话就交换，完成一轮。n--继续下一轮。
* 优化策略：若整个数组已经有序，则无需再交换元素了。
* 性能比较：过度交换操作导致效率比其他平方级别的算法都低下。
* 情况比较：若数据近乎有序的情况下效果较好，但远低于插入排序。
**/
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

/**
* 冒泡排序优化方案
* 优化策略：可以记录上一次不再交换的位置newn，因为从那个位置开始后面的元素都已经有序，关注前newn个元素即可。
* 情况对比：在近乎有序的数据排序有极大提高效果，仍比不上插入排序，且在一般情况反而有一部分损失。
**/
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
