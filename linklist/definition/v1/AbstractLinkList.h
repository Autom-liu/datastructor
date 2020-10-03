#ifndef ABSTRACTLINKNODE_H_INCLUDED
#define ABSTRACTLINKNODE_H_INCLUDED
#include "LinkNode.h"



template <typename E>
class AbstractLinkList {
public:

    virtual E get(int i) = 0;

    virtual void addFirst(E data) = 0;

    virtual void addLast(E data) = 0;

    virtual void add(int i, E data) = 0;

    virtual E remove(int i) = 0;

    virtual E removeFirst() = 0;

    virtual E removeLast() = 0;

    virtual void set(int i, E data) = 0;

    virtual int getSize() = 0;

    class iterator {

        protected:
        LinkNode<E>* head;

        LinkNode<E>* current;

        public:

        iterator(LinkNode<E>* current) {
            this->head = current;
            this->current = current;
        }

        bool hasNext() {
            return current != NULL;
        }

        E next() {
            E data = current->data;
            current = current->next;
            return data;
        }

        void reset() {
            this->current = this->head;
        }
    };

    virtual AbstractLinkList<E>::iterator* newIterator() = 0;

    virtual ~AbstractLinkList() {
    }

};


#endif // ABSTRACTLINKNODE_H_INCLUDED
