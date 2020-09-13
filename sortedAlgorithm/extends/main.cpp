#include <iostream>

#include "core/BinarySearch.h"
#include "helper/TestHelper.h"
#include "core/InversionCount.h"
#include "core/Kselection.h"

using namespace std;

int main()
{
    int n = 10;
    Comparator<int>* ic = TestHelper::getIntComparator();
    int* arr = TestHelper::generateTestCase(n, 0, n);
    sort(arr, arr+n, less<int>());
    TestHelper::printArray(arr, n);
    int target = TestHelper::getRandom(0, n);
    int index = BinarySearch::doSearch(arr, n, target, ic);
    cout<<"target = "<<target<<" index = "<<index;
    if(index > 0) {
        cout<<" arr[index] = "<<arr[index]<<endl;
    }
    cout<<endl;
    int* arr2 = TestHelper::generateNearlySortedCase(n, 1);
    TestHelper::printArray(arr2, n);
    InversionCount<int>* ivc = new InversionCount<int>(ic);
    long acRes = ivc->doCountTest(arr2, n);
    long res = ivc->doCount(arr2, n);
    cout<<"actual Count = "<<acRes<<" Inversion Count = "<<res<<endl;
    cout<<endl;

    int* arr3 = TestHelper::generateTestCase(n, 0, n * 10);
    TestHelper::printArray(arr3, n);
    int k = TestHelper::getRandom(0, n);
    Kselection<int>* ks = new Kselection<int>(ic);
    k = 9;
    int result = ks->doSearch(arr3, n, k);
    cout<<"The K = "<<k <<" selection = "<<result<<endl;
    sort(arr3, arr3 + n, less<int>());
    TestHelper::printArray(arr3, n);
    cout<<"test K selection = "<<arr3[k-1]<<endl;

    delete ivc;
    delete ic;
    delete ks;
    delete[] arr;
    delete[] arr2;
    return 0;
}
