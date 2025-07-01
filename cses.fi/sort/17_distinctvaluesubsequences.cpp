#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    const int mod = 1e9 + 7;
    
    int n;
    cin >> n;
    map<int, int> m;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        m[x];
        m[x]++;
    }
    long long res = 1;
    for(auto i : m) {
        (res *= (i.second + 1)) %= mod;
    }
    cout << res - 1 << '\n';
    return 0;
}
