/*
 * =====================================================================================
 *
 *       Filename:  clustering.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2015 11:14:04
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

using namespace std;
const int INF = numeric_limits<int>::max();

typedef struct node {
    int label;
    struct node* leader;
}node;

typedef struct graph {
    int n1;
    int n2;
    int edge_cost;
}graph;

void mergeDiff(vector<graph>& nvec, int p, int q, int r){
    int n1 = q-p+1;
    int n2 = r-q;
    vector<graph> L;
    vector<graph> R;
    for(int i=0;i<n1; i++){
        L.push_back(nvec[p+i]);    
    }
    for(int i=0; i<n2; i++){
        R.push_back(nvec[q+i+1]);
    }

    int i = 0;
    int j = 0;
    for(int k=p; k <= r; k++){
        if(i< L.size() && j < R.size()){
            if(L[i].edge_cost <= R[j].edge_cost){
                nvec[k] = L[i];
                i += 1;
            } else {
                nvec[k] = R[j];
                j += 1;
            }
        } else if(i==L.size() && j < R.size()){
            nvec[k] = R[j];
            j++;
        } else if(j == R.size() && i < L.size()){
            nvec[k] = L[i];
            i++;
        }
    }
}

void mergeSort(vector<graph>& nvec, int p, int r){
    if(p<r){
        int q = (p+r)/2;
        mergeSort(nvec, p, q);
        mergeSort(nvec, q+1, r);
        mergeDiff(nvec, p, q, r);
    }
}

void printGraph(vector<graph>& nvec){
    for(int i=0; i<nvec.size(); i++){
        cout<<nvec[i].n1<<"\t"<<nvec[i].n2<<"\t"<<nvec[i].edge_cost<<"\n";
    }
}


void printLeaders(vector<int>& v){
    for(int i=0; i < v.size(); i++){
        if(i == v[i])
            cout<<v[i]<<"\t";
    }
    cout<<"\n";
}


void readInputFile(vector<graph>& nvec, string fname, int& N){
    ifstream is(fname);
    if(!is) exit(1);

    int count = 1;
    string line;
    while(getline(is, line)){
        stringstream ls(line);
        if(count > 0){
            ls>>N;
            count--;
        } else {
            int n1, n2, ec;
            graph tmp;
            ls>>n1>>n2>>ec;
            tmp.n1 = n1 - 1;
            tmp.n2 = n2 - 1;
            tmp.edge_cost = ec;
            nvec.push_back(tmp);
        }
    }
}

inline int find(vector<int>& lv, int n ){
    int l = n;
    while(lv[l] != l){
        l = lv[l];
    }
    return l;
}

inline void clusterUnion(vector<int>& lv, int n1, int n2){
    lv[n1] = n2;
}

void initLeaders(vector<int>& lv, int N){
    for(int i=0; i< N; i++){
        lv[i]=i;
    }
}

/* Takes a vector of nodes as input. Outputs k clusters */
int findKSpacing(vector<graph>& nvec, int k, int N){
    vector<int> lv(N);
    int clust_cnt = N;
    initLeaders(lv, N);
    int i;
    for(i=0; i<nvec.size(); i++) {
        if (clust_cnt == k) break;
        int l1 = find(lv, nvec[i].n1);
        int l2 = find(lv, nvec[i].n2);
        //cout<<l1<<"\t"<<l2<<"\n";
        if(l1 != l2) {
            clusterUnion(lv, l1, l2);
            clust_cnt--;
        }
    }

    cout<<"clusters: "<<clust_cnt<<"\n";
    cout<<"nvec size: "<<nvec.size()<<"\n";
    cout<<"i: "<<i<<"\n";
    printLeaders(lv);

    vector<int> edgelist;
    while(i < nvec.size()){
        if(find(lv, nvec[i].n1) != find(lv, nvec[i].n2)){
//            cout<<"edge_cost: "<<nvec[i].edge_cost<<"\n";
            edgelist.push_back(nvec[i].edge_cost); 
        }
        i++;
    }
    
    cout<<"edgelist size: "<<edgelist.size()<<"\n";
    int min = INF;
    for(int j=0; j<edgelist.size(); j++){
        cout<<min<<"\t"<<edgelist[j]<<"\n";
        if(min > edgelist[j]){
            min = edgelist[j];    
        }
    }
    cout<<"min: "<<min<<"\n";
    return min;
} 

int main(void){
    int N;
    string fname = "clustering1.txt";
    vector<graph> nvec;
    readInputFile(nvec, fname, N);
    mergeSort(nvec, 0, nvec.size()-1);
//    printGraph(nvec);
    cout<<"max spacing: "<<findKSpacing(nvec, 4, N)<<"\n";
    cout<<"size of int: "<<sizeof(int)<<"\n";
    
}
