#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef struct LinkNode {
    int data;
    struct LinkNode* next;
}LinkNode;

typedef struct LinkList {
    struct LinkNode* head;
}LinkList;

/**
* create a linkNode
**/
LinkNode* createNode(int data);

/**
* create an initial linkList
**/
LinkList* createByArr(int* arr, int start, int end);

/**
*  create an initial linkList implements by recursive
**/
LinkNode* _createByArr(int* arr, int start, int end);

/**
*   reverse the list
**/
LinkList* reverseList(LinkList* list);

/**
*   reverse the list implements by recursive
**/
LinkNode* _reverseList(LinkNode* node, LinkList* list);

/**
*   get element by index
**/
LinkNode* get(LinkList* list, int index);

/**
*   insert an element to the List
**/
int insert(LinkList* list, LinkNode* data, int index);

/**
* insert an element to the List before
**/
int insertAfter(LinkNode* before, LinkNode* data);

/**
*   remove and return (not free and not set next NULL)
**/
LinkNode* removeList(LinkList* list, int index);

#endif // LINKLIST_H_INCLUDED
