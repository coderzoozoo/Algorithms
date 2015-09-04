/*
 * =====================================================================================
 *
 *       Filename:  finput.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/20/2015 19:08:10
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
#include <sstream>
#include <vector>
#include <list>

using namespace std;

int main(void){
    ifstream is("test.txt");
    if(!is) return 0;
    string line;
    while(getline(is, line)){
        stringstream ls(line);
        int v1, v2;
        while(ls>>v1>>v2){
            cout<<v1<<"\t"<<v2<<"\n";
            vector<int> x(4);
            cout<<"size:"<<x.size()<<"\n";
        }
    }
    return 0;
}
