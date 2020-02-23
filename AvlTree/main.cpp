//
//  main.cpp
//  AvlTree
//
//  Created by apple on 2020/2/21.
//  Copyright © 2020 apple. All rights reserved.
//

#include <iostream>
#include "AvlTree.h"
#define Len(a) ((sizeof(a))/(sizeof(a[0])))
using namespace std;
static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
int main() {
    AvlTree<int> * tree = new AvlTree<int>();
    for(int i=0;i<Len(arr);i++){
        tree->insert(arr[i]);
    }
    cout<< tree->find(1) <<endl;
    cout << tree->height()<< endl;
    cout << tree->maximun() << endl;
    tree->remove(7);
    tree->remove(12);
    tree->print();
    return 0;
}
