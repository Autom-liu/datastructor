#include <iostream>
#include <vector>
#include "core/SortAlgorithm.h"
#include "entity/Comparator.h"
#include "helper/SortTestHelper.h"
#include "core/SelectionSort.h"
#include "core/InsertionSort.h"
#include "core/BubbleSort.h"
#include "core/ShellSort.h"
#include "core/MergeSort.h"
#include "core/QuickSort.h"
#include "core/HeapSort.h"
using namespace std;

void executeTest(vector<SortAlgorithm<int>*> sorter, int* arr, int n) {
    for(unsigned int i = 0; i < sorter.size(); i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        ///SortTestHelper::printArray(arr2, n);
        delete[] arr2;
    }
}

template<typename T>
void stdTest(T* arr, int n) {
    clock_t startTime = clock();
    sort(arr, arr + n, less<int>());
    clock_t endTime = clock();
    cout<<" std sort : "<<double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
}

void reverseSortTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"=====reverseSortTest========"<<endl;
    int* arr = SortTestHelper::generateReserve(n);
    executeTest(sorter, arr, n);
    stdTest(arr, n);
    delete[] arr;
}

void nearlySortTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"=======nearlySortTest============"<<endl;
    int* arr = SortTestHelper::generateNearlySortedCase(n, 100);
    executeTest(sorter, arr, n);
    stdTest(arr, n);
    delete[] arr;
}

void repeatTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"========repeatTest============="<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, 3);
    executeTest(sorter, arr, n);
    stdTest(arr, n);
    delete[] arr;
}


void originTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"===========originTest=============="<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, n * 10);
    executeTest(sorter, arr, n);
    stdTest(arr, n);
    delete[] arr;
}

int main()
{
    int n = 100000;
    Comparator<int>* ic = SortTestHelper::getIntComparator();

    vector<SortAlgorithm<int>*> sorter;
    ///sorter.push_back(new SelectionSort<int>(ic));
    sorter.push_back(new InsertionSort<int>(ic));
    sorter.push_back(new FasterInsertionSort<int>(ic));
    sorter.push_back(new BinaryInsertSort<int>(ic));
    ///sorter.push_back(new FasterSelectionSort<int>(ic));
    ///sorter.push_back(new BubbleSort<int>(ic));
    ///sorter.push_back(new FasterBubbleSort<int>(ic));
    ///sorter.push_back(new SelectionSort<int>(ic));
    ///sorter.push_back(new SelectionSort<int>(ic));
    ///sorter.push_back(new ShellSort<int>(ic));
    ///sorter.push_back(new FasterShellSort<int>(ic));
    ///sorter.push_back(new MergeSort<int>(ic));
    ///sorter.push_back(new FasterMergeSort<int>(ic, n));
    ///sorter.push_back(new FasterMergeSortBU<int>(ic));
    ///sorter.push_back(new QuickSort<int>(ic));
    ///sorter.push_back(new QuickSort2<int>(ic));
    ///sorter.push_back(new QuickSort3<int>(ic));
    ///sorter.push_back(new FasterQuickSort<int>(ic));
    ///sorter.push_back(new FasterQuickSort2<int>(ic));
    ///sorter.push_back(new HeapSort<int>(ic));
    ///sorter.push_back(new FasterHeapSort<int>(ic));

    ///int* arr = SortTestHelper::generateTestCase(n, 0, n * 10);
    ///int* arr = SortTestHelper::generateTestCase(n, 0, 3);
    ///int* arr = SortTestHelper::generateNearlySortedCase(n, 1);
    ///int* arr = SortTestHelper::generateReserve(n);



    originTest(sorter, n);
    repeatTest(sorter, n);
    nearlySortTest(sorter, n);
    reverseSortTest(sorter, n);



    for(unsigned int i = 0; i < sorter.size(); i++) {
        delete sorter[i];
    }
    delete ic;
    return 0;
}

