#include<bits/stdc++.h>
using namespace std;
/* This can be solved using basic DP approach in linear time.
subordinates[u] =   ∑   subordinates[v], where v is a child of u
               v : children[u]   
broj sledbenika = zbir sledbenika od sledbenika
*/
vector<int> veze[200005]; // vektor nizova, global
int sol[200005]; // resenje, global
 
//  prvi poziv 1, 0, 0, cvor 1, nulti nivo, nema preth.
void dfs(int cvor,int nivo, int preth) { // 
	sol[cvor] = 1;
	
	for (int v : veze[cvor]) // za sve sledbenike cvor-a...
		if (v != preth) { // (sem za prethodnika)
			dfs(v, nivo + 1, cvor);
			sol[cvor] += sol[v]; } }	
 
int main() {
    int n; cin >> n;
    
    for(int i = 2; i <= n ; i++) {
        int x; cin >> x;
        veze[i].push_back(x); // oba smera
        veze[x].push_back(i); }

    dfs(1, 0, 0);
    for(int i = 1; i <= n ; i++) 
        cout << sol[i] - 1 << ' '; }