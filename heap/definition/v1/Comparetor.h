#ifndef COMPARETOR_H_INCLUDED
#define COMPARETOR_H_INCLUDED

template <typename T>
class Comparetor {

public:
    virtual int compare(T v1, T v2) = 0;

    bool isLessThan(T v1, T v2) {
        return compare(v1, v2) < 0;
    }

};

#endif // COMPARETOR_H_INCLUDED
