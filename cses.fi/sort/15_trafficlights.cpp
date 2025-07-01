#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n, m;
    cin >> n >> m;
    set<int> lights;
    set<pair<int, pair<int, int>>> ranges;
    lights.insert(0);
    lights.insert(n);
    ranges.insert(make_pair(n, make_pair(0, n)));
    for(int i = 0; i < m; i++) {
        int a;
        cin >> a;
        auto lIt = lights.lower_bound(a);
        auto rIt = lIt;
        lIt--;
        ranges.erase(make_pair(*rIt - *lIt, make_pair(*lIt, *rIt)));
        lights.insert(a);
        ranges.insert(make_pair(*rIt - a, make_pair(a, *rIt)));
        ranges.insert(make_pair(a - *lIt, make_pair(*lIt, a)));
        cout << ranges.rbegin()->first << ' ';
    }
    cout << '\n';
    return 0;
}