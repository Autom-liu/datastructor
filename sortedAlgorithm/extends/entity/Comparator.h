#ifndef COMPARATOR_H_INCLUDED
#define COMPARATOR_H_INCLUDED

template <typename T>
class Comparator {
public:
    virtual bool isLessThan(T a, T b) = 0;
    virtual bool isLessOrEqual(T a, T b) = 0;
    virtual bool isGreaterThan(T a, T b) = 0;
    virtual bool isGreaterOrEqual(T a, T b) = 0;
    virtual bool equals(T a, T b) = 0;
    virtual ~Comparator() {}
};

#endif // COMPARATOR_H_INCLUDED
