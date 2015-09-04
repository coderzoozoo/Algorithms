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

int solveKnapsack(vector<item>& iv, int W, int N){
    vector< vector<int> > A(N+1, vector<int>(W+1));
    for(int i=0; i< W; i++){
        A[0][i] = 0;
    }
    for(int i=1; i< (N+1); i++){
        for(int j=0; j< W + 1; j++){
            if (j < iv[i].wt){
                A[i][j] = A[i-1][j];
            } else {
                A[i][j] = (A[i-1][j] > (A[i-1][(j-iv[i].wt)] + iv[i].val)) ? A[i-1][j] : (A[i-1][(j-iv[i].wt)] + iv[i].val); 
            }
        }
    }
    return A[N][W];
}

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
