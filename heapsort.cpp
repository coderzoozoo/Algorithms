/*
 * =====================================================================================
 *
 *       Filename:  heapsort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/08/2015 15:49:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ravish Mishra (), ravish.mishra@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

typedef struct heap{
    vector<int> A;
    int heap_size;
}heap;
const int INF = std::numeric_limits<int>::max();


typedef vector<int>::iterator viter;

inline int parent(int i){return i/2;}
inline int left(int i) {return 2*i+1;}
inline int right(int i){return (2*i + 2);}
inline int swap(int& a, int& b) {a=a+b; b = a - b; a = a - b;}

void printVect(vector<int> sv){
    for(int i=0; i<sv.size(); i++){
        cout<<sv[i]<<"\t";
    }
    std::cout<<'\n';
}

void maxHeapify(heap& h, int i){
    int l = left(i);
    int r = right(i);
    int largest = -INF;
    if (l < h.heap_size && h.A[l] > h.A[i]){
        largest = l;
    } else {
        largest = i;
    }
    if(r < h.heap_size && h.A[r]> h.A[largest]){
        largest = r;
    }
    if(largest != i){
        swap(h.A[i], h.A[largest]);
        maxHeapify(h,largest);
    }
}

void buildMaxHeap(heap& h){
    h.heap_size = h.A.size();
    for(int i = (h.A.size()/2) - 1; i>=0; i--){
        maxHeapify(h, i);
    }
}


void heapSort(heap& h){
    buildMaxHeap(h);
    for(int i=h.A.size()-1; i>0; i--){
        //Exchange A[1] and A[i]
        swap(h.A[0], h.A[i]);
        h.heap_size = h.heap_size-1;
        maxHeapify(h, 0);
    }
}



int main(void){
    heap h;
    h.A = {5,13,2,25,7,17,20,8,4};
    h.heap_size=0;
    heapSort(h);
    printVect(h.A);
}
