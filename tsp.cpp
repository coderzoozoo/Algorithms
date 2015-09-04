/*
 * =====================================================================================
 *
 *       Filename:  tsp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/29/2015 12:08:16
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
#include <sstream>
#include <limits>
#include <cmath>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

const int INF = std::numeric_limits<int>::max();

typedef struct location{
    float x;
    float y;
}loc;

void readData(vector<loc>& lv, int& N, string fname){
    ifstream is(fname);
    if(!is) exit(1);

    string line;
    int count = 1;
    while(getline(is, line)){
        stringstream ls(line);
        if(count > 0){
            ls>>N;
            count--;
            //cout<<N<<"\n";
        }else{
            loc tmp;
            ls>>tmp.x>>tmp.y;
            lv.push_back(tmp);
        }
    }
}

void printV1(vector<loc>& lv){
    for(int i=0; i<lv.size(); i++){
        cout<<i<<"\t"<<lv[i].x<<"\t"<<lv[i].y<<"\n";
    }
}

void printMatrix(vector<vector<float>>& dm, int N){
    for(int i=0; i<N; i++){
        for(int j=0; j< N; j++){
            cout<<dm[i][j]<<"\t"; 
        }
        cout<<"\n";
    }    
}

void distMatrix(vector<loc>& lv, vector<vector<float>>& dm, int N){
    for(int i=0; i<N; i++){
        for(int j=0; j< N; j++){
            dm[i][j] = sqrt(pow(lv[i].x-lv[j].x, 2) + pow(lv[i].y-lv[j].y,2));
        }
    }    
}

void printSv(vector<vector<int>>& sv, int N){
    for(int i =0; i< N; i++){
        for(int j=0; j<sv[i].size(); j++){
            cout<<sv[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

int choose(int n, int k){
    if(k == 0) return 1;
    return (n * choose(n - 1, k - 1)) / k;
}

typedef struct pg {
    int parent;
    int val;
    int min;
    int max;
}pg;

//void generateSet(vector<vector<int>>& sv, vector<vector<int>>& ev, int card, int max){
void generateSet(vector<vector<int>>& sv, int card, int max){
    vector<vector<pg>> p(card+1);
    pg tmp;
    tmp.parent = -1;
    tmp.val=0;
    tmp.min=1;
    tmp.max = max-1;
    p[0].push_back(tmp);

    int height=1;
    while(height < card){
        for(int j=0; j< p[height-1].size(); j++){
            int min = p[height-1][j].val + 1;       
            for(int k= min; k<max; k++){
                pg temp;
                temp.val=k;
                temp.parent = j;
                temp.min = k+1;
                temp.max = max-1;
                p[height].push_back(temp);

            }
        }
        height++;
    }
    height -=1;
    int j =0;
    for(int i=(p[height].size()-1); i >=0; i--){
        int h = height;
        pg t = p[height][i];
        sv[j].push_back(p[height][i].val);
        while(1){
            if(t.parent == -1) break;
            t = p[h-1][t.parent];
            sv[j].push_back(t.val);
            h--;
        }
        j++;
    }

}


typedef struct range{
    int start;
    int end;
}range;

float tsp(vector<vector<float>>& dm, int N){
    int numsets = pow(2, N-1);
    unordered_map<string, int> nmap;
    cout<<"numsets: "<<numsets<<"\n";
    vector<vector<float>> A(numsets, vector<float>(N));
    A[0][0] = 0; 
    for(int i=1;i< numsets; i++){
        A[i][0] = INF;
    }

    vector<range> map(N+1);
    map[0].start= 0;
    map[0].end = 0;
    map[1].start=0;
    map[1].end=0;
 
    int s = 2;
    for(int i=2; i<=N; i++){
        int nset = choose(N-1,s-1); 
        map[i].start= map[i-1].end + 1;
        map[i].end = map[i].start + nset -1;
        //cout<<i<<"\t"<<map[i].start<<"\t"<<map[i].end<<"\n";
        s++;
    }
    nmap[to_string(0)] = 0;

    for(int m=2; m<=N; m++){
        cout<<"m: "<<m<<"\n";
        int nset = choose(N-1,m-1); 
        //cout<<"nset: "<<nset<<"\n";
        vector<vector<int>> sv(nset);
        generateSet(sv, m, N);
        //printSv(sv, nset);
        for(int i=0; i< nset; i++){
            string s1;
            for(int j=0; j<sv[i].size(); j++){
                s1.append(to_string(sv[i][j]));
                if(sv[i][j] == 0) continue;
                vector<int> kv;
                string s;
                for(int k=0; k<sv[i].size(); k++){
                    //cout<<sv[i][k]<<"\t"<<sv[i][j]<<"\n";
                    if(sv[i][k]!=sv[i][j]){
                        kv.push_back(sv[i][k]);
                        s.append(to_string(sv[i][k]));
                    }
                }
                //cout<<s<<"\n";
                int setindex = nmap[s];
                //cout<<"setindex:"<<setindex<<"\n";
                float min = INF;
                for(int k=0; k<kv.size();k++){
                    //cout<<"kv[k]: "<<kv[k]<<"\t"<<sv[i][j]<<"\n";
                    float a = (A[setindex][kv[k]] == INF)? INF: A[setindex][kv[k]]  + dm[kv[k]][sv[i][j]];
                    min = (a < min)? a: min ; 
                }
                //cout<<map[m].start + i<<"\t"<<sv[i][j]<<"\t"<<min<<"\n";
                A[map[m].start + i][sv[i][j]] = min; 
            }
            nmap[s1] = map[m].start + i;
            //cout<<"s1: "<<s1<<"\t"<<nmap[s1]<<"\n";
        }
    }
    float minlentour = INF;
    for(int i=0; i<N; i++){
        float tmplen = A[numsets-1][i] + dm[i][0];
        //cout<<"mlt: "<<tmplen<<"\n";
        minlentour = (minlentour < tmplen)? minlentour: tmplen;
        /* 
        for(int j=0; j<A[numsets-1].size(); j++){
            cout<<A[numsets-1][j]<<"\t";
        }
        cout<<"\n";
 */
    }

    return minlentour;
}


