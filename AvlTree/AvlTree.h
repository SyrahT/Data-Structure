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
class AvlNode{
public:
    T key;
    int height;
    AvlNode<T> *left;
    AvlNode<T> *right;
    
    AvlNode(T value, AvlNode<T> *l=NULL, AvlNode<T> *r=NULL):key(value),height(1),left(l),right(r){}
};

template <class T>
class AvlTree{
private:
    AvlNode<T> *root;
    int height(AvlNode<T> *t){return t==NULL?0:t->height;}
    void LL(AvlNode<T>* &t);
    void RR(AvlNode<T>* &t);
    void LR(AvlNode<T>* &t);
    void RL(AvlNode<T>* &t);
    int max(int a, int b){return a>b?a:b;}
    void destory(AvlNode<T>* &t);
    void insert(T ket, AvlNode<T> *&t);
    void remove(T ket, AvlNode<T> *&t);
    AvlNode<T>* maximun(AvlNode<T> *t) const;
    AvlNode<T>* minimun(AvlNode<T> *t) const;
    void print(AvlNode<T>* t)const;
    bool find(T key, AvlNode<T> *t) const;
    
public:
    AvlTree():root(NULL){}
    ~AvlTree(){destory(root);}
    
    int height(){return height(root);};
    void insert(T key);
    void remove(T key);
    T maximun(){return maximun(root)->key;}
    T minimun(){return minimun(root)->key;}
    void print(){print(root);}
    bool find(T key){return find(key, root);}
    
};


template <class T>
void AvlTree<T>::LL(AvlNode<T>* &t){
    AvlNode<T> *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::RR(AvlNode<T>* &t){
    AvlNode<T> *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::LR(AvlNode<T>* &t){
    RR(t->left);
    LL(t);
}

template <class T>
void AvlTree<T>::RL(AvlNode<T>* &t){
    LL(t->right);
    RR(t);
}

template <class T>
void AvlTree<T>::insert(T key){
    insert(key, root);
}

template <class T>
void AvlTree<T>::insert(T key, AvlNode<T>* &t){
    if (t==NULL)
        t = new AvlNode<T>(key);
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
void AvlTree<T>::destory(AvlNode<T>* &t){
    if (t==NULL) return;
    if (t->left!=NULL) destory(t->left);
    if (t->right!=NULL) destory(t->left);
    delete t;
}

template <class T>
void AvlTree<T>::print(AvlNode<T>* t)const{
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

template <class T>
bool AvlTree<T>::find(T key, AvlNode<T> *t)const{
    while(t!=NULL && t->key!=key){
        if(key<t->key)
            t = t->left;
        else
            t = t->right;
    }
    return t!=NULL;
}

template <class T>
void AvlTree<T>::remove(const T key){
    if(!find(key))
        cout << "Don't find " << key << "." << endl;
    else
        remove(key, root);
}

template <class T>
void AvlTree<T>::remove(T key, AvlNode<T>* &t){
    if(t==NULL) return;
    if(key<t->key){
        remove(key, t->left);
        if(height(t->right)-height(t->left)==2){
            AvlNode<T> *r=t->right;
            if(height(r->left)>height(r->right))
                RL(t);
            else
                RR(t);
        }
    }else if(key>t->key){
        remove(key, t->right);
        if(height(t->left)-height(t->right)==2){
            AvlNode<T> *l=t->left;
            if(height(l->left)>height(l->right))
                LL(t);
            else
                LR(t);
        }
    }else{
        if(t->left!=NULL && t->right!=NULL){
            if(height(t->left)>height(t->right)){
                AvlNode<T> *tmp=maximun(t->left);
                t->key = tmp->key;
                remove(t->key, t->left);
            }else{
                AvlNode<T> *tmp=minimun(t->right);
                t->key = tmp->key;
                remove(t->key, t->right);
            }
        }else{
            AvlNode<T> *tmp=t;
            t = (t->left!=NULL)?t->left:t->right;
            delete tmp;
        }
        
    }
}

template <class T>
AvlNode<T>* AvlTree<T>::maximun(AvlNode<T> *t) const{
    while(t->right!=NULL) t = t->right;
    return t;
}

template <class T>
AvlNode<T>* AvlTree<T>::minimun(AvlNode<T> *t) const{
    while(t->left!=NULL) t = t->left;
    return t;
}

#endif /* AvlTree_h */
