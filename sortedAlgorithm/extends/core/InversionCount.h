#ifndef INVERSIONCOUNT_H_INCLUDED
#define INVERSIONCOUNT_H_INCLUDED

#include "../entity/Comparator.h"

template <typename T>
class InversionCount {
private:
    Comparator<T>* c;
    T* aux;
    /// [l, r)
    long __doCount(T arr[], int l, int r) {
        if(l >= r - 1) {
            return 0;
        }
        int mid = (l + r)/2;
        long res1 = __doCount(arr, l, mid);
        long res2 = __doCount(arr, mid, r);
        if(c->isLessThan(arr[mid-1], arr[mid])) {
            return res1 + res2;
        }
        return res1 + res2 + __merge(arr, l, mid, r);
    }
    long __merge(T arr[], int l, int mid, int r) {
        for(int i = l; i < r; i++) {
            aux[i] = arr[i];
        }
        int i = l, j = mid;
        long res = 0L;
        for(int k = l; k < r; k++) {
            if(j >= r) {
                arr[k] = aux[i++];
            } else if(i >= mid) {
                arr[k] = aux[j++];
            } else if(c->isLessOrEqual(aux[i], aux[j])) {
                arr[k] = aux[i++];
            } else {
                arr[k] = aux[j++];
                res += mid - i;
            }
        }
        return res;
    }
public:
    InversionCount(Comparator<T>* c) {
        this->c = c;
    }
    long doCount(T arr[], int n) {
        this->aux = new T[n];
        long res = __doCount(arr, 0, n);
        delete[] aux;
        return res;
    }
    long doCountTest(T arr[], int n) {
        long sum = 0L;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(arr[j] < arr[i]) {
                    sum++;
                }
            }
        }
        return sum;
    }

};

#endif // INVERSIONCOUNT_H_INCLUDED
