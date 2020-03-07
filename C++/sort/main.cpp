#include <iostream>
#include <vector>
#include "core/SortAlgorithm.h"
#include "entity/Comparator.h"
#include "helper/SortTestHelper.h"
#include "core/SelectionSort.h"
#include "core/InsertionSort.h"
#include "core/BubbleSort.h"
#include "core/ShellSort.h"
using namespace std;

void executeTest(vector<SortAlgorithm<int>*> sorter, int* arr, int n) {
    for(unsigned int i = 0; i < sorter.size(); i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        delete[] arr2;
    }
}

void reverseSortTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"nearlySortTest:"<<endl;
    int* arr = SortTestHelper::generateReserve(n);
    executeTest(sorter, arr, n);
    delete[] arr;
}

void nearlySortTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"reverseSortTest:"<<endl;
    int* arr = SortTestHelper::generateNearlySortedCase(n, 100);
    executeTest(sorter, arr, n);
    delete[] arr;
}

/**
* �������ظ�Ԫ�ص�����
**/
void repeatTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"repeatTest:"<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, 3);
    executeTest(sorter, arr, n);
    delete[] arr;
}

/**
* ������Է���
**/
void originTest(vector<SortAlgorithm<int>*> sorter, int n) {
    cout<<"originTest:"<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, n * 10);
    executeTest(sorter, arr, n);
    delete[] arr;
}


int main()
{
    int n = 1000;
    Comparator<int>* ic = SortTestHelper::getIntComparator();

    vector<SortAlgorithm<int>*> sorter;
    sorter.push_back(new SelectionSort<int>(ic));
    sorter.push_back(new InsertionSort<int>(ic));
    sorter.push_back(new ShellSort<int>(ic));
    sorter.push_back(new FasterInsertionSort<int>(ic));
    sorter.push_back(new FasterShellSort<int>(ic));
    sorter.push_back(new FasterSelectionSort<int>(ic));
    sorter.push_back(new BubbleSort<int>(ic));
    sorter.push_back(new FasterBubbleSort<int>(ic));
    sorter.push_back(new SelectionSort<int>(ic));
    sorter.push_back(new SelectionSort<int>(ic));

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
* 10W规模的数据，随机序列
* SelectionSort：           25.496
* InsertionSort：           24.956
* BubbleSort:               57.417
* ShellSort:                0.045
* FasterShellSort:          0.036
* FasterInsertionSort：     15.48
* FasterSelectionSort:      23.784
* FasterBubbleSort:         60.21
* 重复序列：
* SelectionSort：           29.669
* InsertionSort：           17.999
* BubbleSort:               50.483
* ShellSort:                0.023
* FasterShellSort:          0.011
* FasterInsertionSort：     11.654
* FasterSelectionSort:      26.424
* FasterBubbleSort:         52.77
* 近乎有序列：
* SelectionSort：           30.661
* InsertionSort：           0.026
* BubbleSort:               15.307
* ShellSort:                0.024
* FasterShellSort:          0.013
* FasterInsertionSort：     0.018
* FasterSelectionSort:      26.944
* FasterBubbleSort:         3.341
* 完全逆序:
* SelectionSort：           26.524
* InsertionSort：           48.98
* BubbleSort:               56.016
* ShellSort:                0.025
* FasterShellSort:          0.014
* FasterInsertionSort：     33.643
* FasterSelectionSort:      27.084
* FasterBubbleSort:         56.049
***/
