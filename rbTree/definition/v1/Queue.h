#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

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

template <typename T>
class Queue {
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

    Queue(int capacity = 16) {
        this->data = new T[capacity];
        this->rear = 0;
        this->front = 0;
        this->capacity = capacity;
        this->length = 0;
    }

    int getSize() {
        return this->length;
    }

    bool isEmpty() {
        return length == 0;
    }

    bool isFull() {
        return length >= capacity;
    }

    void push(T ele) {
        if(isFull()) {
            resize(capacity * 2);
        }
        data[rear] = ele;
        rear = (rear + 1) % capacity;
        length++;
    }

    T pop() {
        if(isEmpty()) {
            throw IndexOutOfBoundException(string("front=" + front).append(" rear" + rear));
        }
        T res = top();
        front = (front + 1) % capacity;
        length--;
        return res;
    }

    T top() {
        if(isEmpty()) {
            throw IndexOutOfBoundException(string("front=" + front).append(" rear" + rear));
        }
        return data[front];
    }

    T back() {
        if(isEmpty()) {
            throw IndexOutOfBoundException(string("front=" + front).append(" rear" + rear));
        }
        return data[(rear - 1 + capacity) % capacity];
    }

    ~Queue() {
        delete data;
    }

};

#endif // QUEUE_H_INCLUDED
