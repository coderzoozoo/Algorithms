/*
 * =====================================================================================
 *
 *       Filename:  clustering.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2015 11:14:04
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
#include <set>
#include <unordered_map>

using namespace std;
const int INF = numeric_limits<int>::max();

void remove_duplicate2(vector<int>& vec) {
    std::set<int> s(vec.begin(), vec.end());
    vec.assign(s.begin(), s.end());
}


void readInputFile(unordered_map<int, int>& nmap, string fname, int& N, int& bits){
    //vector<int> v;
    ifstream is(fname);
    if(!is) exit(1);

    int count = 1;
    int idx = 0;
    string line;
    while(getline(is, line)){
        stringstream ls(line);
        if(count > 0){
            ls>>N>>bits;
            cout<<N<<"\t"<<bits<<"\n";
            count--;
        } else {
            int val;
            int tmp = 0;
            int cnt = 0;
            while(ls>>val){
                tmp |= (val<<cnt);
                //if (cnt < bits - 1) tmp = tmp<<1;
                cnt++;
            }
            if(nmap.find(tmp) == nmap.end()){
      //          v.push_back(tmp);
                nmap[tmp]= idx;
                idx++;
            }
        }
    }
    //remove_duplicate2(v); 
    cout<<nmap.size()<<"\t"<<idx<<"\n";
}
int pop(unsigned x)
{
    int cnt=0;
    for(int i=0; i<24; i++){
        if((x>>i)&0x1){
            cnt++;
        }
    }
    return cnt;
}


int distance(int a, int b){
    unsigned int x = a^b;
    return pop(x); 
}

inline int find(vector<int>& lv, int n ){
    int l = n;
    while(lv[l] != l){
        l = lv[l];
    }
    return l;
}

inline void clusterUnion(vector<int>& lv, int n1, int n2){
    lv[n1] = n2;
}

void initLeaders(vector<int>& lv, int N){
    for(int i=0; i< N; i++){
        lv[i]=i;
    }
}

void printLeaders(vector<int>& lv, int n){
    for(int i=0; i<n; i++){
        cout<<lv[i]<<"\n";
    }
}
/* Takes a vector of nodes as input. Outputs k clusters */
int findK(unordered_map<int, int>& nmap){
    vector<int> lv(nmap.size(), 0);
    int num_clust = nmap.size();
    cout<<"size: "<<num_clust<<"\n";
    initLeaders(lv, nmap.size());
    for(auto it=nmap.begin(); it != nmap.end(); it++){
        int pivot = it->first;
        if(num_clust % 1000 == 0 || num_clust < 9000 ) cout<<num_clust<<"\n";
        //cout<<"pivot: "<<pivot<<"\n";
        vector<int> edgelist;
        //edgelist.push_back(pivot);
        for(int j =0; j < 24; j++){
            int tmp = pivot;
            //cout<<"distance tmp: "<<distance(tmp, pivot)<<"\n";
            tmp ^= (1 << j);
            edgelist.push_back(tmp);
            for(int k=j+1; k <24; k++){
                int tmp1 = tmp;
                tmp1 ^= (1 << k);
                edgelist.push_back(tmp1);
            }
        }
        for(int k=0; k<edgelist.size(); k++){
            if(nmap.find(edgelist[k]) != nmap.end()){
                //cout<<"distance: "<<distance(edgelist[k], pivot)<<"\n";
                int l1 = find(lv, nmap[pivot]);
                int l2 = find(lv, nmap[edgelist[k]]);
                if(l1 != l2){
                    clusterUnion(lv, l1, l2);
                    num_clust--;
                }
            }
        }
    } 
    return num_clust;
}

int main(void){
    int N, bits;
    string fname = "clustering_big.txt";
    unordered_map <int, int> nmap;
    readInputFile(nmap, fname, N, bits);
    int cnt = 0;
    cnt = findK(nmap);
    cout<<"Number of clusters: "<<cnt<<"\n";
    
}
