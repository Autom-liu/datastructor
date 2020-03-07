#ifndef SORTTESTHELPER_H_INCLUDED
#define SORTTESTHELPER_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "../entity/Comparator.h"
#include "../entity/IntegerComparator.h"

using namespace std;

namespace SortTestHelper {

    /**
    *   generate a random array in the range of [l, r)
    **/
    int* generateTestCase(int n, int l, int r) {
        assert( l <= r);
        int* ret = new int[n];
        srand(time(NULL));
        for(int i = 0; i < n; i++) {
            int a = rand() % (r - l) + l;
            ret[i] = a;
        }
        return ret;
    }

    int* generateNearlySortedCase(int n, int swapTime) {
        int* ret = new int[n];
        for(int i = 0; i < n; i++) {
            ret[i] = i;
        }
        srand(time(NULL));
        for(int i = 0; i < swapTime; i++) {
            int posx = rand() % n;
            int posy = rand() % n;
            swap(ret[posx], ret[posy]);
        }
        return ret;
    }

    int* generateReserve(int n) {
        int* ret = new int[n];
        for(int i = 0; i < n; i++) {
            ret[i] = n - i;
        }
        return ret;
    }

    template <typename T>
    T* copyArray(T a[], int n) {
        T* ret = new T[n];
        copy(a, a+n, ret);
        return ret;
    }

    IntegerComparaor* getIntComparator() {
        return new IntegerComparaor();
    }

    /**
    * test the array is sorted
    **/
    template <typename T>
    bool isSorted(T arr[], int n, Comparator<T>* comparator) {
        for(int i = 0; i < n - 1; i ++) {
            if(comparator->isGreaterThan(arr[i], arr[i+1])) {
                return false;
            }
        }
        return true;
    }

    /**
    * print an array
    **/
    template <typename T>
    void printArray(T arr[], int n) {

        for(int i = 0; i < n; i++) {
            cout<< arr[i] << " ";
        }
        cout<<endl;
    }

    /**
    *  test sort
    **/
    template <typename T>
    void testSort(SortAlgorithm<T>* sorter, T arr[], int n) {
        clock_t startTime = clock();
        sorter->sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n, sorter->getComparator()));
        cout<< sorter->getSortName()<<" : "<<double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

    }

};

#endif // SORTTESTHELPER_H_INCLUDED
