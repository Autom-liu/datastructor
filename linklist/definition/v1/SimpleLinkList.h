#ifndef SIMPLELINKLIST_H_INCLUDED
#define SIMPLELINKLIST_H_INCLUDED

#include "AbstractLinkList.h"

template <typename E>
class SimpleLinkList : public AbstractLinkList<E> {
protected:
    LinkNode<E>* head;

    int size;

    LinkNode<E>* getNode(int index) {
        if(index < 0 || index >= size) {
            throw IndexOutOfBoundException("" + index);
        }
        LinkNode<E>* current = head;
        for(int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    void appendNode(LinkNode<E>* prevNode, LinkNode<E>* nextNode) {
        nextNode->next = prevNode->next;
        prevNode->next = nextNode;
    }

    void removeNode(LinkNode<E>* prevNode, LinkNode<E>* targetNode) {
        prevNode->next = targetNode->next;
        targetNode->next = NULL;
        delete targetNode;
    }

public:

    SimpleLinkList() {
        this->head = NULL;
        this->size = 0;
    }

    virtual E get(int i) {
        LinkNode<E>* node = this->getNode(i);
        return node->data;
    }

    virtual void addFirst(E data) {
        this->add(0, data);
    }

    virtual void addLast(E data) {
        this->add(this->size, data);
    }

    virtual void add(int i, E data) {
        if(i == 0) {
            head = new LinkNode<E>(data, head);
        } else {
            LinkNode<E>* prev = getNode(i - 1);
            prev->next = new LinkNode<E>(data, prev->next);
        }
        this->size++;
    }

    virtual E remove(int index) {
        if(index < 0 || index >= size) {
            throw IndexOutOfBoundException("" + index);
        }
        E ret = head->data;
        if(index == 0) {
            LinkNode<E>* nextHead = head->next;
            head->next = NULL;
            delete head;
            head = nextHead;
        } else {
            LinkNode<E>* prev = getNode(index - 1);
            LinkNode<E>* target = prev->next;
            ret = target->data;
            removeNode(prev, target);
        }
        this->size--;
        return ret;
    }

    virtual E removeFirst() {
        return this->remove(0);
    }

    virtual E removeLast() {
        return this->remove(size - 1);
    }

    virtual void set(int i, E data) {
        LinkNode<E>* current = getNode(i);
        current->data = data;
    }

    virtual int getSize() {
        return this->size;
    }

    typename AbstractLinkList<E>::iterator* newIterator() {
        return new typename AbstractLinkList<E>::iterator(this->head);
    }

    virtual ~SimpleLinkList() {
    }

};

#endif // SIMPLELINKLIST_H_INCLUDED
