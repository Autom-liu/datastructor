#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Array.h"
#include "Queue.h"

template <typename T>
class TreeNode {
public:
    T value;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(T value) {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
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

    template <typename T>
    void levelOrder(TreeNode<T>* node, Array<TreeNode<T>*>* result) {
        if(node == NULL) {
            return;
        }
        Queue<TreeNode<T>*>* qq = new Queue<TreeNode<T>*>();
        qq->push(node);
        while(!qq->isEmpty()) {
            TreeNode<T>* head = qq->pop();
            if(head != NULL) {
                result->add(head);
                qq->push(head->left);
                qq->push(head->right);
            }
        }
        delete qq;
    }

    template <typename T>
    void levelOrder(TreeNode<T>* node, Array<T>* result) {
        Queue<TreeNode<T>*>* qq = new Queue<TreeNode<T>*>();
        qq->push(node);
        while(!qq->isEmpty()) {
            TreeNode<T>* head = qq->pop();
            if(head != NULL) {
                result->add(head->value);
                qq->push(head->left);
                qq->push(head->right);
            }
        }
        delete qq;
    }

};

template <typename T>
class AvlTree {
private:
    TreeNode<T>* root;

    int size;

    int getHeight(TreeNode<T>* node) {
        if(node == NULL) {
            return 0;
        }
        return node->height;
    }

    int calHeight(TreeNode<T>* node) {
        if(node == NULL) {
            return 0;
        }
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(TreeNode<T>* node) {
        if(node == NULL) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    /**
    *           root
    *       x            y
    *   T1      T2    T3    T4
    *
    *               x                           y
    *             /   \                       /    \
    *           y       T4                  z       x
    *         /   \             LL         /  \    /  \
    *       z      T3         ------->   T1    T2 T3  T4
    *     /   \
    *   T1     T2
    *
    *      x                                 y
    *    /   \                             /    \
    *  T4      y                         x       z
    *       /   \            RR         /  \    /  \
    *      T3    z        ------->   T4    T3 T1    T2
    *          /   \
    *       T1     T2
    *
    *
    *      x                                 z
    *    /   \                             /    \
    *  T4      y                         x       y
    *       /   \            RL         /  \    /  \
    *      z     T3        ------->   T4    T1 T2    T3
    *    /   \
    *  T1     T2
    *
    *
    *               x                           z
    *             /   \                       /    \
    *           y       T4                  y       x
    *         /   \             LR         /  \    /  \
    *       T3     z         ------->   T3    T1 T2   T4
    *            /   \
    *          T1     T2
    *
    **/
    TreeNode<T>* reBalance(TreeNode<T>* root, TreeNode<T>* x, TreeNode<T>* y, TreeNode<T>* t1, TreeNode<T>* t2, TreeNode<T>* t3, TreeNode<T>* t4) {

        root->left = x;
        root->right = y;
        x->left = t1;
        x->right = t2;

        y->left = t3;
        y->right = t4;

        x->height = calHeight(x);
        y->height = calHeight(y);
        root->height = calHeight(root);

        return root;
    }

    /**
    *   调节以node为根的子树平衡性
    *   返回调整后的根
    **/
    TreeNode<T>* reBalance(TreeNode<T>* node) {
        node->height = calHeight(node);
        int factor = getBalanceFactor(node);
        if(factor > 1 && getBalanceFactor(node->left) >= 0) {  /// LL
            return reBalance(node->left, node->left->left, node, node->left->left->left, node->left->left->right, node->left->right, node->right);
        } else if(factor < -1 && getBalanceFactor(node->right) <= 0) { /// RR
            return reBalance(node->right, node, node->right->right, node->left, node->right->left, node->right->right->left, node->right->right->right);
        } else if(factor > 1 && getBalanceFactor(node->left) < 0) { /// LR
            return reBalance(node->left->right, node->left, node, node->left->left, node->left->right->left, node->left->right->right, node->right);
        } else if(factor < -1 && getBalanceFactor(node->right) > 0) { /// RL
            return reBalance(node->right->left, node, node->right, node->left, node->right->left->left, node->right->left->right, node->right->right);
        }

        return node;
    }

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
            return node;
        }
        return reBalance(node);
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
            TreeNode<T>* ret = removeMax(node->right);
            node = reBalance(node);
            return ret;
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
            TreeNode<T>* ret = removeMin(node->left);
            node = reBalance(node);
            return ret;
        } else {
            TreeNode<T>* ret = node;
            node = node->right;
            return ret;
        }
    }

    /**
    *   删除以node为根的树元素value
    *   返回新的根
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
            node = replaced;
        } else if(node->value > value) {
            node->left = removeNode(node->left, value);
        } else {
            node->right = removeNode(node->right, value);
        }
        if(node != NULL) {
            return reBalance(node);
        } else {
            return NULL;
        }
    }

public:
    AvlTree() {
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

    Array<T>* levelOrder() {
        Array<T>* result = new Array<T>();
        TravelHelper::levelOrder(root, result);
        return result;
    }

    ~AvlTree() {
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
