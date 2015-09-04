/*
 * =====================================================================================
 *
 *       Filename:  countInversions.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/04/2014 12:56:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ravish Mishra (), ravish.mishra@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef vector<int>::iterator vecIter;;

int getEleVecFromFile(vector<int>& inv, string fname){
    ifstream is(fname);
    if(!is) return 0;
    int value;
    while(is >> value){
        inv.push_back(value);
    }
    return 0;
}

void printVect(vector<int> sv){
    vector<int>::iterator viter;
    for(viter=sv.begin(); viter!=sv.end(); viter++){
        std::cout<<*viter;
    }
    std::cout<<'\n';
}

vector<int> countSplitInversions(vecIter left_begin, vecIter left_end, 
                                 vecIter right_begin, vecIter right_end , 
                                 vector<int>& A, int n, double* count){
    vector<int> B(left_begin, left_end);
    vector<int> C(right_begin, right_end);
    int j=0;
    int k=0;
    
    for(int i=0; i<n; i++){
        if(j<B.size() && k < C.size()){
            if(B[j] < C[k]){
                A[i] = B[j];
                ++j;
            } else {
                A[i] = C[k];
                ++k;
                *count+= B.size()-j;
            }
        } else if(k >= C.size()) {
           if(j < B.size()){
                A[i] = B[j];
                ++j;
           } else break; 
        } else {
            if(k < C.size()){
                A[i] = C[k];
                ++k;
            } else break;
        }
    }
    cout<<"inside count and split"<<"\n";
    printVect(A);
    return A;
}

vector<int> countAndSort(vector<int>& A, int n, double* count){
    if(n==1) return A;
    int x=0;
    int y =0;
    int z=0;
    int mid = (n+1)/2;
    vector<int> B(A.begin(), A.begin()+mid);
    vector<int> C(A.begin()+mid, A.end());
    countAndSort(B, B.size(), count);
    countAndSort(C, C.size(), count);
    A = countSplitInversions(B.begin(), B.end(), C.begin(), C.end(), A, n, count);
    return A;
}


int main(void){
    double count=0;
    vector<int> v{5 ,3, 8, 9, 1, 7, 0, 2, 6, 4};
    //getEleVecFromFile(v, "IntegerArray.txt");
    vector<int> sv=countAndSort(v, v.size(), &count);
    //printVect(sv);
    std::cout<<v.size();
    std::cout<<'\n';
    std::cout<<std::fixed<<count;
    std::cout<<'\n';
    return 0;
}
