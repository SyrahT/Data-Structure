//
//  AvlTree.h
//  AvlTree
//
//  Created by apple on 2020/2/21.
//  Copyright © 2020 apple. All rights reserved.
// https://www.cnblogs.com/skywang12345/p/3577360.html#a3

#ifndef AvlTree_h
#define AvlTree_h

#include <iostream>
using namespace std;

template <class T>
class AvlTree{
    struct AvlNode{
        T key;
        int height;
        AvlNode *left;
        AvlNode *right;
        
        AvlNode(T value, AvlNode *l=NULL, AvlNode *r=NULL):key(value),height(0),left(l),right(r){}
    };
private:
    AvlNode *root;
    int height(AvlNode *t){return t==NULL?0:t->height;}
    void LL(AvlNode* &t);
    void RR(AvlNode* &t);
    void LR(AvlNode* &t);
    void RL(AvlNode* &t);
    int max(int a, int b){return a>b?a:b;}
    void destory(AvlNode* &t);
    void insert(T ket, AvlNode *&t);
    void print(AvlNode* &t);
    
public:
    AvlTree():root(NULL){}
    ~AvlTree(){destory(root);}
    
    int height(){return height(root);};
    void insert(T key);
    void move(T key);
    void print(){print(root);}
    
};


template <class T>
void AvlTree<T>::LL(AvlNode* &t){
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::RR(AvlNode* &t){
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::LR(AvlNode* &t){
    RR(t->left);
    LL(t);
}

template <class T>
void AvlTree<T>::RL(AvlNode* &t){
    LL(t->right);
    RR(t);
}

template <class T>
void AvlTree<T>::insert(T key){
    insert(key, root);
}

template <class T>
void AvlTree<T>::insert(T key, AvlNode* &t){
    if (t==NULL)
        t = new AvlNode(key);
    else if(key<t->key){
        insert(key, t->left);
        if (height(t->left)-height(t->right)==2){
            if (key<t->left->key) LL(t);
            else LR(t);
        }
    }else if(key>t->key){
        insert(key, t->right);
        if (height(t->right)-height(t->left)==2){
            if (key<t->right->key) RL(t);
            else RR(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class T>
void AvlTree<T>::destory(AvlNode* &t){
    if (t==NULL) return;
    if (t->left!=NULL) destory(t->left);
    if (t->right!=NULL) destory(t->left);
    delete t;
}

template <class T>
void AvlTree<T>::print(AvlNode* &t){
    if (t==NULL) return;
    cout << t->key << " Left:";
    if(t->left==NULL)
        cout << "NULL";
    else
        cout << t->left->key;
    cout << " Right:";
    if(t->right==NULL)
        cout << "NULL";
    else
        cout << t->right->key;
    cout << endl;
    print(t->left);
    print(t->right);
}

#endif /* AvlTree_h */
