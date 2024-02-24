#include <bits/stdc++.h>
using namespace std;




int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, x;
    pair<string, vector<vector<int>>> tmp;
    int rez = 0;
    cin>>n;
    vector<pair<string, vector<vector<int>>>> igraci;
    vector<vector<int>> resenje;
    vector<int> nule (11, 0);
    vector<bool> gotov(n, false);
    for(int q=0; q<n; q++)
    {

    cin>>tmp.first;
        vector<vector<int>> tp;
    
    for(int i=0; i<5; i++){
        vector<int> t;
        for(int j=0; j<5; j++){
            cin>>x;
            t.push_back(x);
        }
        tp.push_back(t);
    }
    resenje.push_back(nule);
    tmp.second = tp;
    igraci.push_back(tmp);
    }
    


    cin>>m;
    for(int q=0; q<m; q++){

    cin>>x;
    for(int i=0; i<n; i++){

        if(gotov[i] == false){

       
        for(int j=0; j<5; j++){
            for(int p = 0; p<5; p++){
                
                if(igraci[i].second[j][p] == x){
                    resenje[i][j]++;
                    resenje[i][p+6]++;
                    if(j==p) resenje[i][5]++;
                    if(j + p == 4) resenje[i][11]++;
                    
                    if((resenje[i][5] == 5) || (resenje[i][11] == 5) || (resenje[i][p+6] ==5) || (resenje[i][j] == 5))
                    {
                   
                    rez++; 
                    j=5; p = 5; 
                    gotov[i] = true;
                    }

                }
            }
        }
    

        }
    }
    }    
    

    if(rez == 0) cout<<0;
    else{
        cout<<rez<<endl;
        for(int i=0; i<n; i++){
            if(gotov[i] == true) cout<<igraci[i].first<<endl;
        }
    }
    
    }