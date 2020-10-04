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
class Queue {
private:

    T* data;

    int rear;

    int front;

    int capacity;

    void resize(int newCapacity) {
        int oldCapacity = this->capacity;
        T* newData = new T[newCapacity];
        for(int i = front, j = 0; j < oldCapacity; i=(i+1)%capacity) {
            newData[j++] = this->data[i];
        }
        delete this->data;
        this->data = newData;
        this->front = 0;
        this->rear = oldCapacity - 1;
        this->capacity = newCapacity;
    }

public:

    Queue(int capacity = 16) {
        this->data = new T[capacity];
        this->rear = -1;
        this->front = -1;
        this->capacity = capacity;
    }

    int getSize() {
        if(isEmpty()) {
            return 0;
        }
        return (rear - front + capacity) % capacity + 1;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return rear == -1;
    }

    bool isFull() {
        return !isEmpty() && ((rear + 1) % capacity == front);
    }

    void push(T ele) {
        if(isFull()) {
            resize(capacity * 2);
        }
        if(isEmpty()) {
            rear = front = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        data[rear] = ele;
    }

    T pop() {
        if(isEmpty()) {
            throw IndexOutOfBoundException(string("front=" + front).append(" rear" + rear));
        }
        T res = data[front];
        if(front == rear) {
            rear = front = -1;
        } else {
            front = (front + 1) % capacity;
        }
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
        return data[rear];
    }

    ~Queue() {
        delete data;
    }

};

#endif // QUEUE_H_INCLUDED
