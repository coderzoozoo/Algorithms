/*
 * =====================================================================================
 *
 *       Filename:  apsp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/2015 14:40:00
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
const int INF = std::numeric_limits<int>::max();

typedef struct dgraph{
    int label;
    int key;
}dgraph;


typedef struct heap{
    vector<dgraph> A;
    int heap_size;
}heap;

void printVect(vector<int> A){
    for(int i = 0; i < A.size(); i++){
        cout<<A[i]<<"\t";
    }
    cout<<"\n";
}

void printGraph(vector< vector<dgraph> >& al, int nlines){
    int num_iter = (al.size() < nlines)?al.size(): nlines;
    for(int i=0;i<num_iter; i++){
        cout<<i<<"\t";
        for(int j=0; j < al[i].size(); j++){
            cout<<al[i][j].label<<", "<<al[i][j].key<<"\t";
        }
        cout <<"\n";
    }
}

void readDataIntoAl(vector< vector<dgraph> >& al, string fname){
    ifstream is(fname);
    if(!is) return;
    string line;
    int v1, v2, e;
    int count=1;
    while(getline(is, line)){
        stringstream ls(line);
        string val;
        int index;
        if(count>0){
           count--;
        }
        else{
           ls>>v1>>v2>>e;
           dgraph tmp; 
           tmp.label = v2-1;
           tmp.key = e;
           al[v1-1].push_back(tmp);
        }
    }
}

void readSize(string fname, int& n, int& m){
    ifstream is(fname);
    if(!is) return;
    string line;
    while(getline(is, line)){
        stringstream ls(line);
        ls>>n>>m;
        break;
    }
}


int floydWarshall(vector< vector<dgraph> >& al, int n){
    vector<vector<int>> A(n, vector<int>(n));
    cout<<"Array Allocated"<<"\n";
    for(int i=0; i<n; i++){
        for(int j=0; j < n; j++){
            if(i==j){
                A[i][j] = 0;
                continue;
            }
            bool found = false;
            for(int l=0; l<al[i].size(); l++){
                if(al[i][l].label == j){
                    A[i][j] = al[i][l].key;
                    found = true;
                    break;
                }
            }
            if(!found){
                A[i][j] = INF;
              //  cout<<A[i][j][0]<<"\n";
            }
        }
    }
    cout<<"Initialization done"<<"\n";
    

    int min=INF;
    for(int k=0; k<n; k++){
        if(k%100 == 0)cout<<"k: "<<k<<"\n";
        for(int i=0; i< n; i++){
            for(int j=0; j<n; j++){
                int tmp = (A[i][k]==INF || A[k][j]==INF)? INF: A[i][k] + A[k][j];
                A[i][j] = (A[i][j]< tmp)?A[i][j]:tmp; 
                min = (min < A[i][j])? min: A[i][j];
            }
        }
    }

    for(int i=0; i<n; i++){
        if(A[i][i] < 0){
            cout<<"graph has negative cycles."<<"\t"<<i<<"\n";
            return -1;
            //exit(1);
        }
    }

    return min;

}

int main(void) {
    int n, m;
    //vector<string> fv {"g1.txt", "g2.txt", "g3.txt"};
    int x = INF;
    string fname = "g3.txt";
    cout<<fname<<"\n";
    readSize(fname, n, m);
    cout<<"n:"<<n<<"\t"<<"m:"<<m<<"\n";
    vector< vector<dgraph> > al(n);
    readDataIntoAl(al, fname);
    int msp = floydWarshall(al, n);
    cout<<"msp: "<<msp<<"\n";
//    printGraph(al, 200);
    return 0;
}
