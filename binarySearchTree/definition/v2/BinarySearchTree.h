#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Stack.h"

template <typename T>
class TreeNode {
public:
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T value) {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
    bool isLeaf() {
        return left == NULL && right == NULL;
    }
    bool hasLeft() {
        return left != NULL;
    }
    bool hasRight() {
        return right != NULL;
    }
    bool isFull() {
        return left != NULL && right != NULL;
    }
};

namespace TravelHelper {

    template <typename T>
    void preOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        while(current != NULL && !st->isEmpty()) {
            result->add(current);
            if(current->hasRight()) {
                st->push(current->right);
            }
            if(current->hasLeft()) {
                st->push(current->left);
            }
            current = st->pop();
        }
        delete st;
    }

    template <typename T>
    void preOrder(TreeNode<T>* node, Array<T>* result) {
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        st->push(current);
        while(!st->isEmpty()) {
            current = st->pop();
            if(current != NULL) {
                result->add(current->value);
                st->push(current->right);
                st->push(current->left);
            }
        }
        delete st;
    }

    template <typename T>
    void midOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        while(current != NULL || !st->isEmpty()) {
            if(current != NULL) {
                current = current->left;
                st->push(current);
            } else {
                current = st->pop();
                result->add(current);
                current = current->right;
            }
        }
        delete st;
    }

    template <typename T>
    void midOrder(TreeNode<T>* node, Array<T>* result) {
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        while(current != NULL || !st->isEmpty()) {
            if(current != NULL) {
                st->push(current);
                current = current->left;
            } else {
                current = st->pop();
                result->add(current->value);
                current = current->right;
            }
        }
        delete st;
    }

    template <typename T>
    void postOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        TreeNode<T>* current = node;
        TreeNode<T>* lastVisit = NULL; /// 记录上一个被访问的节点
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        while(current != NULL || !st->isEmpty()) {
            if(current != NULL) {
                st->push(current);
                current = current->left;
            } else {
                current = st->top(); /// 只是查看栈顶元素，不做访问
                if(current->hasRight() && current->right != lastVisit) {
                    current = current->right;
                } else {
                    current = st->pop();
                    result->add(current);
                    lastVisit = current;
                    current = NULL; /// 当前节点已经访问完成，下一轮应该再重栈里取了
                }
            }
        }
        delete st;
    }

    template <typename T>
    void postOrder(TreeNode<T>* node, Array<T>* result) {
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        Stack<TreeNode<T>*>* res = new Stack<TreeNode<T>*>();
        st->push(current);
        while(!st->isEmpty()) {
            current = st->pop();
            if(current != NULL) {
                res->push(current);
                st->push(current->left);
                st->push(current->right);
            }
        }
        while(!res->isEmpty()) {
            result->add(res->pop()->value);
        }

        delete res;
        delete st;

    }

};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    int size;

    /**
    *   删除以node为根的树中最小值，参数为引用类型，表示该根能被改变
    *   返回最小元素
    **/
    TreeNode<T>* removeMin(TreeNode<T>*& node) {
        TreeNode<T>* current = node;
        TreeNode<T>* prev = NULL;
        while(current != NULL && current->hasLeft()) {
            prev = current;
            current = current->left;
        }

        if(prev != NULL) {
            prev->left = current->right;
        } else {
            node = node->right;
        }
        current->right = NULL;
        return current;
    }

    /**
    *   删除以node为根的树中最大值，参数为引用类型，表示该根能被改变
    *   返回最大元素
    **/
    TreeNode<T>* removeMax(TreeNode<T>*& node) {
        TreeNode<T>* current = node;
        TreeNode<T>* prev = NULL;
        while(current != NULL && current->hasRight()) {
            prev = current;
            current = current->right;
        }

        if(prev != NULL) {
            prev->right = current->left;
        } else {
            node = node->left;
        }
        current->left = NULL;
        return current;
    }

    void removeNode(TreeNode<T>*& node) {
        TreeNode<T>* replaced = NULL;
        if(node->hasLeft()) {
            replaced = removeMax(node->left);
            replaced->left = node->left;
            replaced->right = node->right;
        } else if(node->hasRight()) {
            replaced = removeMin(node->right);
            replaced->left = node->left;
            replaced->right = node->right;
        } else {

        }
        delete node;
        node = replaced;
        size--;
    }

public:
    BinarySearchTree() {
        this->root = NULL;
        this->size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    void add(T value) {
        /// 使用二级指针可以减少对待插入位置的源头判断，这算是指针支持语言C和C++特有的方式
        TreeNode<T>** addr = &root;
        TreeNode<T>* current = *addr;

        while(current != NULL) {
            if(current->value > value) {
                addr = &(current->left);
            } else if(current->value < value) {
                addr = &(current->right);
            } else {
                current->value = value;
                return;
            }
            current = *addr;
        }
        *addr = new TreeNode<T>(value);
        size++;
    }

    bool contains(T value) {
        TreeNode<T>* current = root;
        while(current != NULL) {
            if(current->value == value) {
                return true;
            } else if(current->value > value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void remove(T value) {
        TreeNode<T>** addr = &root;
        TreeNode<T>* current = * addr;
        while(current != NULL) {
            if(current->value > value) {
                addr = &(current->left);
            } else if(current->value < value) {
                addr = &(current->right);
            } else {
                return removeNode(*addr);
            }
            current = *addr;
        }
    }

    Array<T>* preOrder() {
        Array<T>* result = new Array<T>();
        TravelHelper::preOrder(this->root, result);
        return result;
    }

    Array<T>* midOrder() {
        Array<T>* result = new Array<T>();
        TravelHelper::midOrder(this->root, result);
        return result;
    }

    Array<T>* postOrder() {
        Array<T>* result = new Array<T>();
        TravelHelper::postOrder(this->root, result);
        return result;
    }

    ~BinarySearchTree() {
        Array<TreeNode<T>*>* result = new Array<TreeNode<T>*>();
        TravelHelper::postOrder(root, result);
        typename Array<TreeNode<T>*>::iterator* it = result->newIterator();
        while(it->hasNext()) {
            delete it->next();
        }
        delete it;
        delete result;
    }

};

#endif // TREENODE_H_INCLUDED
