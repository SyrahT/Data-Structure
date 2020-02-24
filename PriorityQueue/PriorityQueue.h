//
//  PriorityQueue.h
//  PriorityQueue
//
//  Created by apple on 2020/2/23.
//  Copyright © 2020 apple. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

template <class T>
class PriorityQueue {
private:
    int length;
    T *arr;
    int size;
    void doubleSize();
    void buildHeap();
    void percolateDown(int i);
    
public:
    PriorityQueue(int s=100):length(0),size(s){arr = new T [s];}
    PriorityQueue(const T data[], int l);
    ~PriorityQueue(){delete [] arr;}
    bool isEmpty() {return length==0;}
    void enQueue(const T &x);
    T deQueue();
    T getHead(){return arr[1];}
    
};

template <class T>
PriorityQueue<T>::PriorityQueue(const T data[], int l):length(l),size(l+10){
    arr = new T [size];
    for(int i=1;i<=l;i++) arr[i] = data[i-1];
    buildHeap();
}

template <class T>
void PriorityQueue<T>::enQueue(const T &x){
    if(length==size-1) doubleSize();
    int i=++length;
    for(;i>1 && x<arr[i/2];i/=2){
        arr[i] = arr[i/2];
    }
    arr[i] = x;
}

template <class T>
T PriorityQueue<T>::deQueue(){
    T minItem=arr[1];
    arr[1] = arr[length--];
    percolateDown(1);
    return minItem;
}

template <class T>
void PriorityQueue<T>::percolateDown(int i){
    int child;
    T tmp=arr[i];
    for(;i*2<=length;i=child){
        child=i*2;
        if(child+1<=length && arr[child+1]<arr[child]) child++;
        if(arr[child]<tmp) arr[i] = arr[child];
        else break;
    }
    arr[i] = tmp;
}

template <class T>
void PriorityQueue<T>::doubleSize(){
    size *= 2;
    T* tmp=arr;
    arr = new T [size];
    for(int i=0;i<=length;i++) arr[i] = tmp[i];
    delete [] tmp;
}

template <class T>
void PriorityQueue<T>::buildHeap(){
    for(int i=length/2;i;i--) percolateDown(i);
}

#endif /* PriorityQueue_h */
