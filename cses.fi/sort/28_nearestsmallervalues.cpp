#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<int> sol(n, 0);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = make_pair(x, i + 1);
    }
    sort(a.begin(), a.end());
    queue<int> ta;
    set<int> s;
    ta.push(a[0].second);
    for(int i = 1; i < n; i++) {
        if(a[i].first != a[i - 1].first) {
            while(!ta.empty()) {
                s.insert(ta.front());
                ta.pop();
            }
        }
        auto it = s.upper_bound(a[i].second);
        if(it != s.begin()) {
            it--;
            sol[a[i].second - 1] = *it;
        }
        ta.push(a[i].second);
    }
    for(auto i : sol) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}
