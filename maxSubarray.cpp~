/*
 * =====================================================================================
 *
 *       Filename:  maxSubarray.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2014 13:15:57
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
#include <cmath>

using namespace std;
typedef vector<int>::iterator vecIter; 
typedef struct arrayParams{
    int low;
    int high;
    double sum;
}ap;


ap findMaxCrossingArray(vector<int>& A, int high, int  mid, int low){
    long int sum = 0;
    double left_sum = -INFINITY;
    int max_left=mid;
    for(int i=mid; i>=low; i--){
        sum += A[i];
        if (sum > left_sum){
            left_sum = sum;
            max_left = i;
        }
    }
    sum=0;
    double right_sum = -INFINITY;
    int max_right=mid;
    for(int i=(mid+1);i<=high;i++){
        sum += A[i];
        if (sum > right_sum){
            right_sum = sum;
            max_right = i;
        }
    }
    ap mca;
    mca.low = max_left;
    mca.high = max_right;
    mca.sum = left_sum + right_sum;
    return mca;
}


ap findMaxSubarray(vector<int>& A, int high, int low){
    if(high==low){
        ap msa;
        msa.low=low;
        msa.high=low;
        msa.sum=A[low];
        return msa;
    } else{
        int mid = (high+low)/2; 
        ap leftmsa, rightmsa, crossmsa;
        leftmsa = findMaxSubarray(A, mid, low);
        rightmsa = findMaxSubarray(A, high, mid+1);
        crossmsa = findMaxCrossingArray(A, high, mid, low);
        if(leftmsa.sum >= rightmsa.sum && leftmsa.sum >= crossmsa.sum) return leftmsa;
        else if(rightmsa.sum >= leftmsa.sum && rightmsa.sum >= crossmsa.sum) return rightmsa;
        else return crossmsa;
    }
}

ap linearMaxsubarray(vector<int>& A, int high, int low){
    long int sum = 0;
    double maxsum = -INFINITY;
    int left = low;
    int maxleft = low;
    int maxright = high;
    for(int i=low; i <= high; i++){
        sum += A[i];
        if (sum < 0){
            sum = 0;
            left = i+1;
        } else if (sum > maxsum){
            maxsum = sum;
            maxright = i;
            maxleft = left;
        } 
    }
    ap maxsa;
    maxsa.low = maxleft;
    maxsa.high = maxright;
    maxsa.sum = maxsum;
    return maxsa;

}

void printMaxSubarray(const ap msa){
    cout<<"low:";
    cout<<msa.low<<'\t';
    cout<<"high:";
    cout<<msa.high<<'\t';
    cout<<"sum:";
    cout<<msa.sum<<'\t';
    cout<<'\n';
}

int main(void){
    vector<int> v{-2, -3, 4, -1, -2, 1, 5, -3};
    ap msa = linearMaxsubarray(v,v.size()-1, 0); 
    printMaxSubarray(msa);
    ap rmsa = findMaxSubarray(v,v.size()-1, 0);
    printMaxSubarray(rmsa);
}

