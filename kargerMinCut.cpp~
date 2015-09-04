/*
 * =====================================================================================
 *
 *       Filename:  kargerMinCut.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/12/2015 16:49:28
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
#include <sstream>
#include <random>
#include <limits>
#include <cmath>

using namespace std;

void readDataIntoAL(vector< list<int> >& al, string fname){
    ifstream is(fname);    
    if(!is) return;
    string line;
    while(getline(is, line)){
        int value;
        list<int> linedata;
        stringstream linestream(line);
        int count = 1;
        while(linestream >> value){
            if(0 == count) linedata.push_back(value - 1);
            else count -= 1;
        }
        al.push_back(linedata);
    }
}

void printGraph(vector< list<int> > al){
    for(int i=0; i<al.size(); i++){
        list<int>::iterator it;
        for(it=al[i].begin(); it != al[i].end(); it++){
            cout<<*it<<"\t";
        }
        cout<<"\n";
    }
}

int findMinCut(vector< list<int> > al){
    int nnode = al.size();
    int count = nnode;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,nnode-1);
    int node1 = -1;
    while(count > 2){
        do {
            node1 = dis(gen);
            //cout<<"node1: "<<node1<<"\t"<<al[node1].empty()<<"\n";
        } while(al[node1].empty());

        int node2 = -1;
        std::uniform_real_distribution<> dis1(0,al[node1].size()-1);
        list<int>::iterator it = al[node1].begin();
        std::advance(it, dis1(gen));
        node2 = *it;

        //cout <<"node1: "<<node1<<"\t"<<"node2: "<<node2<<"\n";

        al[node1].splice(al[node1].end(), al[node2]);
        //cout<<"is empty node 2: "<<al[node2].empty()<<"\n";
        al[node1].remove(node1);
        al[node1].remove(node2);
        for(int i = 0; i < al.size(); i++){
            list<int>::iterator  it;
            for(it = al[i].begin(); it != al[i].end(); it++){
                if((*it) == node2){

                    *it = node1;
                }
            }
        }
        count -= 1;
        //cout<<"============================="<<"\n";
        //printGraph(al);
    }
    return al[node1].size();
}

const int INF = std::numeric_limits<int>::max();

int main(void){
    vector< list<int> > gr;
    readDataIntoAL(gr, "kargerMinCut.txt"); 
    //printGraph(gr);
    int nnode = gr.size();
    int mincut = INF;
    int N = nnode*nnode*log(nnode);
    cout<<"N: "<<N<<"\n";
    N = 10000;
    for(int i=0; i < N; i++){
        int numcut = findMinCut(gr);
        if(numcut < mincut) mincut = numcut;
        if(i == ((i/100)*100)) cout<<i<<"\n";
    }
    cout<<"mincut: "<<mincut<<"\n";
    return 0;
}
