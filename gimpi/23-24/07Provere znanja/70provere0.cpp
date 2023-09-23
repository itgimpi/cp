#include <bits/stdc++.h>
using namespace std;
/* Provere znanja podzadatak 0

da je malo ucenika, malo visina...
posle svakog ulaska, sortiraj niz...
sada je element u sredini resenje...
ako su pozicije od 0 do n-1, sredina je (n-1)/2...
ispis srednjeg elementa...  */

int v[1000005]; // milion
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin>>n;
	for(int i = 0, br = 0; i < n; i++) {
		int vi, ai; cin >> vi >> ai;
		for (int ii = 0; ii < ai; ii++)
			v[br++] = vi;
		sort(v, v+br);
		cout << v[(br-1)/2] << '\n'; } // 
	
	return 0; }
