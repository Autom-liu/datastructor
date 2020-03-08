#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED

/**
* 希尔排序
* 核心原理：选取一个增量序列，以这个增量序列作为每一段排序的【间隔】，对带间隔的序列进行插入排序。
* 实现原理：要先找到满足条件的最大值，例如以1,2,4,8,...这种以2为公比的序列，其最大值是n/2，以该值作为间隔gap不断往前推（不断除以2）
*           从这个gap位置开始遍历整个数组，每一次进行插入排序时注意是将arr[i]插入到(...arr[i-3*gap] arr[i-2*gap] arr[i-gap])有序序列中，注意是以gap为偏移量。
*           也就是说，若前gap个元素比较大，那么第前gap个元素往后移动。
*           在实现上需要注意边界值得处理，前一个元素表示为j-gap，应确保j-gap>=0
* 情况比较： 比平方级别排序算法好太多，但比其他高级排序算法差些。但是在特殊的场景下（近乎有序，重复序列，完全逆序）表现较为出色
**/
template <typename T>
class ShellSort : public SortAlgorithm<T> {
private:
    Comparator<T>* c;
    /**
    *  ...arr[i-3*gap] arr[i-2*gap] arr[i-gap] arr[i]...
    **/
    void insertProper(T arr[], int gap, int i) {
        T inserted = arr[i];
        int j = i;
        for(j = i; j >= gap && c->isLessThan(inserted, arr[j-gap]); j -= gap) {
            arr[j] = arr[j-gap];
        }
        arr[j] = inserted;
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


/**
* 希尔排序的一种优化
* 希尔排序的优化在于选取的序列不同，选取的序列很大程度上决定了算法的时间复杂度。
* 在本例中选取的序列为1,4,13,41,... 递推公式为 A(n+1)=3A(n)+1 公比为3的序列作为【间隔】gap
* 在实现上一模一样，就是找到最大值后不断除以3往前递推，其他逻辑一成不变。
* 优化后相对于优化前总体性能有所提升，在一般随机场景仍低于其他高级排序，在其他特殊场景有显著的出色表现。
**/
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
