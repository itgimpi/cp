#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    vector<vector<char>> a(n,vector<char>(m));
    vector<pair<int,int>> plu;
    int br = 0;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
            if(a[i][j]=='+'){
                br++;
                plu.push_back(make_pair(i,j));
            }
        }
    }
    int maks = 0;
    
    while(br--){
        
        bool pro = true;
        int temp = 0;
        
        int st = 1;
        while(pro){
            if(plu[br].first+st >= n or plu[br].first-st<0 or plu[br].second+st >= m or plu[br].second-st<0){
                pro = false;
            }

            else if(a[plu[br].first+st][plu[br].second] == '|' and a[plu[br].first-st][plu[br].second] == '|' and a[plu[br].first][plu[br].second+st] == '-' and a[plu[br].first][plu[br].second-st]== '-' and a[plu[br].first+st][plu[br].second+st] == '\\' and a[plu[br].first-st][plu[br].second-st] == '\\' and a[plu[br].first-st][plu[br].second+st] == '/' and a[plu[br].first+st][plu[br].second-st] == '/'){
                st++;
                temp++;
            }
            else{
                pro = false;
            }
            
            
        }
        
        maks = max(temp,maks);
    }
    cout << maks;

    return 0;
}