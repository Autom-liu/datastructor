#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Array.h"

template <typename T>
class Stack {

private:
    Array<T>* container;

public:

    Stack(int capacity = 16) {
        this->container = new Array<T>(capacity);
    }

    T pop() {
        return this->container->removeLast();
    }

    T top() {
        return container->get(size() - 1);
    }

    void push(T ele) {
        container->add(ele);
    }

    int size() {
        return container->getLength();
    }

    bool isEmpty() {
        return container->isEmpty();
    }

    ~Stack() {
        delete container;
    }

};

#endif // STACK_H_INCLUDED