/**
* 实验数据结论：
* 10W规模的数据，随机序列              100W规模数据                           1000W 规模数据
* SelectionSort：           25.496      ShellSort           0.603  0.61        9.453    9.114
* InsertionSort：           24.956      FasterShellSort     0.589  0.576       8.134    7.352
* BinaryInsertSort          5.765
* BubbleSort:               57.417      MergeSort           0.723  0.734       7.692    7.359
* ShellSort:                0.045       FasterMergeSort     0.296  0.29        2.323    2.235
* FasterShellSort:          0.036       QuickSort           0.321  0.318       10.901
* FasterInsertionSort：     15.48       QuickSort2          0.307  0.299       14.872
* FasterSelectionSort:      23.784      QuickSort3          0.311  0.31        10.28           8.466  8.318 7.518
* FasterBubbleSort:         60.21       FasterQuickSort     0.251  0.243       2.347    2.349  2.13
* 重复序列：                           FasterQuickSort2     0.294  0.305       2.833    2.729               2.307
*                                       HeapSort             0.537  0.52       7.631    7.269
*                                       FasterHeapSort       0.447  0.449      6.543    6.468
* SelectionSort：           29.669     重复序列
* InsertionSort：           17.999     ShellSort             0.235  0.234      2.885    3.093
* BubbleSort:               50.483     FasterShellSort       0.122  0.117      1.358    1.572
* BinaryInsertSort          6.141
* ShellSort:                0.023      MergeSort             0.646  0.642      7.259    7.092
* FasterShellSort:          0.011      FasterMergeSort       0.203  0.201      2.621    2.328
* FasterInsertionSort：     11.654     QuickSort             ----   ----       -----
* FasterSelectionSort:      26.424     QuickSort2            ----   ----       -----
* FasterBubbleSort:         52.77      QuickSort3            ----   ----       -----
* 近乎有序列：                        FasterQuickSort       0.028   0.026      0.358   0.344   0.258        0.295
* SelectionSort：           30.661    FasterQuickSort2       0.024   0.023      0.282   0.314
* BinaryInsertSort          0.021     HeapSort               0.249   0.259      2.797   3.335
*                                       FasterHeapSort       0.211   0.212      2.281   2.769
* InsertionSort：           0.026      近乎有序列：
* BubbleSort:               15.307     ShellSort             0.211  0.208       2.51    2.948
* ShellSort:                0.024      FasterShellSort       0.093  0.098       1.079   1.259
* FasterShellSort:          0.013      MergeSort             0.583  0.619       6.275   6.801
* FasterInsertionSort：     0.018      FasterMergeSort       0.012  0.012       0.095   0.112
* FasterSelectionSort:      26.944     QuickSort             0.3    0.335       19.981
* FasterBubbleSort:         3.341      QuickSort2            0.328  0.336       25.478
* 完全逆序:                            QuickSort3            0.239  0.233       19.408          11.898  1.034  1.066
* SelectionSort：           26.524     FasterQuickSort       0.512  0.533       33.112  32.863  23.787  2.579
* InsertionSort：           48.98      FasterQuickSort2      0.675  0.668       49.818  49.736                  2.324
* BinaryInsertSort          13.289     HeapSort             0.372  0.378       4.239   5.138
*                                       FasterHeapSort       0.302  0.304       3.436   4.264
* BubbleSort:               56.016     完全逆序
* ShellSort:                0.025      ShellSort             0.264  0.268       3.864   3.805
* FasterShellSort:          0.014      FasterShellSort       0.134  0.133       1.988   1.943
* FasterInsertionSort：     33.643     MergeSort             0.592  0.582       7.607   7.355
* FasterSelectionSort:      27.084     FasterMergeSort       0.189  0.189       2.466   2.057
* FasterBubbleSort:         56.049     QuickSort             0.488  0.487       38.337
*                                      QuickSort2            0.455  0.476       38.63
*                                      QuickSort3            0.315  0.309       26.497           6.424  ----  1.093
*                                      FasterQuickSort       0.52   0.507       37.715  35.946   27.752       -----
*                                      FasterQuickSort2      0.807  0.738       65.419  65.11
*                                       HeapSort             0.369  0.373       4.243   6.139
*                                       FasterHeapSort       0.303  0.303       3.537   4.525
***/
