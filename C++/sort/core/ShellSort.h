#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED


template <typename T>
class ShellSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    /**
    *  ...arr[i-3*gap] arr[i-2*gap] arr[i-gap] arr[i]...
    **/
    void insertProper(T arr[], int gap, int i) {
        T inserted = arr[i];
        int j = i - gap;
        for(j = i - gap; j >= 0 && c->isLessThan(inserted, arr[j]); j -= gap) {
            arr[j+gap] = arr[j];
        }
        arr[j+gap] = inserted;
    }
public:
    ShellSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int gap = n/2; gap > 0; gap /= 2) {
            for(int i=gap; i<n; i++) {
                insertProper(a, gap, i);
            }
        }
    }
    string getSortName() {
        return "Shell Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~ShellSort() {
    }
};



template <typename T>
class FasterShellSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    int getMaxGap(int n) {
        int gap = 1;
        while(gap < n / 3) {
            gap = 3 * gap + 1;
        }
        return gap;
    }

public:
    FasterShellSort<T> (Comparator<T>* c) {
        this->c = c;
    }
    void sort(T a[], int n) {
        for(int gap = getMaxGap(n); gap >= 1; gap /= 3) {
            for(int i = gap; i < n; i++) {
                T e = a[i];
                int j = i;
                for(j = i; j >= gap && c->isLessThan(e, a[j-gap]); j -= gap) {
                    a[j] = a[j-gap];
                }
                a[j] = e;
            }
        }
    }
    string getSortName() {
        return "Faster Shell Sort";
    }

    Comparator<T>* getComparator() {
        return this->c;
    }
    ~FasterShellSort() {
    }
};

#endif // SHELLSORT_H_INCLUDED
