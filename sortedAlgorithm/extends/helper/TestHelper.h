#ifndef TESTHELPER_H_INCLUDED
#define TESTHELPER_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "../entity/Comparator.h"
#include "../entity/IntegerComparator.h"

using namespace std;

namespace TestHelper {


    int getRandom(int l, int r) {
        return rand() % (r - l) + l;
    }

    IntegerComparaor* getIntComparator() {
        return new IntegerComparaor();
    }

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
}

#endif // TESTHELPER_H_INCLUDED
