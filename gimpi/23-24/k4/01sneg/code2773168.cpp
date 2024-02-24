#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, minl, maxl = 0, curl, ti, tj;
    cin >> n >> m;
    vector<vector<char>> sneg(n);
    for(int i = 0; i < n; i++) {
        sneg[i].resize(m);
        for(int j = 0; j < m; j++) {
            cin >> sneg[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(sneg[i][j] == '+') {
                minl = 99;
                
                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti--; // gore levo
                    tj--;
                    if(sneg[ti][tj] == '\\') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);

                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti--; // gore
                    if(sneg[ti][tj] == '|') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);

                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti++; // dole
                    if(sneg[ti][tj] == '|') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);

                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    tj--; // levo
                    if(sneg[ti][tj] == '-') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);

                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    tj++; // desno
                    if(sneg[ti][tj] == '-') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);
                
                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti--; // gore desno
                    tj++;
                    if(sneg[ti][tj] == '/') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);
                
                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti++; // dole levo
                    tj--;
                    if(sneg[ti][tj] == '/') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);
                
                ti = i;
                tj = j;
                curl = 0;
                while(ti > 0 && ti < n - 1 && tj > 0 && tj < m - 1) {
                    ti++; // dole desno
                    tj++;
                    if(sneg[ti][tj] == '\\') {
                        curl++;
                    }
                    else {
                        break;
                    }
                }
                minl = min(curl, minl);
            }
            maxl = max(maxl, minl);
        }
    }
    cout << maxl << '\n';
    return 0;
}