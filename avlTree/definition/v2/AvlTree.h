#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Stack.h"
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
        TreeNode<T>* current = node;
        Stack<TreeNode<T>*>* st = new Stack<TreeNode<T>*>();
        st->push(current);
        while(current != NULL || !st->isEmpty()) {
            current = st->pop();
            if(current != NULL) {
                result->add(current);
                st->push(current->right);
                st->push(current->left);
            }
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
                current = st->top(); /// 第一次，只是查看栈顶元素，不做访问
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

    void restoreNode(Stack<TreeNode<T>**>* addrStack, TreeNode<T>** node) {
        TreeNode<T>* current = *node;
        if(current->hasLeft()) {
            addrStack->push(&(current->left));
            current = current->left;
            while(current != NULL && current->hasRight()) {
                addrStack->push(&(current->right));
                current = current->right;
            }
        } else if (current->hasRight()) {
            addrStack->push(&(current->right));
            current = current->right;
            while(current != NULL && current->hasLeft()) {
                addrStack->push(&(current->left));
                current = current->left;
            }
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
        TreeNode<T>** addr = &root;
        TreeNode<T>* current = *addr;
        Stack<TreeNode<T>**>* addrStack = new Stack<TreeNode<T>**>();

        while(current != NULL) {
            if(current->value > value) {
                addr = &(current->left);
            } else if(current->value < value) {
                addr = &(current->right);
            } else {
                current->value = value;
                return;
            }
            addrStack->push(addr);
            current = *addr;
        }
        *addr = new TreeNode<T>(value);
        size++;
        while(!addrStack->isEmpty()) {
            TreeNode<T>** node = addrStack->pop();
            *node = reBalance(*node);
        }
        delete addrStack;
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
        Stack<TreeNode<T>**>* addrStack = new Stack<TreeNode<T>**>();
        while(current != NULL) {
            addrStack->push(addr);
            if(current->value > value) {
                addr = &(current->left);
            } else if(current->value < value) {
                addr = &(current->right);
            } else {
                removeNode(*addr);
                break;
            }
            current = *addr;
        }

        if(!addrStack->isEmpty()) {
            TreeNode<T>** node = addrStack->top();
            if(*node != NULL) {
                restoreNode(addrStack, node);
            }
        }

        while(!addrStack->isEmpty()) {
            TreeNode<T>** node = addrStack->pop();
            if(*node != NULL) {
                *node = reBalance(*node);
            }
        }

        delete addrStack;
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
