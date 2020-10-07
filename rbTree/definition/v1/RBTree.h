#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "Array.h"
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
class RBTree {
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
        TreeNode<T>* nextNode = NULL;
        if(node->value > value) {
            nextNode = add(node->left, value);
            node->left = nextNode;
        } else if (node->value < value) {
            nextNode = add(node->right, value);
            node->right = nextNode;
        } else {
            node->value = value;
            return node;
        }
        return insertBalance(node, nextNode);
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
    TreeNode<T>* removeMax(TreeNode<T>*& node, TreeNode<T>*& parent) {
        if(node->hasRight()) {
            parent = node;
            return removeMax(node->right, parent);
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
    TreeNode<T>* removeMin(TreeNode<T>*& node, TreeNode<T>*& parent) {
        if(node->hasLeft()) {
            parent = node;
            return removeMin(node->left, parent);
        } else {
            TreeNode<T>* ret = node;
            node = node->right;
            return ret;
        }
    }

    /**
    *   查找以node为根的最小元素的父结点
    *   返回该最小元素的父结点
    **/
    TreeNode<T>*& findMinParent(TreeNode<T>*& node, TreeNode<T>*& parent) {
        if(node->hasLeft()) {
            return findMinParent(node->left, node);
        } else {
            return parent;
        }
    }

    /**
    *   查找以node为根的最大元素的父结点
    *   返回该最小元素的父结点
    **/
    TreeNode<T>*& findMaxParent(TreeNode<T>*& node, TreeNode<T>*& parent) {
        if(node->hasRight()) {
            return findMaxParent(node->right, node);
        } else {
            return parent;
        }
    }

    /**
    *   删除以node为根的树元素value
    **/
    void removeNode(TreeNode<T>*& parent, TreeNode<T>*& node, T value) {
        if(node == NULL) {
            return ;
        }
        if(node->value == value) {
            if(node->hasLeft()) {
                TreeNode<T>*& parent = findMaxParent(node->left, node);
                TreeNode<T>*& delNode = parent == node ? node->left : parent->right;
                TreeNode<T>* brotherNode = parent == node ? node->right : parent->left;
                removeSimpleNode(parent, delNode, brotherNode, node);
            } else if(node->hasRight()) {
                TreeNode<T>*& parent = findMinParent(node->right, node);
                TreeNode<T>*& delNode = parent == node ? node->right : parent->left;
                TreeNode<T>* brotherNode = parent == node ? node->left : parent->right;
                removeSimpleNode(parent, delNode, brotherNode, node);
            } else {
                if(parent != NULL) {
                    TreeNode<T>* brotherNode = parent->left == node ? parent->right : parent->left;
                    removeLeafNode(parent, node, brotherNode);
                } else {
                    delete node;
                    node = NULL;
                }
            }
            size--;
        } else if(node->value > value) {
            removeNode(node, node->left, value);
        } else {
            removeNode(node, node->right, value);
        }
    }

    bool isNeedReBalanceInDeletion(TreeNode<T>* delNode) {
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

    /**
    *  待删除的结点非叶子结点，实际删除的结点在以该结点为根的子树下
    **/
    void removeSimpleNode(TreeNode<T>*& parent, TreeNode<T>*& delNode, TreeNode<T>* brotherNode, TreeNode<T>*& node) {

        bool flag = true;
        bool isNeedReBalance = isNeedReBalanceInDeletion(delNode);
        if(node == parent) {
            TreeNode<T>* oldNode = node;
            TreeNode<T>* oldDelNode = delNode;
            TreeNode<T>* replaced = oldDelNode->hasLeft() ? oldDelNode->left : oldDelNode->right;
            delNode = replaced;
            node = replaceNode(oldDelNode, node);
            delete oldNode;
            flag = false;
        }

        ///cout<<"node->value= "<<node->value<<" parent->value= "<<parent->value<<endl;
        if(isNeedReBalance) {
            parent = deleteReBalance(parent, brotherNode);
        }

        if(flag) {
            TreeNode<T>* oldNode = node;
            TreeNode<T>* oldDelNode = delNode;
            TreeNode<T>* replaced = oldDelNode->hasLeft() ? oldDelNode->left : oldDelNode->right;
            delNode = replaced;
            node = replaceNode(oldDelNode, node);
            delete oldNode;
        }
    }

    void removeLeafNode(TreeNode<T>*& parent, TreeNode<T>*& delNode, TreeNode<T>* brotherNode) {
        if(isNeedReBalanceInDeletion(delNode)) {
            parent = deleteReBalance(parent, brotherNode);
        }
        cout<<"after Balanced"<<endl;
        delete delNode;
        delNode = NULL;
    }

    TreeNode<T>* replaceNode(TreeNode<T>* from, TreeNode<T>* to) {
        if(from == NULL || to == NULL) {
            return NULL;
        }
        from->left = to->left;
        from->right = to->right;
        from->color = to->color;
        return from;
    }


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
        cout<<"parent: "<<parent->value<<" color: "<<parent->color<<" brother: "<<brother->value<<" color: "<<brother->color<<" need reBalance"<<endl;
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
        root = add(root, value);
        root->color = BLACK;
    }

    bool contains(T value) {
        return contains(root, value) != NULL;
    }

    void remove(T value) {
        removeNode(root, root, value);
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
