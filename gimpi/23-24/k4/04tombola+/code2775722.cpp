#include <bits/stdc++.h>

using namespace std;
int a[50][5][5];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n; cin >> n;
    vector<string> ime(n);
    for(int i = 0; i < n; i++){
        cin >> ime[i];
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                cin >> a[i][j][k];
            }
        }
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }
    vector<string> res;
    int res1 = 0;
    sort(b.begin(),b.end());
    for(int i = 0; i < n; i++){
        vector<vector<bool>> pro(5,vector<bool>(5));
        bool da = false;
        for(int j = 0; j < 5; j++){
            bool red = true;
            for(int k = 0; k < 5; k++){
                if(binary_search(b.begin(),b.end(),a[i][j][k])){
                    pro[j][k] = true;
                }
                else{ pro[j][k] = false;
                    red= false;}
            }
            if(red){
                da = true;
                break;
            }
        }
        if(da){
            res.push_back(ime[i]);
            res1++;
        }
        else{
            for(int j = 0; j < 5; j++){
            bool kolona = true;
            for(int k = 0; k < 5; k++){
                if(pro[k][j] == false){
                    kolona = false;
                    break;
                }
                
            }
            if(kolona){
                da = true;
                break;
            }
        }

        
        if(da){
            res.push_back(ime[i]);
            res1++;
        }
        else{
            bool dijagonala = true;
            for(int j = 0,k = 0; j < 5 and k < 5; j++, k++){
                if(pro[j][k] == false){
                    dijagonala = false;
                    break;
                }
            }
            if(dijagonala){
                da = true;
            }
            else{
                dijagonala = true;

            
            for(int j = 0,k = 4; j < 5 and k >= 0; j++, k--){
                if(pro[j][k] == false){
                    dijagonala = false;
                    break;
                }
                
        }
        if(dijagonala) da = true;}

    
        if(da){
            res.push_back(ime[i]);
            res1++;
        }}}}
    cout << res1 << '\n';
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << '\n';
    }

    return 0;
}