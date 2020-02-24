//
//  main.cpp
//  PriorityQueue
//
//  Created by apple on 2020/2/23.
//  Copyright © 2020 apple. All rights reserved.
//

#include <iostream>
#include "PriorityQueue.h"
#define Len(a) (sizeof(a)/sizeof(a[0]))
using namespace std;
static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
int main() {
    PriorityQueue<int> p = PriorityQueue<int>(arr, Len(arr));
    cout << p.getHead() << endl;
    for(int i=0;i<Len(arr)-1;i++){
        p.deQueue();
        cout << p.getHead() << endl;
    }
}
