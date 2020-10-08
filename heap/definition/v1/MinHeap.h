#ifndef MINHEAP_H_INCLUDED
#define MINHEAP_H_INCLUDED

#include "Comparetor.h"
#include "Array.h"

template <typename T>
class MinHeap {
private:

    Array<T>* heap;

    Comparetor<T>* c;

    int parent(int index) {
        return (index - 1) / 2;
    }

    int left(int index) {
        return index * 2 + 1;
    }

    int right(int index) {
        return index * 2 + 2;
    }

    /**
    *   以k为索引的结点向上堆化
    **/
    void shiftUp(int k) {
        T value = heap->get(k);
        while(k > 0 && c->isLessThan(value, heap->get(parent(k)))) {
            heap->set(k, heap->get(parent(k)));
            k = parent(k);
        }
        heap->set(k, value);
    }

    void shiftDown(int k) {

        T value = heap->get(k);

        while(left(k) < heap->getLength()) {
            int j = left(k);
            if(j+1 < size() && c->isLessThan(heap->get(j+1), heap->get(j))) {
                j = j+1;
            }
            if(c->isLessThan(value, heap->get(j))) {
                break;
            }
            heap->set(k, heap->get(j));
            k = j;
        }
        heap->set(k, value);
    }

public:

    MinHeap(Comparetor<T>* c, int capacity = 16) {
        this->heap = new Array<T>(capacity);
        this->c = c;
    }

    MinHeap(Comparetor<T>* c, T* arr, int size) {
        this->heap = new Array<T>(arr, size);
        this->c = c;

        for(int i = parent(size - 1); i >= 0; i--) {
            shiftDown(i);
        }
    }

    int size() {
        return heap->getLength();
    }

    bool isEmpty() {
        return heap->isEmpty();
    }

    void add(T value) {
        heap->add(value);
        shiftUp(heap->getLength() - 1);
    }

    T top() {
        if(isEmpty()) {
            throw new IndexOutOfBoundException("top");
        }
        return heap->get(0);
    }

    T pop() {
        if(isEmpty()) {
            throw new IndexOutOfBoundException("pop");
        }
        T ret = top();

        T newtop = heap->removeLast();

        heap->set(0, newtop);

        shiftDown(0);

        return ret;

    }

    T replace(T value) {
        T ret = top();
        heap->set(0, value);
        shiftDown(0);
        return ret;
    }

    typename Array<T>::iterator* newIterator() {
        return heap->newIterator();
    }

    ~MinHeap() {
        delete heap;
    }

};

#endif // MINHEAP_H_INCLUDED
