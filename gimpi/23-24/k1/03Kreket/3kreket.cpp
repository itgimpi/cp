#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m, rez = 0;
    int k=0, r=0, e=0, t=0;
    int temp, maks= 0;
    char c;
    cin>>n>>m;
    for(int i = 0; i<n; i++){
        cin>>c;
        if(c == 'k') k++;
        if(c == 'r') r++;
        if(c == 'e') e++;
        if(c == 't') t++;
    }
   
    
    for(int K=0; K<=m; K++){
    for(int R=0; K+R<=m; R++){
        for(int E=0; K+R+E <=m; E++){
            for(int T=0; K+R+E+T<=m; T++){
                temp = min(min((k+K)/2,(e+E)/2), min( r+R, t+T));
                rez= ((k+K)*(k+K) + (r+R)*(r+R)+ (e+E)*(e+E)+ (t+T)*(t+T));
                
                if(rez+ temp*7 > maks)
                    maks = rez+temp*7;
            }}}}
    cout<<maks ;



    return 0;
}