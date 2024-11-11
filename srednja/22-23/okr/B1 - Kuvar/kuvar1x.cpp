#include <bits/stdc++.h>
using namespace std;	
const int N = 100010; // maks. dimenzija nizova

int x[N], y[N], z[N]; // ovde se deklarisu veci nizovi
int cnt[N];           // za brojanje emisija, inicijalno sve na 0
	
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for(int i = 0; i < n; i++) cin >> x[i];
    for(int i = 0; i < n; i++) cin >> y[i];
    for(int i = 0; i < n; i++) cin >> z[i];
	
    long long res = 0;
    for(int i = 0; i < n; i++)  // za svaku emisiju...
        for(int j = 0; j < n; j++)   // za svaki scenario...
            if (x[i] == y[z[j]-1])   // -1 zbog prebacivanja sa 1, 2, 3, ... na 0, 1, 2, ...
                res++;               // ako je isto jelo...
                
    cout << res;
    return 0; }