//
// Created by Cameron Rosenberger on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLTREE_H

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;
using namespace std;

template<typename K, typename V>
class AVLTree {
private:
    class AVLNode {
    public:
        V val;
        K key;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        int height = 0;

    };

    AVLNode *root = nullptr;

    void inorder_print(AVLTree<K, V>::AVLNode *curr, int level) {
        if (curr != nullptr) {
            inorder_print(curr->left, level + 1);
            cout << setw(level * 2) << curr->key << ": " << curr->val << endl;
            inorder_print(curr->right, level + 1);
        }
    }

    int getHeight(AVLNode *curr);

    V& insert(AVLNode *&, const K &, const V &);
    V& insert(AVLNode *&, const K &);

    void rotateWithRightChild(AVLNode *&k1);

    void rotateWithLeftChild(AVLNode *&k1);

    void doubleWithLeftChild(AVLNode *&k1);

    void doubleWithRightChild(AVLNode *&k1);

    V& find(AVLNode *curr, const K &k) const {

        if (curr != nullptr) {
            if (curr->key == k) {
                return curr->val;
            }else if(k<curr->key){
                return find(curr->left, k);
            }else if(k>curr->key){
                return find(curr->right, k);
            }
        }
        throw runtime_error("V in find not found");
    }

    void kill(AVLNode *&);

    AVLNode* copy(AVLNode *arg);

public:
    AVLTree<K, V>() : root(nullptr) {}
    AVLTree<K,V>& operator=(const AVLTree<K,V>);
    AVLTree(const AVLTree<K, V> &arg);

    ~AVLTree();

    void print() { inorder_print(root, 0); }

    void insertGetV(const K &, const V &);
    V& insertGetV( const K &k);

    V &find(const K &k) const;

    bool isEmpty();

    V& operator[](const K&);
    void destroy();

};
template<typename K, typename V>
AVLTree<K,V>& AVLTree<K,V>::operator=(const AVLTree<K,V> arg){
    AVLTree temp(arg);
    swap(temp.root,root);
    return *this;
}

template<typename K, typename V>
typename AVLTree<K, V>::AVLNode *AVLTree<K, V>::copy(AVLNode *arg) {
    if (arg == nullptr) {
        return nullptr;
    }
    AVLNode *node = new AVLNode;
    node->key = arg->key;
    node->val = arg->val;
    node->left = copy(arg->left);
    node->right = copy(arg->right);
    return node;
}

template<typename K, typename V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V> &arg) {
    root = copy(arg.root);
}

template<typename K, typename V>
V& AVLTree<K, V>::find(const K &k) const {
    return find(root, k);
}

template<typename K, typename V>
//public one
void AVLTree<K, V>::insertGetV(const K &k, const V &v) {
     insert(root, k, v);
}
template<typename K, typename V>
V& AVLTree<K,V>::insertGetV(const K& k){
    return insert(root,k);
}
template<typename K, typename V>
int AVLTree<K, V>::getHeight(AVLNode *curr) {
    if (curr == nullptr) {
        return -1;
    }
    return curr->height;
}

template<typename K, typename V>
V& AVLTree<K, V>::insert(AVLNode *&curr, const K &k) {
    if (curr == nullptr) {
        curr = new AVLNode;

        curr->key = k;
        //curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return curr->val;
    } else if (k < curr->key) {
        if (getHeight(curr->left) - getHeight(curr->right) == 2) {
            if (k < curr->left->key) {
                rotateWithLeftChild(curr);
            } else {
                doubleWithLeftChild(curr);
            }
        }
        return insert(curr->left, k);
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    } else if (curr->key < k) {
        if (getHeight(curr->left) - getHeight(curr->right) == -2) {
            if (k > curr->right->key) {
                rotateWithRightChild(curr);
            } else {
                doubleWithRightChild(curr);
            }
        }
        return insert(curr->right, k);
    } else {
        //curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return curr->val;
    }

}
template<typename K, typename V>
V& AVLTree<K, V>::insert(AVLNode *&curr, const K &k, const V &v) {
    if (curr == nullptr) {
        curr = new AVLNode;
        curr->val = v;
        curr->key = k;
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return curr->val;
    } else if (k < curr->key) {
        V ret = insert(curr->left, k, v);
        if (getHeight(curr->left) - getHeight(curr->right) == 2) {
            if (k < curr->left->key) {
                rotateWithLeftChild(curr);
            } else {
                doubleWithLeftChild(curr);
            }
        }
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return ret;
    } else if (curr->key < k) {
        V ret = insert(curr->right, k, v);
        if (getHeight(curr->left) - getHeight(curr->right) == -2) {
            if (k > curr->right->key) {
                rotateWithRightChild(curr);
            } else {
                doubleWithRightChild(curr);
            }
        }
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return ret;
    } else {
        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    return curr->val;
    }

}
template<typename K, typename V>
V& AVLTree<K,V>::operator[](const K& k){
    return find(k);
}

template<typename K, typename V>
void AVLTree<K, V>::rotateWithRightChild(AVLNode *&k1) {

    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1 = k2;
}

template<typename K, typename V>
void AVLTree<K, V>::rotateWithLeftChild(AVLNode *&k1) {
    AVLNode *k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1 = k2;
}

template<typename K, typename V>
void AVLTree<K, V>::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template<typename K, typename V>
void AVLTree<K, V>::doubleWithLeftChild(AVLNode *&k1) {
    rotateWithRightChild(k1->left);
    rotateWithLeftChild(k1);
}

template<typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    kill(root);
}
template<typename K, typename V>
void AVLTree<K,V>:: destroy(){
    kill(root);
}
template<typename K, typename V>
void AVLTree<K, V>::kill(AVLNode*& arg) {

    if (arg != nullptr) {
        kill(arg->left);
        kill(arg->right);
        delete arg;

    }
}

template<typename K, typename V>
bool AVLTree<K, V>::isEmpty() {
    return root == nullptr;
}

#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H
