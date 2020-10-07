#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Stack.h"
#include "Queue.h"

const bool BLACK = true;
const bool RED = false;

const bool LEFT = true;
const bool RIGHT = false;

template <typename T>
class TreeNode {
public:
    T value;
    TreeNode* left;
    TreeNode* right;
    bool color;
    TreeNode(T value) {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->color = RED;
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
class RBTree {
private:
    TreeNode<T>* root;

    int size;

    void filpColors(TreeNode<T>* node, bool color) {
        if(node == NULL) {
            return;
        }
        node->color = color;
        if(node->hasLeft()) {
            node->left->color = !color;
        }
        if(node->hasRight()) {
            node->right->color = !color;
        }
    }

    bool getColor(TreeNode<T>* node) {
        if(node == NULL) {
            return BLACK;
        }
        return node->color;
    }

    bool hasRedChild(TreeNode<T>* node) {
        if(node == NULL) {
            return false;
        }
        return getColor(node->left) == RED || getColor(node->right) == RED;
    }

    bool allRedChild(TreeNode<T>* node) {
        if(node == NULL) {
            return false;
        }
        return getColor(node->left) == RED && getColor(node->right) == RED;
    }

    /**
    *           root
    *       x            y
    *   T1      T2    T3    T4
    *
    *               xB                          yR
    *             /   \                       /    \
    *           yR       T4                 zR     xB
    *         /   \             LL         /  \    /  \
    *       zR      T3         ------->   T1    T2 T3  T4
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
        if(x != NULL) {
            x->left = t1;
            x->right = t2;
        }

        if(y != NULL) {
            y->left = t3;
            y->right = t4;
        }
        return root;
    }

    TreeNode<T>* nullableNode(TreeNode<T>* node, bool left) {
        if(node == NULL) {
            return NULL;
        }
        return left ? node->left : node->right;
    }

    TreeNode<T>* insertBalance(TreeNode<T>* node, TreeNode<T>* nextNode) {
        /// 上报的颜色为黑，或当前节点为红，不用调整
        if(getColor(nextNode) == BLACK || getColor(node) == RED) {
            return node;
        }
        /// 上报节点的孩子颜色都不是红，不用调整
        if(!hasRedChild(nextNode)) {
            return node;
        }
        TreeNode<T>* retNode = node;
        if(allRedChild(node)) {  ///颜色反转
            filpColors(node, RED);
        } else if (node->left == nextNode && getColor(nextNode->left) == RED) {  //LL
            retNode = reBalance(node->left, node->left->left, node, node->left->left->left, node->left->left->right, node->left->right, node->right);
            filpColors(retNode, BLACK);
        } else if (node->right == nextNode && getColor(nextNode->right) == RED) { //RR
            retNode = reBalance(node->right, node, node->right->right, node->left, node->right->left, node->right->right->left, node->right->right->right);
            filpColors(retNode, BLACK);
        } else if (node->right == nextNode && getColor(nextNode->left) == RED) {  // RL
            retNode = reBalance(node->right->left, node, node->right, node->left, node->right->left->left, node->right->left->right, node->right->right);
            filpColors(retNode, BLACK);
        } else if (node->left == nextNode && getColor(nextNode->right) == RED) {  //LR
            retNode = reBalance(node->left->right, node->left, node, node->left->left, node->left->right->left, node->left->right->right, node->right);
            filpColors(retNode, BLACK);
        }
        return retNode;
    }

    TreeNode<T>* deleteReBalance(TreeNode<T>* parent, TreeNode<T>* brother) {
        if(brother == NULL) {
            return parent;
        }
        ///兄弟为红色，单次旋转变色后，转为兄弟黑色，父亲红色处理 （兄弟是红色，兄弟一定不为空，父亲一定是黑色）
        if(getColor(brother) == RED && parent->left == brother) {  //LL
            TreeNode<T>* newBrother = brother->right;
            TreeNode<T>* retNode = reBalance(brother, brother->left, parent, nullableNode(brother->left, LEFT), nullableNode(brother->left, RIGHT), brother->right, parent->right);
            brother->color = BLACK;
            parent->color = RED;
            retNode->right = deleteReBalance(parent, newBrother);
            return retNode;
        } else if (getColor(brother) == RED && parent->right == brother) { //RR
            TreeNode<T>* newBrother = brother->left;
            TreeNode<T>* retNode = reBalance(brother, parent, brother->right, parent->left, brother->left, nullableNode(brother->right, LEFT), nullableNode(brother->right, RIGHT));
            brother->color = BLACK;
            parent->color = RED;
            retNode->left = deleteReBalance(parent, newBrother);
            return retNode;
        }
        /// 兄弟为黑，父亲也为黑，兄的两个孩子均为黑（删除黑叶子结点时，这种情况兄弟存在且两个孩子都为空）转为兄红色处理
        else if (getColor(brother) == BLACK && getColor(parent) == BLACK && getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
            brother->color = RED;
            return deleteReBalance(parent, brother);
        }
        /// 兄弟为黑，兄的两个孩子均为黑，父亲为红，变色平衡
        else if (getColor(brother) == BLACK && getColor(parent) == RED && getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
            parent->color = BLACK;
            brother->color = RED;
            return parent;
        }
        /// 兄弟为黑，与兄同边的孩子为红，（此时该红孩子一定存在）单旋变色平衡
        else if (getColor(brother) == BLACK && parent->left == brother && getColor(brother->left) == RED) { // LL
            TreeNode<T>* retNode = reBalance(brother, brother->left, parent, nullableNode(brother->left, LEFT), nullableNode(brother->left, RIGHT), brother->right, parent->right);
            retNode->color = getColor(parent);
            retNode->left->color = BLACK;
            retNode->right->color = BLACK;
            return retNode;
        } else if (getColor(brother) == BLACK && parent->right == brother && getColor(brother->right) == RED) { // RR
            TreeNode<T>* retNode = reBalance(brother, parent, brother->right, parent->left, brother->left, nullableNode(brother->right, LEFT), nullableNode(brother->right, RIGHT));
            retNode->color = getColor(parent);
            retNode->left->color = BLACK;
            retNode->right->color = BLACK;
            return retNode;
        }
        /// 兄弟为黑，与兄不同边的孩子为红，（此时该红孩子一定存在），另一边为黑色。双旋变色平衡
        else if (getColor(brother) == BLACK && parent->left == brother && getColor(brother->right) == RED && getColor(brother->left) == BLACK) { // LR
            TreeNode<T>* retNode = reBalance(brother->right, brother, parent, brother->left, brother->right->left, brother->right->right, parent->right);
            retNode->color = getColor(parent);
            retNode->left->color = BLACK;
            retNode->right->color = BLACK;
            return retNode;
        } else if (getColor(brother) == BLACK && parent->right == brother && getColor(brother->left) == RED && getColor(brother->right) == BLACK) { // RL
            TreeNode<T>* retNode = reBalance(brother->left, parent, brother, parent->left, brother->left->left, brother->left->right, brother->right);
            retNode->color = getColor(parent);
            retNode->left->color = BLACK;
            retNode->right->color = BLACK;
            return retNode;
        }
        return parent;
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

public:
    RBTree() {
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
            addrStack->push(addr);
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
        while(!addrStack->isEmpty()) {
            TreeNode<T>** parentNode = addrStack->pop();
            *parentNode = insertBalance(*parentNode, *addr);
            addr = parentNode;
        }
        if(root != NULL) {
            root->color = BLACK;  /// 始终保持根结点为黑色
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

    Array<T>* levelOrder() {
        Array<T>* result = new Array<T>();
        TravelHelper::levelOrder(root, result);
        return result;
    }

    ~RBTree() {
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
