#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Array.h"

const bool BLACK = true;
const bool RED = false;

const bool LEFT = true;
const bool RIGHT = false;

template <typename K, typename V>
class TreeNode {
public:
    K key;
    V value;
    TreeNode* left;
    TreeNode* right;
    bool color;
    TreeNode(K key, V value) {
        this->key = key;
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
    template <typename K, typename V>
    void postOrder(TreeNode<K, V>* node, Array<TreeNode<K, V>* >* result) {
        if(node == NULL) {
            return;
        }
        postOrder(node->left, result);
        postOrder(node->right, result);
        result->add(node);
    }
};

template <typename K, typename V>
class TreeMap {
private:
    TreeNode<K, V>* root;

    int size;

    /**
    *   在以node为节点的树中添加一个元素key
    *   返回该树的根
    *   该BST不支持重复元素（集合）
    **/
    TreeNode<K, V>* add(TreeNode<K, V>* node, K key, V value) {
        if(node == NULL) {
            this->size++;
            return new TreeNode<K, V>(key, value);
        }
        TreeNode<K, V>* nextNode = NULL;
        if(node->key > key) {
            nextNode = add(node->left, key, value);
            node->left = nextNode;
        } else if (node->key < key) {
            nextNode = add(node->right, key, value);
            node->right = nextNode;
        } else {
            node->value = value;
            return node;
        }
        return insertBalance(node, nextNode);
    }

    /**
    *   在以node为节点的树中查找一个元素key
    *   返回结果
    **/
    TreeNode<K, V>* contains(TreeNode<K, V>* node, K key) {
        if(node == NULL) {
            return NULL;
        } else if(node->key == key) {
            return node;
        } else if (node->key > key) {
            return contains(node->left, key);
        } else {
            return contains(node->right, key);
        }
    }

    /**
    * 寻找以node为根的树中最大的节点
    **/
    TreeNode<K, V>* findMax(TreeNode<K, V>* node) {
        if(node->hasRight()) {
            return findMax(node->right);
        }
        return node;
    }

    /**
    * 寻找以node为根的树中最小的节点
    **/
    TreeNode<K, V>* findMin(TreeNode<K, V>* node) {
        if(node->hasLeft()) {
            return findMin(node->left);
        }
        return node;
    }

    /**
    *   删除以node为根的树元素key
    *   告知是否需要重新调平衡
    **/
    bool removeNode(TreeNode<K, V>*& node, K key, V value) {
        if(node == NULL) {
            return false;
        }
        TreeNode<K, V>* brother = NULL;
        bool isNeedReBalance = false;
        if(node->key == key) {
            if(node->isFull()) {
                TreeNode<K, V>* maxNode = findMax(node->left);
                K maxkey = maxNode->key;
                V maxValue = maxNode->value;
                isNeedReBalance = removeNode(node->left, maxkey);
                brother = node->right;
                node->key = maxkey; /// 值替换
                node->value = maxValue;
            } else {
                isNeedReBalance = isNeedReBalanceInDeletion(node);
                TreeNode<K, V>* delNode = node;
                node = node->hasLeft() ? node->left : node->right;
                delete delNode;
                size--;
                return isNeedReBalance;
            }
        } else if(node->key > key) {
            isNeedReBalance = removeNode(node->left, key);
            brother = node->right;
        } else {
            isNeedReBalance = removeNode(node->right, key);
            brother = node->left;
        }

        return isNeedReBalance && deleteReBalance(node, brother);
    }

    bool isNeedReBalanceInDeletion(TreeNode<K, V>* delNode) {
        if(delNode == NULL) {
            return false;
        }

        if(delNode->hasLeft()) {
            delNode->left->color = BLACK;
        } else if (delNode->hasRight()) {
            delNode->right->color = BLACK;
        }

        return getColor(delNode) == BLACK && delNode->isLeaf();
    }