void fillTestMatrix(vector<vector<float>>& tm){
    tm[0][0] = 0;
    tm[0][1] = 1;
    tm[0][2] = 6;
    tm[0][3] = 8;
    tm[0][4] = 4;


    tm[1][0] = 1;
    tm[1][1] = 0;
    tm[1][2] = 8;
    tm[1][3] = 5;
    tm[1][4] = 6;

    tm[2][0] = 6;
    tm[2][1] = 8;
    tm[2][2] = 0;
    tm[2][3] = 9;
    tm[2][4] = 7;

    tm[3][0] = 8;
    tm[3][1] = 5;
    tm[3][2] = 9;
    tm[3][3] = 0;
    tm[3][4] = 8;

    tm[4][0] = 4;
    tm[4][1] = 6;
    tm[4][2] = 7;
    tm[4][3] = 8;
    tm[4][4] = 0;
}

void fillTestMatrix1(vector<vector<float>>& tm){
    tm[0][0] = 0;
    tm[0][1] = 1;
    tm[0][2] = 4;
    tm[0][3] = 2;


    tm[1][0] = 1;
    tm[1][1] = 0;
    tm[1][2] = 6;
    tm[1][3] = 3;

    tm[2][0] = 4;
    tm[2][1] = 6;
    tm[2][2] = 0;
    tm[2][3] = 5;

    tm[3][0] = 2;
    tm[3][1] = 3;
    tm[3][2] = 5;
    tm[3][3] = 0;
}

int main(void){
    vector<loc> lv;
    int N;
    string fname = "tsp.txt";
    readData(lv, N, fname);
    //printV1(lv);
    vector<vector<float>> dm(N, vector<float>(N));
    distMatrix(lv, dm, N);
    //vector<vector<float>> dv(5, vector<float>(5));
    //fillTestMatrix(dv);
    float tl = tsp(dm, N);
    cout<<"Min Tour Length: "<<std::fixed<<tl<<"\n";
    //int nset = choose(3,2); 
    //vector<vector<int>> sv(nset);
    //generateSet(sv, 2, 4);
    //printSv(sv, nset);
    //printMatrix(dm, N);
    return 0;
}
