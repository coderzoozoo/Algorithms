/*
 * =====================================================================================
 *
 *       Filename:  QuickSort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/30/2015 17:13:39
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


using namespace std;

void swap(int& a, int& b){ 
    int tmp = a;
    a = b;
    b = tmp;
}

int median(vector<int>& A, int i, int j, int k){
    int max;
    max = i;
    if(A[j]> A[max]) max = j;
    if(A[k] > A[max]) max = k;


    int median;
    if(max == i){
        if(A[j] > A[k]) median = j;
        else median = k;
    } else if(max == j){
        if(A[i]> A[k]) median = i;
        else median = k;
    } else {
        if(A[i] > A[j]) median = i;
        else median = j;
    }
    return median;
}

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
    for(int i=0; i< sv.size(); i++){
        cout<<sv[i]<<"\t";
    }
    std::cout<<'\n';
}


int partition(vector<int>& A, int p, int r, int& count){
    //int mid = (p+r)/2;
    //swap(A[p], A[median(A, p, mid, r)]);
    //swap(A[p], A[r]);
    count+= r-p;
    int x = A[p];
    int i = p + 1;
    for(int j=p+1; j <= r; j++){
        if(A[j] < x){
            swap(A[i], A[j]);
            i = i+1;
        }
    }
    swap(A[p], A[i-1]);
    return i-1;

}

void quickSort(vector<int>& A, int p, int r, int& count){
    if(p < r) {
        int q = partition(A,p,r,count);
        //printVect(A);
        quickSort(A, p, q-1, count);
        quickSort(A, q+1, r, count);
    }
}


int main(void){
    //vector<int> A {13,19,9,5,12,8,7,4,11,2,6,21};
    //vector<int> B {8,2,4,5,7,1};
    //cout<<median(B, 0, 2, 5);
    
    vector<int> A;
    getEleVecFromFile(A, "QuickSort.txt");
    cout<<"Size: "<<A.size()<<"\n";
    int count  = 0;
    quickSort(A, 0, A.size()-1, count);
    //cout<<"\n********Sorted Array*****************\n";
    cout<<"No of comparisons:"<<fixed<<count<<"\n";
    //printVect(A);
   
    return 0;
}


