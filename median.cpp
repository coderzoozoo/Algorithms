/*
 * =====================================================================================
 *
 *       Filename:  median.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/2015 00:15:39
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
#include <limits>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

typedef struct heap{
    vector<int> A;
    int heap_size;
}heap;


const int INF = std::numeric_limits<int>::max();

inline int parent(int i){ return ((i-1)/2);}
inline int left(int i){return (2*i + 1);}
inline int right(int i) {return (2*i + 2);}
inline void swap(int& a, int& b){a = a+b; b = a -b; a = a - b;}

void maxHeapify(heap& h, int i){
    int l = left(i);
    int r = right(i);
    int largest = INF;

    if(l < h.heap_size && h.A[l] > h.A[i]){
        largest = l;
    } else {
        largest = i;
    }

    if(r < h.heap_size && h.A[r] > h.A[largest]){
        largest = r;
    }

    if(largest != i){
        swap(h.A[largest], h.A[i]);
        maxHeapify(h, largest);
    }
}


void heapIncreaseKey(heap& h, int i, int x){
    if(x < h.A[i]){
        cout<<"new key is less than current key"<<"\n";
        exit(0);
    }

    h.A[i] = x;
    while(i > 0 && h.A[parent(i)] <  h.A[i]){
        swap(h.A[i], h.A[parent(i)]);
        i = parent(i);
    }
}

void insertIntoMaxHeap(heap& h, int x){
    h.heap_size += 1;
    h.A[h.heap_size-1]= (-INF);
    heapIncreaseKey(h, h.heap_size-1, x);
}

int  extractMax(heap& h){
    if(h.heap_size < 1){
        cout<<"Heap underflow!"<<"\n";
        exit(0);
    }
    int max = h.A[0];
    h.A[0] = h.A[h.heap_size-1];
    //h.A.pop_back();
    h.heap_size -= 1;
    maxHeapify(h, 0);
    return max;
}


void minHeapify(heap& h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = -INF;

    if(l < h.heap_size && h.A[l] < h.A[i]){
        smallest = l;
    } else {
        smallest = i;
    }

    if(r < h.heap_size && h.A[r] < h.A[smallest]){
        smallest = r;
    }

    if(smallest != i){
        swap(h.A[smallest], h.A[i]);
        minHeapify(h, smallest);
    }
}


void heapDecreaseKey(heap& h, int i, int x){
    if(x > h.A[i]){
        cout<<x<<"\t"<<h.A[i]<<"\n";
        cout<<"new key is greater than current key"<<"\n";
        exit(0);
    }
    h.A[i] = x;
    while(i > 0 && h.A[parent(i)] > h.A[i]){
        swap(h.A[i], h.A[parent(i)]);
        i = parent(i);
    }
}

void insertIntoMinHeap(heap& h, int x){
    h.heap_size += 1;
    h.A[h.heap_size-1]= (INF);
    heapDecreaseKey(h, h.heap_size-1, x);
}

int  extractMin(heap& h){
    if(h.heap_size < 1){
        cout<<"Heap underflow!"<<"\n";
        exit(0);
    }
    int min = h.A[0];
    h.A[0] = h.A[h.heap_size-1];
    //h.A.pop_back();
    h.heap_size -= 1;
    minHeapify(h, 0);
    return min;
}


void printVect(vector<int> A){
    for(int i = 0; i < A.size(); i++){
        cout<<A[i]<<"\t";
    }
    cout<<"\n";
}


void getEleVecFromFile(vector<int>& inv, string fname){
    ifstream is(fname);
    if(!is) return;
    int value;
    while(is >> value){
        inv.push_back(value);
    }
}

int main(void){
    vector<int> inpvec;
    getEleVecFromFile(inpvec, "Median.txt");
    cout<<"read vector: "<<inpvec.size()<<"\n";
    heap hlow; //supports extract max
    hlow.heap_size=0;
    heap hhigh; //supports extract min
    hhigh.heap_size = 0;
    int sum=0;
    for(int i=0; i < 10000; i++){
        hhigh.A.push_back(0);
        hlow.A.push_back(0);
    }
    for(int i=0; i<inpvec.size(); i++){
        if(hlow.heap_size == 0){
            insertIntoMaxHeap(hlow, inpvec[i]);
        } else {
            int hlow_max = hlow.A[0];
            if(inpvec[i] <= hlow.A[0]){
                insertIntoMaxHeap(hlow, inpvec[i]);
            } else {
                insertIntoMinHeap(hhigh, inpvec[i]);
            }
        }

        if(hlow.heap_size > hhigh.heap_size && hlow.heap_size - hhigh.heap_size > 1){
            insertIntoMinHeap(hhigh, extractMax(hlow));
        } else if(hlow.heap_size < hhigh.heap_size){
            insertIntoMaxHeap(hlow, extractMin(hhigh));
        }
        sum += hlow.A[0];
        cout<<hlow.A[0]<<"\n";
    }
    cout<<"hlow size: "<<hlow.heap_size<<"\n";
    cout<<"hhigh size: "<<hhigh.heap_size<<"\n";
    cout<<"hlow max: "<<hlow.A[0]<<"\t"<<"hhigh min: "<<hhigh.A[0]<<"\n";
    cout<<"Sum : " <<sum%10000<<"\n";

    return 0;
}
