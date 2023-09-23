#include <bits/stdc++.h>

/* Provere znanja

ima najvise 1000 ucenika... niz sa 1000 visina
posle svakog ulaska, sortiraj niz...
sada je element u sredini resenje...
ako su pozicije od 0 do n-1, sredina je (n-1)/2...
ispis srednjeg elementa...

Za svaki ulazak (n) sortiraj niz... O( n n log n) ~ 10 na 6


*/

using namespace std;
typedef long long ll;

// 
int v[1005];
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
