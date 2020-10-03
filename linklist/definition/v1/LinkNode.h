#ifndef LINKNODE_H_INCLUDED
#define LINKNODE_H_INCLUDED

typedef std::string string;

class IndexOutOfBoundException {
private:
    string msg;
public:
    IndexOutOfBoundException(string msg) : msg(msg) {}
};

template <typename E>
class LinkNode {
public:
    E data;
    LinkNode<E>* next;

    LinkNode(E data, LinkNode<E>* next = NULL) {
        this->data = data;
        this->next = next;
    }
    LinkNode(LinkNode<E>* next = NULL) {
        this->next = next;
    }

};


#endif // LINKNODE_H_INCLUDED
