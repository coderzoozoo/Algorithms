#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef struct kele {
    int a;
    int list_index;
    int index;
}kele;


typedef struct heap{
    vector<kele> A;
    int heap_size;
}heap;

const int INF = std::numeric_limits<int>::max();

inline int parent(int i){return i/2;}
inline int left(int i) {return 2*i+1;}
inline int right(int i){return (2*i + 2);}

void  swap(kele& l, kele& r) {
    kele tmp;
    tmp.a = l.a;
    tmp.list_index = l.list_index;
    tmp.index = l.index;

    l.a = r.a;
    l.list_index = r.list_index;
    l.index = r.index;

    r.a = tmp.a;
    r.list_index = tmp.list_index;
    r.index = tmp.index;
}

void printVect(vector<int> sv){
    for(int i=0; i<sv.size(); i++){
        cout<<sv[i]<<"\t";
    }
    std::cout<<'\n';
}

void minHeapify(heap& h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = -INF;
    if(l<h.heap_size && h.A[i].a > h.A[l].a){
        smallest = l;
    } else {
        smallest = i;
    }
    if(r < h.heap_size && h.A[smallest].a > h.A[r].a){
        smallest = r;
    }
    if(i != smallest){
        swap(h.A[i], h.A[smallest]);
        minHeapify(h, smallest);
    }
}

void buildMinHeap(heap& h){
    h.heap_size = h.A.size();
    for(int i = (h.A.size()-1)/2; i >= 0; i--){
        minHeapify(h, i);    
    }
}

/*
void heapDecreaseKey(heap& h, int i, int key){
    if(h.A[i] <= key){
        cout<<"\n new key is greater than the current key";
        exit(0);
    }
    h.A[i] = key;
    while(i>0 && A[parent(i)]> A[i]){
        swap(h.A[i], h.A[parent(i)]);
        i = parent(i);
    }
}


void minHeapInsert(heap& h, int key){
    h.heap_size += 1;
    A[heap_size-1] = INF;
    heapDecreaseKey(h, h.heap_size-1, key);
}


void buildMinHeapByInsertion(heap& h){
    h.heap_size = 1;
    for(int i =0; i<h.A.size(); i++){
        minHeapInsert(h, A[i]);
    }
}
*/

int** allocateTwoDArray(int rows, int cols){
    int **matrix = 0;
    //Allocate memory for rows
    try{
        matrix = new int *[rows];
    }
    catch(std::bad_alloc& ba){
        cout<<"Allocation Failed";
        exit(0);
    }

    //Allocate memory for columns
    for(int i=0; i<rows; i++){
        try{
            matrix[i] = new int[cols];
        }
        catch(std::bad_alloc& ba){
            for(int j=0; j<i; j++){
                delete [] matrix[j];
                delete [] matrix;
                exit(0);
            }
        }
    }
    return matrix;
}


void kWayMerge(vector<int>& ov, int (&matrix)[3][4], int row, int cols){
    heap h;
    for(int i=0; i<row; i++){
        kele tmp;
        tmp.a = matrix[i][0];
        tmp.list_index = i;
        tmp.index = 0;
        h.A.push_back(tmp);
    }
    buildMinHeap(h);
    for(int i=0; i < (row*cols); i++){
        ov.push_back(h.A[0].a);
        if(h.A[0].index+1< cols){
            h.A[0].a = matrix[h.A[0].list_index][h.A[0].index+1];
            h.A[0].index += 1;
        } else {
            h.A[0].a = h.A[h.heap_size-1].a; 
            h.A[0].list_index = h.A[h.heap_size-1].list_index;
            h.A[0].index = h.A[h.heap_size-1].index;
            h.heap_size -= 1; 
        }
        minHeapify(h, 0);
    }
}


int main (void) {
    int arr[][4] = {{1, 3, 5, 7},
                    {2, 4, 6, 8},
                    {0, 9, 10, 11}}; 
    vector<int> ov;    
    kWayMerge(ov, arr, 3, 4);
    printVect(ov);
    return 0;
}
