/*
 * =====================================================================================
 *
 *       Filename:  dijkshtra.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/01/2015 19:10:15
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


typedef struct dgraph{
    int label;
    int key;
}dgraph;


typedef struct heap{
    vector<dgraph> A;
    int heap_size;
}heap;

const int INF = std::numeric_limits<int>::max();

inline int parent(int i){ return (i/2);}
inline int left(int i){return (2*i + 1);}
inline int right(int i) {return (2*i + 2);}
void swap(dgraph& a, dgraph& b) {
    dgraph tmp;
    tmp.label = a.label;
    tmp.key = a.key;

    a.label = b.label;
    a.key = b.key;

    b.label = tmp.label;
    b.key = tmp.key;
}


void printVect(vector<int> A){
    for(int i = 0; i < A.size(); i++){
        cout<<A[i]<<"\t";
    }
    cout<<"\n";
}

void printGraph(vector< vector<dgraph> >& al){
    for(int i=0;i<al.size(); i++){
        for(int j=0; j < al[i].size(); j++){
            cout<<"\t"<<al[i][j].label<<"\t"<<al[i][j].key<<"\n";
        }
    }
}

void minHeapify(heap& h, int i){
    int l = left(i);
    int r = right(i);
    int smallest = -INF;

    if(l < h.heap_size && h.A[l].key < h.A[i].key){
        smallest = l;
    } else {
        smallest = i;
    }

    if(r < h.heap_size && h.A[r].key < h.A[smallest].key){
        smallest = r;
    }

    if(smallest != i){
        swap(h.A[smallest], h.A[i]);
        minHeapify(h, smallest);
    }
}


void buildMinHeap(heap& h){
    h.heap_size = h.A.size();
    for(int i=(h.A.size()/2)- 1; i>=0; i--){
        minHeapify(h, i);
    }
}

void heapDecreaseKey(heap& h, int i, dgraph node){
    if(node.key > h.A[i].key){
        cout<<"new key is greater than current key"<<"\n";
        exit(0);
    }

    h.A[i] = node;
    while(i > 0 && h.A[parent(i)].key > h.A[i].key){
        swap(h.A[i], h.A[parent(i)]);
        i = parent(i);
    }
}

void insert(heap& h, dgraph node){
    h.heap_size += 1;
    dgraph tnode;
    tnode.label= node.label;
    tnode.key = INF;
    h.A.push_back(tnode);
    heapDecreaseKey(h, h.heap_size-1, node);
}

dgraph extractMin(heap& h){
    if(h.heap_size < 1){
        cout<<"Heap underflow!"<<"\n";
        exit(0);
    }
    dgraph min = h.A[0];
    h.A[0] = h.A[h.A.size()-1];
    h.A.pop_back();
    h.heap_size -= 1;
    minHeapify(h, 0);
    return min;
}

dgraph deleteNode(heap& h, int l){
    dgraph tnode;
    for(int i=0; i<h.heap_size; i++){
        if(h.A[i].label == l){
            tnode.label = l;
            tnode.key= h.A[i].key;
            swap(h.A[i], h.A[h.heap_size-1]);
            h.A.pop_back();
            h.heap_size -= 1;
            minHeapify(h, i);
        }
    }
    return tnode;
}



void readDataIntoAl(vector< vector<dgraph> >& al, string fname){
    ifstream is(fname);
    if(!is) return;
    string line;
    while(getline(is, line)){
        stringstream ls(line);
        string val;
        int count=1;
        int index;
        while(ls>>val){
            if(count > 0){
                index = stoi(val, nullptr);
                //cout<<"index: "<<index<<"\n";
                count--;
            } else {
                string delimiter = ",";
                int pos =val.find(delimiter);
                string token1 = val.substr(0, pos);
                string token2 = val.substr(pos+delimiter.length(), val.length());
                dgraph tnode;
                tnode.label = (stoi(token1, nullptr)) - 1;
                tnode.key = stoi(token2, nullptr);
                al[index-1].push_back(tnode);
            }
        }
    }
}


void createHeap( vector< vector<dgraph> >& al, heap& h, int N, int sn){
    vector<int> nodewt(N, INF);
    for(int i=0; i< al[sn].size(); i++) {
        nodewt[al[sn][i].label] = al[sn][i].key;
    }
    for(int i=0; i< N; i++){
        if(i!=sn){
            dgraph tnode;
            tnode.label = i;
            tnode.key = nodewt[i];
            insert(h, tnode);
        }
    
    }
}


void processNode(vector< vector<dgraph> >& al, heap& h,dgraph node, vector<bool>& X){
    for(int i=0; i<al[node.label].size(); i++){
        if(X[al[node.label][i].label]) continue;
        dgraph tnode = deleteNode(h, al[node.label][i].label);
        tnode.key = (tnode.key < node.key + al[node.label][i].key)?tnode.key:node.key + al[node.label][i].key;
        insert(h, tnode);
    }
    
}


void calculateShortestPath(vector< vector<dgraph> >&al, vector<int>& spv, int srcnode){
    vector<bool> X(200, false); 
    X[srcnode]= true;
    spv[srcnode] = 0;
    int np = 1;
    heap h;
    h.heap_size=0;
    createHeap(al, h, al.size() ,srcnode);
    do{
        dgraph tnode = extractMin(h);
        if(X[tnode.label]) continue;
        X[tnode.label] = true;
        spv[tnode.label] = tnode.key;
        processNode(al, h, tnode, X);
        np++;
    }while(np<al.size());
}

int main(void){
    int N = 200;
    vector< vector<dgraph> > al(N);
    string fname = "dijkstraData.txt";
    readDataIntoAl(al, fname);
    vector<int> spv(N, 0);
    calculateShortestPath(al, spv, 0);
    vector<int> t{7,37,59,82,99,115,133,165,188,197};
    printVect(spv);
    
    for(int i=0; i<t.size();i++){
        cout<<spv[t[i]-1]<<",";
    }
    cout<<"\n";
}
