#include <bits/stdc++.h>
using namespace std;    
//const int N = 100005; // maks. dimenzija nizova

int cnt[5];           // za brojanje emisija, inicijalno sve na 0
    
int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // nizovi
    int *px, *py, *pz, *pcnt;

    long long res = 0;
    for(px = x; px < x + n; px++) {  // broj emisija za svako jelo
        //cnt [ *px ]++;   // nizovski
        //(*(pcnt + *px))++; // pokazivacki kratko
        pcnt = cnt + *px;
        (*pcnt)++; }
                
    px = pcnt = NULL; // ne mora, zbog preglednisti
    //for(int i = 0; i < n; i++) res += cnt[y[z[i] - 1]]; // nizovski
    
    for(int i = 0; i < n; i++) {
        pz = z + i;
        py = y + *pz - 1;
        pcnt = cnt + *py;
        res += *pcnt; }
    
    cout << res;
    return 0; }