    void filpColors(TreeNode<K, V>* node, bool color) {
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

    bool getColor(TreeNode<K, V>* node) {
        if(node == NULL) {
            return BLACK;
        }
        return node->color;
    }

    bool hasRedChild(TreeNode<K, V>* node) {
        if(node == NULL) {
            return false;
        }
        return getColor(node->left) == RED || getColor(node->right) == RED;
    }

    bool allRedChild(TreeNode<K, V>* node) {
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
    TreeNode<K, V>* reBalance(TreeNode<K, V>* root, TreeNode<K, V>* x, TreeNode<K, V>* y, TreeNode<K, V>* t1, TreeNode<K, V>* t2, TreeNode<K, V>* t3, TreeNode<K, V>* t4) {

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

    TreeNode<K, V>* nullableNode(TreeNode<K, V>* node, bool left) {
        if(node == NULL) {
            return NULL;
        }
        return left ? node->left : node->right;
    }

    TreeNode<K, V>* insertBalance(TreeNode<K, V>* node, TreeNode<K, V>* nextNode) {
        /// 上报的颜色为黑，或当前节点为红，不用调整
        if(getColor(nextNode) == BLACK || getColor(node) == RED) {
            return node;
        }
        /// 上报节点的孩子颜色都不是红，不用调整
        if(!hasRedChild(nextNode)) {
            return node;
        }
        TreeNode<K, V>* retNode = node;
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

    /**
    *   删除结点时调节以parent为根，brother为兄弟的子树颜色平衡
    *   返回是否需要继续上层平衡
    **/
    bool deleteReBalance(TreeNode<K, V>*& parent, TreeNode<K, V>* brother) {
        if(brother == NULL) {
            return false;
        }
        ///兄弟为红色，单次旋转变色后，转为兄弟黑色，父亲红色处理 （兄弟是红色，兄弟一定不为空，父亲一定是黑色）
        if(getColor(brother) == RED && parent->left == brother) {  //LL
            TreeNode<K, V>* newBrother = brother->right;
            parent = reBalance(brother, brother->left, parent, nullableNode(brother->left, LEFT), nullableNode(brother->left, RIGHT), brother->right, parent->right);
            parent->color = BLACK;
            parent->right->color = RED;
            return deleteReBalance(parent->right, newBrother);
        } else if (getColor(brother) == RED && parent->right == brother) { //RR
            TreeNode<K, V>* newBrother = brother->left;
            parent = reBalance(brother, parent, brother->right, parent->left, brother->left, nullableNode(brother->right, LEFT), nullableNode(brother->right, RIGHT));
            parent->color = BLACK;
            parent->left->color = RED;
            return deleteReBalance(parent->left, newBrother);
        }
        /// 兄弟为黑，父亲也为黑，兄的两个孩子均为黑（删除黑叶子结点时，这种情况兄弟存在且两个孩子都为空）转为兄红色处理
        else if (getColor(brother) == BLACK && getColor(parent) == BLACK && getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
            brother->color = RED;
            return true;    /// 此时需要告知向上重新调平衡
        }
        /// 兄弟为黑，兄的两个孩子均为黑，父亲为红，变色平衡
        else if (getColor(brother) == BLACK && getColor(parent) == RED && getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
            parent->color = BLACK;
            brother->color = RED;
            return false;
        }
        /// 兄弟为黑，与兄同边的孩子为红，（此时该红孩子一定存在）单旋变色平衡
        else if (getColor(brother) == BLACK && parent->left == brother && getColor(brother->left) == RED) { // LL
            bool oldColor = getColor(parent);
            parent = reBalance(brother, brother->left, parent, nullableNode(brother->left, LEFT), nullableNode(brother->left, RIGHT), brother->right, parent->right);
            parent->color = oldColor;
            parent->left->color = BLACK;
            parent->right->color = BLACK;
            return false;
        } else if (getColor(brother) == BLACK && parent->right == brother && getColor(brother->right) == RED) { // RR
            bool oldColor = getColor(parent);
            parent = reBalance(brother, parent, brother->right, parent->left, brother->left, nullableNode(brother->right, LEFT), nullableNode(brother->right, RIGHT));
            parent->color = oldColor;
            parent->left->color = BLACK;
            parent->right->color = BLACK;
            return false;
        }
        /// 兄弟为黑，与兄不同边的孩子为红，（此时该红孩子一定存在），另一边为黑色。双旋变色平衡
        else if (getColor(brother) == BLACK && parent->left == brother && getColor(brother->right) == RED && getColor(brother->left) == BLACK) { // LR
            parent = reBalance(brother->right, brother, parent, brother->left, brother->right->left, brother->right->right, parent->right);
            parent->color = getColor(parent);
            parent->left->color = BLACK;
            parent->right->color = BLACK;
            return false;
        } else if (getColor(brother) == BLACK && parent->right == brother && getColor(brother->left) == RED && getColor(brother->right) == BLACK) { // RL
            parent = reBalance(brother->left, parent, brother, parent->left, brother->left->left, brother->left->right, brother->right);
            parent->color = getColor(parent);
            parent->left->color = BLACK;
            parent->right->color = BLACK;
            return false;
        }
        return false;
    }

public:
    TreeMap() {
        this->root = NULL;
        this->size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    void put(K key, V value) {
        root = add(root, key, value);
        root->color = BLACK;
    }

    bool contains(K key) {
        return contains(root, key) != NULL;
    }

    V get(K key) {
        return contains(root, key)->value;
    }

    void remove(K key) {
        removeNode(root, key);
    }

    ~TreeMap() {
        Array<TreeNode<K, V>*>* result = new Array<TreeNode<K, V>*>();
        TravelHelper::postOrder(root, result);
        typename Array<TreeNode<K, V>*>::iterator* it = result->newIterator();
        while(it->hasNext()) {
            delete it->next();
        }
        delete it;
        delete result;
    }

};

#endif // TREENODE_H_INCLUDED
