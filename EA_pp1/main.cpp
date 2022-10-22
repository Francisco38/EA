#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#define MAX_SIZE 50

using namespace std;
int found=0;

int val[1000];
int matriz[MAX_SIZE*2][MAX_SIZE*2]={};
unordered_map<int,vector<int>> piecesMap;
unordered_map<int,vector<int>> piecesMapTrio;
vector<int> pieces;

int find_solution(int x,int y,int c,int l);

void print_solution(int c,int l){
    for(int x=0;x<c;x++){
        for(int y=0;y<l;y++){
            cout<<matriz[x][y];
            if(y<l-1){
                cout<<" ";
            }
            if(y%2==1 && y<l-1) {
                cout<<" ";
            }
        }
        cout<<endl;
        if(x%2==1 && x<c-1) {
            cout<<endl;
        }
    }
}

int fit_left(int x,int y){
    int a,b;
    a=matriz[x][y-1];
    b=matriz[x+1][y-1];
    return b+a*1000;
}

int fit_top(int x,int y){
    int a,b;
    a=matriz[x-1][y];
    b=matriz[x-1][y+1];
    return a+b*1000;
}

int fit(int x,int y){
    int a,b,c;
    a=matriz[x-1][y];
    b=matriz[x-1][y+1];
    c=matriz[x+1][y-1];
    return a+b*1000+c*1000000;
}

void place_piece(int x,int y,int r,int v1,int v2,int v3,int v4){
    if(r==-1) {
        r = 3;
    }

    if(r==0){
        matriz[x][y]=v1;
        matriz[x+1][y+1]=v3;
        matriz[x+1][y]=v4;
        matriz[x][y+1]=v2;
    }
    else if(r==1){
        matriz[x][y]=v4;
        matriz[x+1][y+1]=v2;
        matriz[x+1][y]=v3;
        matriz[x][y+1]=v1;
    }
    else if(r==2){
        matriz[x][y]=v3;
        matriz[x+1][y+1]=v1;
        matriz[x+1][y]=v2;
        matriz[x][y+1]=v4;
    }
    else if(r==3){
        matriz[x][y]=v2;
        matriz[x+1][y+1]=v4;
        matriz[x+1][y]=v1;
        matriz[x][y+1]=v3;
    }

}

int find_solution(int x,int y,int c,int l){
    int v1,v2,v3,v4,type;
    vector<int> value_set;

    if(y>=c){
        y=0;
        x=x+2;
        if(x>=l){
            found=1;
            return 0;
        }
    }
    if(x==0 ){
        type=0;
        value_set=piecesMap[fit_left(x,y)];
    }
    else if(y==0){
        type=1;
        value_set=piecesMap[fit_top(x,y)];
    }
    else{
        type=2;
        value_set=piecesMapTrio[fit(x,y)];
    }

    for (int i = 0; i < (int)value_set.size(); i=i+2)
    {
        int index=value_set[i];
        v1=pieces[index];
        v2=pieces[index+1];
        v3=pieces[index+2];
        v4=pieces[index+3];
        int rotate=value_set[i+1];
        if(pieces[index+4]==0){
            pieces[index+4]=1;
            if(type==0){
                place_piece(x,y,rotate-1,v1,v2,v3,v4);
            }
            else{
                place_piece(x,y,rotate,v1,v2,v3,v4);
            }
            if(find_solution(x,y+2, c, l)==0){
                return 0;
            }
            else{
                pieces[index+4]=0;
            }
        }
    }
    return 1;
}

void addmap(int v1,int v2,int v3,int v4,int index){
    int find=v1+v2*1000;
    vector<int> tempVector={index};
    if(piecesMap.find(find)!=piecesMap.end()){
        piecesMap[find].push_back(index);
        piecesMap[find].push_back(0);
    }
    else{
        piecesMap[find]=tempVector;
        piecesMap[find].push_back(0);
    }

    find=v2+v3*1000;
    if(piecesMap.find(find)!=piecesMap.end()){
        piecesMap[find].push_back(index);
        piecesMap[find].push_back(3);
    }
    else{
        piecesMap[find]=tempVector;
        piecesMap[find].push_back(3);
    }


    find=v3+v4*1000;
    if(piecesMap.find(find)!=piecesMap.end()){
        piecesMap[find].push_back(index);
        piecesMap[find].push_back(2);
    }
    else{
        piecesMap[find]=tempVector;
        piecesMap[find].push_back(2);
    }

    find=v4+v1*1000;
    if(piecesMap.find(find)!=piecesMap.end()){
        piecesMap[find].push_back(index);
        piecesMap[find].push_back(1);
    }
    else{
        piecesMap[find]=tempVector;
        piecesMap[find].push_back(1);
    }


    find=v1+v2*1000+v4*1000000;
    if(piecesMapTrio.find(find)!=piecesMapTrio.end()){
        piecesMapTrio[find].push_back(index);
        piecesMapTrio[find].push_back(0);
    }
    else{
        piecesMapTrio[find]=tempVector;
        piecesMapTrio[find].push_back(0);
    }

    find=v3+v4*1000+v2*1000000;
    if(piecesMapTrio.find(find)!=piecesMapTrio.end()){
        piecesMapTrio[find].push_back(index);
        piecesMapTrio[find].push_back(2);
    }
    else{
        piecesMapTrio[find]=tempVector;
        piecesMapTrio[find].push_back(2);
    }

    find=v4+v1*1000+v3*1000000;
    if(piecesMapTrio.find(find)!=piecesMapTrio.end()){
        piecesMapTrio[find].push_back(index);
        piecesMapTrio[find].push_back(1);
    }
    else{
        piecesMapTrio[find]=tempVector;
        piecesMapTrio[find].push_back(1);
    }

    find=v2+v3*1000+v1*1000000;
    if(piecesMapTrio.find(find)!=piecesMapTrio.end()){
        piecesMapTrio[find].push_back(index);
        piecesMapTrio[find].push_back(3);
    }
    else{
        piecesMapTrio[find]=tempVector;
        piecesMapTrio[find].push_back(3);
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n_cases,n,col,lin,a,b,c,d;
    for(int t=0;t<1000;t++){
        val[t]=0;
    }

    cin>>n_cases;
    for(int i=0;i<n_cases;i++){
        cin>>n;
        cin>>lin;
        cin>>col;
        cin>>a;
        val[a]++;
        cin>>b;
        val[b]++;
        cin>>c;
        val[c]++;
        cin>>d;
        val[d]++;
        matriz[0][0]=a;
        matriz[0][1]=b;
        matriz[1][0]=d;
        matriz[1][1]=c;
        for(int x=0;x<n-1;x++){
            cin>>a;
            cin>>b;
            cin>>c;
            cin>>d;
            addmap(a,b,c,d,x*5);
            val[a]++;
            val[b]++;
            val[c]++;
            val[d]++;

            pieces.push_back(a);
            pieces.push_back(b);
            pieces.push_back(c);
            pieces.push_back(d);
            pieces.push_back(0);
        }

        int num_impar=0;
        int imp_par=0;
        for(int t=0;t<1000;t++){
            if(val[t]%2==1){
                num_impar++;
            }
            val[t]=0;
        }
        if(num_impar<=4){
            if(imp_par<=(lin+col)*2){
                find_solution(0,2,col*2,lin*2);
            }
        }
        if(found==0){
            cout<<"impossible puzzle!"<<endl;
        }
        else{
            print_solution(lin*2,col*2);
        }
        piecesMap.clear();
        piecesMapTrio.clear();
        pieces.clear();
        found=0;
    }
    return 0;
}