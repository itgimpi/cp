#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m; // broj brda i dana
	vector <pair < int, int >> a(n); // rastojanje i vreme zatvaranja
	vector <pair < int, int >> pocetak(m);
	vector <int> sol(m);
	multiset <int> s1, s2; // 
	int x;
	for(int i = 0; i < n; i++) { // rastojanja i vremena, bez spusta
		//xi je растојање од i-тог брда, ti je време до кад ради кућа 
		cin >> a[i].first >> a[i].second >> x;
		// vreme do kad radi - rastojanje = vreme za odmor
		s2.insert(a[i].second - a[i].first); } // vremena za odmor od nulte tacke idu u skup s2
	sort(begin(a), end(a)); // poredjaj rastojanja i vremena po rastojanjima
	for(int i = 0; i < m; i++) { // za svaki dan...
		cin >> pocetak[i].first; // ...zapamti pocetnu udaljenost od pocetka 
		pocetak[i].second = i; } // i redni broj upita
	sort(begin(pocetak), end(pocetak)); // poredjaj upite po rastojanjima od pocetka
	int ind = 0, tren;
	for(int i = 0; i < m; i++) { // za svaki dan...
		while(ind < n && a[ind].first < pocetak[i].first) { // za sve kuce koje mogu da se posete
			// dodaj vreme do kad radi + rastojanje
			s1.insert(a[ind].second + a[ind].first);
			s2.erase(s2.find(a[ind].second - a[ind].first));
			ind++; 	}
		tren = 0;
		if(!s1.empty()) 
			tren = max(tren, *(--s1.end()) - pocetak[i].first);
		if(!s2.empty()) 
			tren = max(tren, *(--s2.end()) + pocetak[i].first);
		sol[pocetak[i].second] = tren; } // zapamti resenje za taj dan
	for(int i = 0; i < m; i++)
		cout << sol[i] << ' ';  // resenja
	return 0; }
