#include <bits/stdc++.h>
using namespace std;
/* 4. Dva bitna niza, podzadatak 1, n = 0
Postoji samo 1 niz, od m elemenata
Ako je taj niz oblika: 101010... -> 123456... najveci je broj m.
Ako je taj niz oblika: 010101... -> 234567... najveci je broj m + 1.
=> u 100% cik-cak nizu ( 0 -> 1 -> 0 ... ) prvi element odredjuje najveci elemenat
Ako niz nije cik cak?
Da je bilo 10 (m=2), elementi bi bili 12, naj = m
Ako je 11, elementi su 13, naj = m + 1
...
  */ 

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<int> v;
    int n; cin >> n; // n = 0
    
    int m; cin >> m;
    v.resize(m);
    for (int i = 0; i < m; ++i)
        cin >> v[i];

    int naj = m;
    if ( v[0] == 0 ) naj++; // prvi mora da bude 2 umesto 1
    for (int j = 1; j < m; ++j)  // kroz drugi niz
        if ( v[j-1] == v[j] ) naj++; // za svaka dva uzastopno ista elementa...

    cout << naj << endl; }
