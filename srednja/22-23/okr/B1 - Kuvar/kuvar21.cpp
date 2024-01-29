#include <bits/stdc++.h>
using namespace std;	
const int N = 100005; // maks. dimenzija nizova

int cnt[N];           // za brojanje emisija, inicijalno sve na 0
	
int main() {
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // nizovi

    int n = 4;

	
    long long res = 0;
    for(int i = 0; i < n; i++)  // broj emisija za svako jelo
        cnt[x[i]]++;   
                
    // za svaki scenario koji vodi ka nekom jelu, dodaj u resenje broj emisija o tom jelu
    for(int i = 0; i < n; i++) res += cnt[y[z[i] - 1]];
	
    cout << res;
    return 0; }