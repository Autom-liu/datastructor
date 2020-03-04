#ifndef SORTALGORITHM_H_INCLUDED
#define SORTALGORITHM_H_INCLUDED
#include "../entity/Comparator.h"

#include <cstring>

using namespace std;

template <typename T>
class SortAlgorithm {
public:
    virtual void sort(T a[], int n)=0;
    virtual string getSortName() = 0;
    virtual Comparator<T>* getComparator() = 0;
    virtual ~SortAlgorithm() {}
};

#endif // SORTALGORITHM_H_INCLUDED
