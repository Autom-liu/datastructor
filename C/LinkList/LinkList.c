#include <stdlib.h>
#include "LinkList.h"

/**
* create a empty linkList
**/
LinkNode* createNode(int data) {
    LinkNode* result = malloc(sizeof(LinkNode));
    result->data = data;
    result->next = NULL;
    return result;
}

/**
* create an initial linkList
**/
LinkList* createByArr(int* arr, int start, int end) {
    LinkList* result = malloc(sizeof(LinkList*));
    /// LinkNode* head = _createByArr(arr, start, end);
    /// result->head = head;
    LinkNode* next = NULL;
    for(end = end - 1; end >= start; end --) {
        LinkNode* current = createNode(arr[end]);
        current->next = next;
        next = current;
    }
    result->head = next;
    return result;
}

LinkNode* _createByArr(int* arr, int start, int end) {
    if (start >= end) {
        return NULL;
    }
    LinkNode* result = createNode(arr[start]);
    result->next = _createByArr(arr, start + 1, end);
    return result;
}

LinkNode* get(LinkList* list, int index) {
    int i = 0, ret = (list != NULL && index >= 0);
    LinkNode* current = NULL;
    if (ret) {
        current = list->head;
        for(i = 0; i < index && current != NULL; i++) {
            current = current->next;
        }
    }
    return current;
}

/**
*   reverse the list
**/
LinkList* reverseList(LinkList* list) {
    /// _reverseList(list->head, list);
    /// return list;
    /// 删除该节点 -> 头插该节点 -> 指针前移
    LinkNode* current = list->head;
    LinkNode* prev = NULL;
    while(current != NULL) {
        if(prev != NULL) {
            prev->next = current->next;
            insert(list, current, 0);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return list;
}

/**
*   reverse the list implements by recursive
*   return the last element of the list and confirm not NULL
**/
LinkNode* _reverseList(LinkNode* node, LinkList* list) {
    if(node->next == NULL) {
        list->head = node;
        return node;
    }
    LinkNode* lastNode = _reverseList(node->next, list);
    lastNode->next = node;
    node->next = NULL;
    return node;
}

/**
*   insert an element to the List
**/
int insert(LinkList* list, LinkNode* data, int index) {
    int ret = 1;
    if (index == 0) {
        data->next = list->head;
        list->head = data;
    } else {
        LinkNode* current = get(list, index - 1);
        ret = ret && insertAfter(current, data);
    }
    return ret;
}

/**
* insert an element to after the before node
**/
int insertAfter(LinkNode* before, LinkNode* data) {
    int ret = (before != NULL && data != NULL);
    if (ret) {
        data->next = before->next;
        before->next = data;
    }
    return ret;
}

LinkNode* removeList(LinkList* list, int index) {
    LinkNode* target = NULL;
    if (index == 0) {
        target = list->head;
        list->head = list->head->next;
    } else {
        LinkNode* prev = get(list, index - 1);
        LinkNode* target = prev->next;
        prev->next = target->next;
    }
    return target;
}
