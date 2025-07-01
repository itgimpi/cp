#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = make_pair(y, x);
    }
    sort(a.begin(), a.end());
    multiset<int> members;
    for(int i = 0; i < k; i++) {
        members.insert(0);
    }
    int w = 0;
    for(int i = 0; i < n; i++) {
        auto it = members.upper_bound(a[i].second);
        if(it == members.begin())
            continue;
        it--;
        members.erase(it);
        members.insert(a[i].first);
        w++;
    }
    cout << w << '\n';
    return 0;
}
