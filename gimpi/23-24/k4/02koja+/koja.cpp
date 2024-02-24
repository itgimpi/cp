#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector <pair < int, int >> a(n);
	vector <pair < int, int >> q(m);
	vector <int> sol(m);
	multiset <int> s1, s2;
	int x;
	for(int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second >> x;
		s2.insert(a[i].second - a[i].first); 	}
	sort(begin(a), end(a));
	for(int i = 0; i < m; i++) {
		cin >> q[i].first;
		q[i].second = i; 	}
	sort(begin(q), end(q));
	int pos = 0, tren;
	for(int i = 0; i < m; i++) {
		while(pos < n && a[pos].first < q[i].first) {
			s1.insert(a[pos].second + a[pos].first);
			s2.erase(s2.find(a[pos].second - a[pos].first));
			pos++; 		}
		tren = 0;
		if(!s1.empty()) 
			tren = max(tren, *(--s1.end()) - q[i].first);

		if(!s2.empty()) 
			tren = max(tren, *(--s2.end()) + q[i].first);
		sol[q[i].second] = tren; 	}
	for(int i = 0; i < m; i++) 
		cout << sol[i] << ' ';
	return 0; }
