/*
 * =====================================================================================
 *
 *       Filename:  schedulejobs.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/03/2015 11:22:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ravish Mishra (), ravish.mishra@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

typedef struct job {
    int index;
    int weight;
    int length;
    int diff;
    float ratio;
}job;

const int INF = numeric_limits<int>::max();

void mergeDiff(vector<job>& jvec, int p, int q, int r, string orderby){
    int n1 = q-p+1;
    int n2 = r-q;
    //cout<<"pqr: "<<p<<"\t"<<q<<"\t"<<r<"\n";
    //cout<<"n1: "<<n1<<"\t"<<"n2: "<<n2<<"\n";
    vector<job> L;
    vector<job> R;
    for(int i=0;i<n1; i++){
        //cout<<"L: "<<jvec[p+i]<<"\n";
        L.push_back(jvec[p+i]);    
    }
    for(int i=0; i<n2; i++){
        //cout<<"R: "<<jvec[q+i+1]<<"\n";
        R.push_back(jvec[q+i+1]);
    }
    /*  
    int dummy;
    dummy = -INF;
    L.push_back(dummy);
    R.push_back(dummy);
    */

    int i = 0;
    int j = 0;

    for(int k=p; k <= r; k++){
        if(i< L.size() && j < R.size()){
            if((orderby=="diff" && L[i].diff >= R[j].diff) ||(orderby=="weight" && L[i].weight >= R[j].weight) || (orderby=="ratio" && L[i].ratio >= R[j].ratio)){
                jvec[k] = L[i];
                i += 1;
            } else {
                jvec[k] = R[j];
                j += 1;
            }
        } else if(i==L.size() && j < R.size()){
            jvec[k] = R[j];
            j++;
        } else if(j == R.size() && i < L.size()){
            jvec[k] = L[i];
            i++;
        }
    }
   /* 
    cout<<"inside merge"<<"\n";
    for(int i=p; i <=r; i++){
        cout<<jvec[i]<<"\t";
    }
    cout<<"\n";
    */
}

void mergeSort(vector<job>& jvec, int p, int r, string orderby){
    if(p<r){
        int q = (p+r)/2;
        mergeSort(jvec, p, q, orderby);
        mergeSort(jvec, q+1, r, orderby);
        mergeDiff(jvec, p, q, r, orderby);
    }
}


void readData(vector<job>& jvec, string fname, int& N){
    ifstream is(fname);
    if(!is) exit(0);
    string line;
    int count = 1;
    int jobindex=0;
    while(getline(is, line)){
        stringstream ls(line);
        int val1, val2;
        if(count > 0){
            ls>>N;    
            cout<<"N: "<<N<<"\n";
            count--;
        }else {
            ls>>val1>>val2;
            job tmp;
            tmp.index = jobindex;
            tmp.weight = val1;
            tmp.length = val2;
            tmp.diff = val1 - val2;
            tmp.ratio = float(val1)/float(val2);
            jvec.push_back(tmp);
            jobindex++;
        } 
    
    }
}

void printVec(vector<job>& jvec, int n){
    for(int i=0; i< n; i++){
        cout<<jvec[i].index<<"\t"<<jvec[i].weight<<"\t"<<jvec[i].length<<"\t"<<jvec[i].diff<<"\t"<<jvec[i].ratio<<"\n";
    }
}

void handleTies(vector<job>& jvec){
    int p=0, r;
    for(int i=0; i< jvec.size(); i++){
        if(jvec[i].diff == jvec[p].diff){
            r = i;
            if(i== (jvec.size() - 1) && r > p) mergeSort(jvec, p, r, "weight");
        } else {
            if(r > p) mergeSort(jvec, p, r, "weight");
            p = i;
        }
    }
}


long int calculateWeightedCompletionTime(vector<job> jvec){
    int waiting = 0;
    long int sum=0;
    for(int i=0; i<jvec.size(); i++){
        waiting += jvec[i].length;
        sum += jvec[i].weight*waiting;
    }
    return sum;
}

int main(void){
    vector<job> jvec;
    string fname = "jobs.txt";
    int N;
    readData(jvec, fname, N);
    cout<<jvec.size()<<"\n";
    mergeSort(jvec, 0, jvec.size()-1, "ratio");
    //handleTies(jvec);
    //printVec(jvec, 10000);
    /*  
    vector<int> a{2, 4, 5, 7, 1, 2, 3, 6};
    mergeSort(a, 0, a.size()-1);
    for(int i=0; i< a.size(); i++) cout<<a[i]<<"\t";
    cout<<"\n";
    */
    cout<<"Weighted Completetion time: "<<calculateWeightedCompletionTime(jvec)<<"\n";
    return 0;
}


