#ifndef INTEGERCOMPARATOR_H_INCLUDED
#define INTEGERCOMPARATOR_H_INCLUDED

#include "Comparator.h"

class IntegerComparaor : public Comparator<int> {
public:

    bool isLessThan(int a, int b) {
        return a < b;
    }


    bool isLessOrEqual(int a, int b) {
        return a <= b;
    }

    bool isGreaterThan(int a, int b) {
        return a > b;
    }

    bool isGreaterOrEqual(int a, int b) {
        return a >= b;
    }


    bool equals(int a, int b) {
        return a == b;
    }

    ~IntegerComparaor() {

    }
};

#endif // INTEGERCOMPARATOR_H_INCLUDED
