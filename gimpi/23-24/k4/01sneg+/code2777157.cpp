#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    char a[n][m];
    int br=0;
    vector<pair<int,int>> poz;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> a[i][j];
            if (a[i][j]=='+') {
                br++;
                poz.push_back(make_pair(i,j));}
        }
    }
    int maxi=0;
    for(int i=0; i<br; i++){
        
            int levici =poz[i].first;
            int levj=poz[i].second-1;
            int levgi=poz[i].first-1;
            int levdi=poz[i].first+1;

            int cenj=poz[i].second;
            int cengi=poz[i].first-1;
            int cendi=poz[i].first+1;

            int desnci =poz[i].first;
            int desnj=poz[i].second+1;
            int desngi=poz[i].first-1;
            int desndi=poz[i].first+1;
            int nmax=0;
        while(1){

            if(levj<0  || levgi<0 || levdi > n || cengi<0 || cendi> n || desnj>m || desngi<0 || desndi>n)
                break;
            if (a[levici][levj]=='-' && a[levgi][levj]=='\\' && a[levdi][levj]=='/' && a[cengi][cenj]=='|' && a[cendi][cenj]=='|' && a[desnci][desnj]=='-' && a[desndi][desnj]=='\\' && a[desngi][desnj]=='/'){
                nmax++;
                levj--; levgi--; levdi++; cengi--; cendi++; desnj++; desngi--; desndi++;   
            }
            else break;
            maxi=max(nmax,maxi);

        }
    }
    cout << maxi;
return 0;}