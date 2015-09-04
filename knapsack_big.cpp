/*
 * =====================================================================================
 *
 *       Filename:  knapsack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2015 16:04:05
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
#include <sstream>

using namespace std;
typedef struct item{
    int val;
    int wt;
}item;


void readInput(vector<item>& iv, int& N, int& W, string fname){
    ifstream is(fname);
    if(!is) exit(1);

    string line;
    int count = 1;
    while(getline(is, line)){
        stringstream ls(line);
        if(count > 0){
            ls>>W>>N;
            count--;
        }else {
            int v, w;
            ls>>v>>w;
            item tmp;
            tmp.val = v;
            tmp.wt = w;
            iv.push_back(tmp);
        }
    }
}
void printV(vector<item>& iv){
    for(int i=0; i<iv.size(); i++){
        cout<<iv[i].val<<"\t"<<iv[i].wt<<"\n";
    }
}

int solveKnapsack(vector<item>& iv, int& W, int& N){
    vector<int> A(W+1, 0);
    for(int i=1; i< (N+1); i++){
        if(i%100 ==0) cout<<i<<"\n";
        vector<int> B(W+1, 0);
        for(int j=0; j< W + 1; j++){
            if (j < iv[i].wt){
                B[j] = A[j];
            } else {
                B[j] = (A[j] > (A[(j-iv[i].wt)] + iv[i].val)) ? A[j] : (A[(j-iv[i].wt)] + iv[i].val); 
            }
        }
        A.assign(B.begin(), B.end());
    }
    return A[W];
}

typedef struct score{
    int top;
    int middle;
    int bottom;
}score;


int main(void){
    vector<item> iv;
    int N, W;
    readInput(iv, N, W, "knapsack1.txt");

    //readInput(iv, N, W, "test.txt");
    cout<<N<<"\t"<<W<<"\n";
//    printV(iv);
    cout << "Optimal Sol: "<<solveKnapsack(iv, W, N)<<"\n";
    return 0;
}
