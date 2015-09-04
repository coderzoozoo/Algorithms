/*
 * =====================================================================================
 *
 *       Filename:  optimalBST.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2015 18:57:53
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

const int INF = std::numeric_limits<int>::max(); 
using namespace std;

int optimalBST(vector<float>& f, int N){
    vector< vector<float> > A(N, vector<float>(N));

    for(int i=0; i<N;i++)
        A[i][i] = f[i];

    for(int s=2; s<=N ; s++){
        for(int i=0; i< N-s+1; i++){
            int j = i + s -1; 
            float min = INF;
            float sumfq = 0;

            for(int k=i; k<=j; k++){
               sumfq += f[k]; 
            }
            //cout<<sumfq<<"\n";
            for(int r=i; r<=j; r++){
                cout<<i<<"\t"<<r<<"\t"<<j<<"\t"<<s<<"\n";
                float a = (i>r-1) ? 0 : A[i][r-1];
                float b = ((r+1) > j) ? 0 : A[r+1][j];
                float cost = sumfq + a + b;
                min = (min < cost)? min: cost;
            }
            cout<<min<<"\t"<<i<<"\t"<<j<<"\n";
            A[i][j] = min; 
        }
    }

    cout<<"sol : "<<std::fixed<<A[0][N-1]<<"\n";
    return A[0][N-1];
}

int main(void){
    vector<float> f{0.2, 0.05, 0.17, 0.1, 0.2, 0.03, 0.25};
    int N = 7;
    cout<<optimalBST(f, N)<<"\n";
    return 0;
}

