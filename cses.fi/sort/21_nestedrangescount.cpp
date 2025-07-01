#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    vector<int> c(n, 0), s(n, 0);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
        aI.push_back(i);
    }
    sort(aI.begin(), aI.end(), comp1);
    ordered_multiset<int> q;
    for(int i : aI) {
        c[i] = q.size() - q.order_of_key(a[i].second);
        q.insert(a[i].second);
    } 
    q.clear();
    for(int i = n - 1; i >= 0; i--) {
        s[aI[i]] = q.order_of_key(a[aI[i]].second + 1);
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
