#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> a;

bool comp1(int i, int j) {
    if(a[i].first != a[j].first)
        return a[i].first < a[j].first;
    return a[i].second > a[j].second;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> aI;
    vector<bool> c(n, false), s(n, false);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
        aI.push_back(i);
    }
    sort(aI.begin(), aI.end(), comp1);
    multiset<int> q;
    for(int i : aI) {
        auto it = q.lower_bound(a[i].second);
        if(it != q.end()) {
            c[i] = true;
        }
        q.insert(a[i].second);
    }
    q.clear();
    for(int i = n - 1; i >= 0; i--) {
        auto it = q.upper_bound(a[aI[i]].second);
        if(it != q.begin()) {
            s[aI[i]] = true;
        }
        q.insert(a[aI[i]].second);
    }
    for(auto i : s) {
        cout << i << ' ';
    }
    cout << '\n';
    for(auto i : c) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}
