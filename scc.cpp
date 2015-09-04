/*
 * =====================================================================================
 *
 *       Filename:  scc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/20/2015 18:58:35
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
#include <fstream>
#include <list>
#include <limits>
#include <sstream>
#include <exception>
#include <algorithm>

using namespace std;

int N = 875714;
//int N=9;
vector<int> lvec(N, -1);
vector<int> ftvec(N, -1);
vector<int> scccnt;

typedef struct gv{
    int label;
    int leader;
}gv;

void printGraph(vector< vector<int> > al){
    for(int i=0; i<al.size(); i++){
        vector<int>::iterator it;
        for(it=al[i].begin(); it != al[i].end(); it++){
            cout<<*it<<"\t";
        }
        cout<<"\n";
    }
}

void printVect(vector<int> vec){
    for(int i=0; i<vec.size(); i++){
        cout<<vec[i]<<"\t";
    }
    cout<<"\n";
}

void printBvect(vector<bool> vec){
    for(int i=0; i<vec.size(); i++){
        cout<<vec[i]<<"\t";
    }
    cout<<"\n";
}


void readDataIntoAl(vector< vector<int> >& al, string fname, bool reverse){
    ifstream is(fname);
    if(!is) return;
    string line;
    while(getline(is, line)){
        list<int> ld;
        stringstream ls(line);
        int val1,val2;
        while(ls>>val1>>val2){
            if(reverse){
                al[val2-1].push_back(val1-1);
            } else {
                al[val1-1].push_back(val2-1); 
            }
        }
    }
}


int t=-1;
int s=-1;
void vanilaDFS(vector< vector<int> >& al, int index, vector<bool>& visited, bool reverse, int& count){
    if(!reverse) count++;
    visited[index]= true;
    lvec[index] = s;
    for(int i=0; i<al[index].size(); i++){
        if(!visited[al[index][i]]){
            vanilaDFS(al, al[index][i], visited, reverse, count);
        }
    }

    if(reverse){
        t++;
        ftvec[t] = index;
    }
}


void dfsLoop(vector< vector<int> >& al, bool reverse){
    int nnodes = al.size();
    vector<bool> expvec(nnodes, false);
    for(int i=nnodes-1; i>= 0; i--){
        int index;
        if(reverse) index = i;
        else index = ftvec[i];
        if(!expvec[index]){
            int count=0;
            s=index;
            vanilaDFS(al, index, expvec, reverse, count);
            if(!reverse && count>0) scccnt.push_back(count);
        }
    }
}

void processGraph(vector<int>& lvec, vector<int>& ftvec, bool rev, string fname, vector<int>& scccnt, int N){
    vector< vector<int> > grev(N);
    readDataIntoAl(grev, fname, rev);
    dfsLoop(grev, rev);
}

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

int main(void){
    string fname = "SCC.txt";

    processGraph(lvec, ftvec, true, fname, scccnt, N);
    //printVect(ftvec);
    cout<<"grev done"<<"\n";

    processGraph(lvec, ftvec, false, fname, scccnt, N);
    //printVect(lvec);
    sort(scccnt.begin(), scccnt.end(), myobject);
    printVect(scccnt);
    int cnt=0;
    for(int i=0; i<scccnt.size();i++){
        cnt += scccnt[i];
    }
    cout<<"\n"<<"total: "<<cnt<<"\n";
    return 0;
}