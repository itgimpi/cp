#include <bits/stdc++.h>

using namespace std;


void dfs(int c, int preth,vector<vector<int>> &veze, vector<pair<int, int>> &maks, int i){
    for(int s : veze[c]){
        if(s != preth){
        dfs(s, c, veze, maks, i+1);
        maks[s].first = i; //dfs algoritam koji kada prodje cvor meri broj veza izmedju cvorova od pocetka
        }
    }

}


int main(){
    
    ios_base::sync_with_stdio(false);
    int n; cin>>n;
    vector<vector<int>> veze(n+1);
    vector<pair<int,int>> maks(n+1); //maks niz koji se koristi za prvi dfs
    vector<pair<int, int>> maks2(n+1);//maks niz koji se koristi za drugi dfs

    for(int i=0; i<n+1; i++){
        maks[i].first = 0;
        maks[i].second= i;
        maks2[i].first = 0;
        maks2[i].second= i;
    }
    int naj;
    for(int i=1; i<n; i++){
        int u, v; cin>>u>>v;
        veze[u].push_back(v);
        veze[v].push_back(u);
    }
    dfs(1, 0, veze, maks, 1 ); //1. dfs od elementa 1 da bi pronasli najdalji element
    sort(maks.begin(),maks.end());//sortira se vector parova jer se na n+1 elementu nalazi najdalji.
    dfs(maks[n].second,0, veze, maks2, 1); // 2. dfs od najdaljeg elementa od 1, da bi nasli pravi najdalji element
    sort(maks2.begin(), maks2.end()); //sortira se maks2 da bi zadnji element bio najveci
    cout<<maks2[n].first; 


}