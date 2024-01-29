#include <bits/stdc++.h>
using namespace std;	
const int N = 100005; // maks. dimenzija nizova
int x[N], y[N], z[N]; // nizovi
int cnt[N];           // za brojanje emisija, inicijalno sve na 0
	
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for(int i = 0; i < n; i++) cin >> x[i];
    for(int i = 0; i < n; i++) cin >> y[i];
    for(int i = 0; i < n; i++) cin >> z[i];
	
    long long res = 0;
    for(int i = 0; i < n; i++)  // broj emisija za svako jelo
        cnt[x[i]]++;   
                
    // za svaki scenario koji vodi ka nekom jelu, dodaj u resenje broj emisija o tom jelu
    for(int i = 0; i < n; i++) res += cnt[y[z[i] - 1]];
	
    cout << res;
    return 0; }