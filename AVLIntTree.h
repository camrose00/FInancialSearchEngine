//
// Created by Cameron Rosenberger on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLINTTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLINTTREE_H

#include <iostream>

using namespace std;
template<typename K,typename V>
class AVLIntTree {
private:
    class AVLNode{
    public:
        V val;
        K key;
        AVLNode* left = nullptr;
        AVLNode* right = nullptr;
        int height =0;
    };

    AVLNode* root=nullptr;
    void print(AVLNode* curr){
        if(curr!=nullptr){
            print(curr->left);
            cout<<curr->val<<" ";
            print(curr->right);
        }
    }
    int getHeight(AVLNode* curr){
        if(curr==nullptr){
            return -1;
        }
        return curr->height;
    }
    void insert(AVLNode*& curr,int x){
        if(curr==nullptr) {
            curr = new AVLNode;
            curr->val = x;
        }else if(x<curr->val){
            insert(curr->left,x);
            if(getHeight(curr->left)-getHeight(curr->right)==2){
                if(x<curr->left->val){
                    rotateWithLeftChild(curr);
                }else{
                    doubleWithLeftChild(curr);
                }
            }

        }else if (curr->val<x){
            insert(curr->right,x);
            if(getHeight(curr->left)-getHeight(curr->right)==-2){
                if(x>curr->right->val){
                   rotateWithRightChild(curr);
                }else{
                    doubleWithRightChild(curr);
                }
            }

        }else{
            ;//duplicates
        }
        curr->height = max(getHeight(curr->left),getHeight(curr->right))+1;
    }
    void rotateWithRightChild(AVLNode*& k1){

        AVLNode* k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;
        k1->height=max(getHeight(k1->left),getHeight(k1->right))+1;
        k2->height=max(getHeight(k2->left),getHeight(k2->right))+1;
        k1=k2;
    }
    void doubleWithRightChild(AVLNode*& k1){
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    void rotateWithLeftChild(AVLNode*& k1){
        AVLNode* k2=k1->left;
        k1->left=k2->right;
        k2->right=k1;
        k1->height=max(getHeight(k1->left),getHeight(k1->right))+1;
        k2->height=max(getHeight(k2->left),getHeight(k2->right))+1;
        k1=k2;

    }
    void doubleWithLeftChild(AVLNode*& k1){
        rotateWithRightChild(k1->left);
        rotateWithLeftChild(k1);
    }
public:
    void print(){
        print(root);
    }
    void insert(int x){
        insert(root,x);
    }
};


#endif //INC_22SU_SEARCH_ENGINE_AVLINTTREE_H
