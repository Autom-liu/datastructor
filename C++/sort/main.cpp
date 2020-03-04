#include <iostream>
#include "core/SortAlgorithm.h"
#include "entity/Comparator.h"
#include "helper/SortTestHelper.h"
#include "core/SelectionSort.h"
#include "core/InsertionSort.h"
#include "core/BubbleSort.h"
#include "core/ShellSort.h"
#include "core/FasterSelectionSort.h"
#include "core/FasterInsertionSort.h"
#include "core/FasterBubbleSort.h"
#include "core/FasterShellSort.h"
using namespace std;

void reverseSortTest(SortAlgorithm<int>* sorter[], int len, int n) {
    cout<<"nearlySortTest:"<<endl;
    int* arr = SortTestHelper::generateReserve(n);
    for(int i = 0; i < len; i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        delete[] arr2;
    }
    delete[] arr;
}

void nearlySortTest(SortAlgorithm<int>* sorter[], int len, int n) {
    cout<<"reverseSortTest:"<<endl;
    int* arr = SortTestHelper::generateNearlySortedCase(n, 100);
    for(int i = 0; i < len; i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        delete[] arr2;
    }
    delete[] arr;
}

/**
* �������ظ�Ԫ�ص�����
**/
void repeatTest(SortAlgorithm<int>* sorter[], int len, int n) {
    cout<<"repeatTest:"<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, 3);
    for(int i = 0; i < len; i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        delete[] arr2;
    }
    delete[] arr;
}

/**
* ������Է���
**/
void originTest(SortAlgorithm<int>* sorter[], int len, int n) {
    cout<<"originTest:"<<endl;
    int* arr = SortTestHelper::generateTestCase(n, 0, n * 10);
    for(int i = 0; i < len; i++) {
        int* arr2 = SortTestHelper::copyArray(arr, n);
        SortTestHelper::testSort(sorter[i], arr2, n);
        delete[] arr2;
    }
    delete[] arr;
}


int main()
{
    int n = 100000;
    int len = 8;
    Comparator<int>* ic = SortTestHelper::getIntComparator();
    SortAlgorithm<int>* sorter[] = {
        new SelectionSort<int>(ic),
        new InsertionSort<int>(ic),
        new ShellSort<int>(ic),
        new FasterInsertionSort<int>(ic),
        new FasterShellSort<int>(ic),
        new FasterSelectionSort<int>(ic),
        new BubbleSort<int>(ic),
        new FasterBubbleSort<int>(ic)
    };

    //originTest(sorter, len, n);
    //repeatTest(sorter, len, n);
    //nearlySortTest(sorter, len, n);
    reverseSortTest(sorter, len, n);

    for(int i = 0; i < len; i++) {
        delete sorter[i];
    }
    delete ic;
    return 0;
}


/**
* ʵ�����ݽ��ۣ�
* 10W��ģ�����ݣ��������
* SelectionSort��           25.496
* InsertionSort��           24.956
* BubbleSort:               57.417
* ShellSort:                0.045
* FasterShellSort:          0.036
* FasterInsertionSort��     15.48
* FasterSelectionSort:      23.784
* FasterBubbleSort:         60.21
* �ظ����У�
* SelectionSort��           29.669
* InsertionSort��           17.999
* BubbleSort:               50.483
* ShellSort:                0.023
* FasterShellSort:          0.011
* FasterInsertionSort��     11.654
* FasterSelectionSort:      26.424
* FasterBubbleSort:         52.77
* ���������У�
* SelectionSort��           30.661
* InsertionSort��           0.026
* BubbleSort:               15.307
* ShellSort:                0.024
* FasterShellSort:          0.013
* FasterInsertionSort��     0.018
* FasterSelectionSort:      26.944
* FasterBubbleSort:         3.341
* ��ȫ����:
* SelectionSort��           26.524
* InsertionSort��           48.98
* BubbleSort:               56.016
* ShellSort:                0.025
* FasterShellSort:          0.014
* FasterInsertionSort��     33.643
* FasterSelectionSort:      27.084
* FasterBubbleSort:         56.049
***/
