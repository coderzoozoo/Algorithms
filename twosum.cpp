/*
 * =====================================================================================
 *
 *       Filename:  twosum.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/08/2015 12:51:12
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
#include <list>
#include <limits>
#include <sstream>
#include <fstream>
#include <string>
#include <random>
#include <functional>
#include <cmath>


using namespace std;

void readFileIntoVector(vector<long int>& numvec, string fname){
    ifstream is(fname);
    if(!is){
        cout<<"no input stream found"<<"\n";
        return;
    }
    long int  val;
    while(is>>val){
        numvec.push_back(val);
    }

}

int generatePrimeNumber(long int x){
    for(long int i = x; i > 1; i--){
        bool isprime = true;
        for(long int j =2; j < sqrt(i); j++){
           if(i == (i/j)*j) isprime = false;
        }
        if(isprime) return i;
    }
}


int hashfunction(long int x, long int htsize){
    long int val = (x<0)? -x: x;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,htsize);
    gen.seed(val);
   
    return (val + dis(gen)) % htsize;
}

void createHashTable(vector< vector<long int> >& ht, vector<long int>& numvec ){
    int htsize = ht.size();
    int cnt=0;
    for(int i=0; i< numvec.size(); i++){
        //int index = hashfunction(numvec[i], htsize);
        int index = ((numvec[i] < 0)? -numvec[i]: numvec[i])%htsize; 
        bool found = false;
        for(int j=0; j < ht[index].size(); j++){
            if(ht[index][j]==numvec[i]) {
                found = true;
                cnt++;
                break;
            }
        }
        if(!found) ht[index].push_back(numvec[i]);
    }
    cout<<"Hash table created: "<<cnt<<"\n";
}

bool lookup(vector< vector<long int> >& ht, long int x){
    //int index = hashfunction(x, ht.size());
    int index = ((x < 0)? -x: x) % ht.size(); 
    for(int i=0; i < ht[index].size(); i++){
        if(ht[index][i] == x) return true;
    }
    return false;
}


int main(void){
    vector<long int> inpvec;
    readFileIntoVector(inpvec, "2sum.txt");
    cout<<"size of vec: "<<inpvec.size()<<"\n";
    int N = generatePrimeNumber(2000000); 
    cout<<"N: "<<N<<"\n";
    vector< vector<long int> > ht(N);
    createHashTable(ht, inpvec);
    int count=0;
    for(int t=-10000; t<=10000; t++){
        cout<<"target: "<<t<<"\n";
        for(int i = 0; i< inpvec.size(); i++){
            long int x = inpvec[i];
            long int y = t - x;
            if(x != y && lookup(ht, y)){
                count++;
                break;
            }

        }
    }
    cout<<"answer = "<<count<<"\n";
    return 0;
}
