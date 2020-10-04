#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef std::string string;

class IndexOutOfBoundException {
private:
    string msg;
public:
    IndexOutOfBoundException(string msg) : msg(msg) {}
};


template <typename T>
class DQueue {
private:

    T* data;

    int rear;

    int front;

    int capacity;

    int length;

    void resize(int newCapacity) {
        int oldCapacity = this->capacity;
        T* newData = new T[newCapacity];
        for(int i = front, j = 0; j < oldCapacity; i=(i+1)%capacity) {
            newData[j++] = this->data[i];
        }
        delete this->data;
        this->data = newData;
        this->front = 0;
        this->rear = oldCapacity;
        this->capacity = newCapacity;
        this->length = oldCapacity;
    }

public:

    DQueue(int capacity = 16) {
        this->data = new T[capacity];
        this->rear = 0;
        this->front = 0;
        this->capacity = capacity;
    }

    int getSize() {
        return this->length;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return length == 0;
    }

    bool isFull() {
        return length >= capacity;
    }

    void pushBack(T ele) {
        if(isFull()) {
            resize(capacity * 2);
        }
        data[rear] = ele;
        rear = (rear + 1) % capacity;
        length++;
    }

    void pushTop(T ele) {
        if(isFull()) {
            resize(capacity * 2);
        }
        front = (front - 1 + capacity) % capacity;
        data[front] = ele;
        length++;
    }

    T popTop() {
        if(isEmpty()) {
            throw IndexOutOfBoundException("in popTop");
        }
        T res = data[front];
        front = (front + 1) % capacity;
        length--;
        return res;
    }

    T popBack() {
        if(isEmpty()) {
            throw IndexOutOfBoundException("in popBack");
        }
        rear = (rear - 1 + capacity) % capacity;
        length--;
        return data[rear];
    }

    T top() {
        if(isEmpty()) {
            throw IndexOutOfBoundException("in top");
        }
        return data[front];
    }

    T back() {
        if(isEmpty()) {
            throw IndexOutOfBoundException("in back");
        }
        return data[(rear - 1 + capacity) % capacity];
    }

    ~DQueue() {
        delete data;
    }

};

#endif // QUEUE_H_INCLUDED
