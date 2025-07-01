#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    set<int> a;
	for(int i = 1; i <= n; i++) {
        a.insert(i);
    }
	if(a.size() <= 1) {
		cout << 1 << '\n';
		return 0;
	}
	int value = 2;
    while(!a.empty()) {
		cout << value << ' ';
		a.erase(a.find(value));
		if(a.size() == 0)
			break;
    	auto next = a.lower_bound(value);
		if(next == a.end()) {
			if(a.size() < 2) {
				cout << *(a.begin()) << '\n';
				return 0;
			}
			next = a.begin();
			next++;
		}
		else {
			next++;
			if(next == a.end()) {
				next = a.begin();
			}
		}
		value = *next;
	}
    cout << '\n';
}
