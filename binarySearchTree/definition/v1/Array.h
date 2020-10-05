#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef std::string string;

#ifndef EXCEPTION
#define EXCEPTION
class IndexOutOfBoundException {
private:
    string msg;
public:
    IndexOutOfBoundException(string msg) : msg(msg) {}
};
#endif // EXCEPTION

template <typename E>
class Array {
private:
    E* data;
    int length;
    int capacity;
    void copyArray(E* arr, int sz) {
        copyArray(arr, 0, 0, sz);
    }
    void copyArray(E* arr, int srcPos, int destPos, int length) {
        for(int i = 0; i < length; i++) {
            data[srcPos + i] = arr[destPos + i];
        }
    }
    void relength(int newCapacity) {
        E* oldData = data;
        data = new E[newCapacity];
        copyArray(oldData, length);
        delete oldData;
    }
public:
    Array(int capacity = 16) {
        this->data = new E[capacity];
        this->length = 0;
        this->capacity = capacity;
    }
    Array(E* arr, int sz) {
        data = new E[capacity = sz * 2];
        length = sz;
        copyArray(arr, sz);
    }
    int getLength() {
        return length;
    }
    int getCapacity() {
        return capacity;
    }
    bool isEmpty() {
        return length == 0;
    }
    bool contains(E e) {
        for(int i = 0; i < length; i++) {
            if(data[i] == e) {
                return true;
            }
        }
        return false;
    }
    int find(E e) {
        for(int i = 0; i < length; i++) {
            if(data[i] == e) {
                return i;
            }
        }
        return -1;
    }
    bool checkIndex(int index) {
        return index < 0 || index > length;
    }
    void insert(int index, E ele) {
        if(checkIndex(index)) {
            return ;
        }
        if(length >= capacity) {
            relength(capacity = capacity * 2);
        }
        for(int i = length-1; i >= index; i--) {
            data[i + 1] = data[i];
        }
        data[index] = ele;
        length++;

    }
    void add(E ele) {
        insert(length, ele);
    }
    void prepend(E ele) {
        insert(0, ele);
    }
    E get(int index) {
        if(checkIndex(index)) {
            throw IndexOutOfBoundException("" + index);
        }
        return data[index];
    }
    E remove(int index) {
        if(checkIndex(index)) {
            throw IndexOutOfBoundException("" + index);
        }
        E ele = data[index];
        for(int i = index + 1; i < length; i++) {
            data[i-1] = data[i];
        }
        length--;
        if(length < capacity / 4 && capacity > 16) {
            relength(capacity = capacity  / 2);
        }
        return ele;
    }
    E removeFirst() {
        return remove(0);
    }
    E removeLast() {
        return remove(length-1);
    }

    class iterator;

    Array<E>::iterator* newIterator() {
        return new Array<E>::iterator(this->data, this->length);
    }

    class iterator {
    private:
        int index;
        int length;
        E* data;
    public:
        iterator(E* data, int length) {
            this->index = 0;
            this->data = data;
            this->length = length;
        }
        bool hasNext() {
            return index < length;
        }
        E next() {
            return data[index++];
        }
    };

};

#endif // ARRAY_H_INCLUDED
