#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Array.h"

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
    bool hasOnlyLeft() {
        return left != NULL && right == NULL;
    }
    bool hasOnlyRight() {
        return right != NULL && left == NULL;
    }
    bool isFull() {
        return left != NULL && right != NULL;
    }
};

namespace TravelHelper {

    template <typename T>
    void preOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        if(node == NULL) {
            return;
        }
        result->add(node);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    template <typename T>
    void preOrder(TreeNode<T>* node, Array<T>* result) {
        if(node == NULL) {
            return;
        }
        result->add(node->value);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    template <typename T>
    void midOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        if(node == NULL) {
            return;
        }
        midOrder(node->left, result);
        result->add(node);
        midOrder(node->right, result);
    }

    template <typename T>
    void midOrder(TreeNode<T>* node, Array<T>* result) {
        if(node == NULL) {
            return;
        }
        midOrder(node->left, result);
        result->add(node->value);
        midOrder(node->right, result);
    }

    template <typename T>
    void postOrder(TreeNode<T>* node, Array<TreeNode<T>* >* result) {
        if(node == NULL) {
            return;
        }
        postOrder(node->left, result);
        postOrder(node->right, result);
        result->add(node);
    }

    template <typename T>
    void postOrder(TreeNode<T>* node, Array<T>* result) {
        if(node == NULL) {
            return;
        }
        postOrder(node->left, result);
        postOrder(node->right, result);
        result->add(node->value);
    }

};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    int size;

    /**
    *   在以node为节点的树中添加一个元素value
    *   返回该树的根
    *   该BST不支持重复元素（集合）
    **/
    TreeNode<T>* add(TreeNode<T>* node, T value) {
        if(node == NULL) {
            this->size++;
            return new TreeNode<T>(value);
        }
        if(node->value > value) {
            node->left = add(node->left, value);
        } else if (node->value < value) {
            node->right = add(node->right, value);
        } else {
            node->value = value;
        }
        return node;
    }

    /**
    *   在以node为节点的树中查找一个元素value
    *   返回结果
    **/
    TreeNode<T>* contains(TreeNode<T>* node, T value) {
        if(node == NULL) {
            return NULL;
        } else if(node->value == value) {
            return node;
        } else if (node->value > value) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }

    /**
    * 寻找以node为根的树中最大的节点
    **/
    TreeNode<T>* findMax(TreeNode<T>* node) {
        if(node->hasRight()) {
            return findMax(node->right);
        }
        return node;
    }

    /**
    * 寻找以node为根的树中最小的节点
    **/
    TreeNode<T>* findMin(TreeNode<T>* node) {
        if(node->hasLeft()) {
            return findMin(node->left);
        }
        return node;
    }

    /**
    *   删除以node为根的最大元素，其中参数值是引用，表示该根会被替换
    *   返回该最大元素
    **/
    TreeNode<T>* removeMax(TreeNode<T>*& node) {
        if(node->hasRight()) {
            return removeMax(node->right);
        } else {
            TreeNode<T>* ret = node;
            node = node->left;
            return ret;
        }
    }

    /**
    *   删除以node为根的最小元素，其中参数值是引用，表示该根会被替换
    *   返回该最小元素
    **/
    TreeNode<T>* removeMin(TreeNode<T>*& node) {
        if(node->hasLeft()) {
            return removeMin(node->left);
        } else {
            TreeNode<T>* ret = node;
            node = node->right;
            return ret;
        }
    }

    /**
    *   删除以node为根的树元素value
    **/
    TreeNode<T>* removeNode(TreeNode<T>* node, T value) {
        if(node == NULL) {
            return NULL;
        }
        if(node->value == value) {
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

            size--;
            delete node;
            return replaced;
        } else if(node->value > value) {
            node->left = removeNode(node->left, value);
        } else {
            node->right = removeNode(node->right, value);
        }
        return node;
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
        root = add(root, value);
    }

    bool contains(T value) {
        return contains(root, value) != NULL;
    }

    void remove(T value) {
        root = removeNode(root, value);
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
