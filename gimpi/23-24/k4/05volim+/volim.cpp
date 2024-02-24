#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 5;

ll pref[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int n, t, a, b;
    cin >> n >> t >> a >> b;
    int l;
    for(int i = 0; i < n; i++) {
        cin >> l;
        pref[i + 1] = pref[i] + l;   }
    ll sol=0;
    int y;
    for(int x = 0; x < n; x++) {
        if(x * b > t) break; 
        y = (t - x * b) / a;
        sol = max(sol, pref[min(y + x, n)] - pref[x]);     }
    cout << sol;
    return 0; }