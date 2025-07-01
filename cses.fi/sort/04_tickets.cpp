#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, x;
    cin >> n >> m;
    multiset<int> a;
    for(int i = 1; i <= n; i++) {
        cin >> x;
        a.insert(x);
    }
    for(int i = 0; i < m; i++) {
        cin >> x;
        auto it = a.upper_bound(x);
        if(it == a.begin())
            cout << -1 << '\n';
        else {
            it--;
            cout << *it << '\n';
            a.erase(it);
        }
    }
    return 0;
}