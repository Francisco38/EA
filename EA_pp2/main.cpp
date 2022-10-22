#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;
unordered_map<int, vector<int>> dic;
unordered_map<int, vector<int>> dic2;

void findBest(int n, int parrent_used){
    vector<int> rel1={0,0};
    vector<int> rel2={0,0};
    vector<int> temp3;
    vector<int> v=dic[n];
    rel1[0]=1;
    rel1[1]=v[v.size()-1];

    if(parrent_used==0){
        if(v.size()==1){
            dic2[n][2]=rel1[0];
            dic2[n][3]=rel1[1];
            return;
        }
        for(int i=0;i<(int)v.size()-1;i++){
            vector<int> v2= dic2[v[i]];
            if(v2[0]==-1){
                findBest(v[i],1);
            }
            v2= dic2[v[i]];
            rel1[0]+=v2[0];
            rel1[1]+=v2[1];
        }
        dic2[n][2]=rel1[0];
        dic2[n][3]=rel1[1];
    }
    else{
        if(v.size()==1){
            dic2[n][0]=rel2[0];
            dic2[n][1]=rel2[1];
            return;
        }
        for(int i=0;i<(int)v.size()-1;i++){
            vector<int> v2= dic2[v[i]];
            if(v2[0]==-1){
                findBest(v[i],1);
            }
            if(v2[2]==-1){
                findBest(v[i],0);
            }
            v2= dic2[v[i]];
            rel1[0]+=v2[0];
            rel1[1]+=v2[1];
            rel2[0]+=v2[2];
            rel2[1]+=v2[3];
        }
        if(rel1[0]<rel2[0]){
            dic2[n][0]=rel1[0];
            dic2[n][1]=rel1[1];
        }
        else if(rel1[0]>rel2[0]){
            dic2[n][0]=rel2[0];
            dic2[n][1]=rel2[1];
        }
        else{
            if(rel1[1]>rel2[1]){
                dic2[n][0]=rel1[0];
                dic2[n][1]=rel1[1];
            }
            else{
                dic2[n][0]=rel2[0];
                dic2[n][1]=rel2[1];
            }
        }
    }
}

int main() {
    string temp;
    while (getline(cin, temp)) {
        stringstream s(temp);
        vector<int> a;
        int n = 0;
        s >> n;
        if (n == -1) {
            findBest(0,1);
            vector<int> temp2 = dic2[0];
            cout <<temp2[0] << " " << temp2[1]<<endl;
            dic.clear();
            dic2.clear();
        } else {
            int x = 0;
            while (s >> x) {
                a.push_back(x);
            }
            dic[n] = a;
            dic2[n]={-1,-1,-1,-1};
        }
    }
    return 0;
}