#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;
typedef long long llint; 

//llint prefiksor[2*MAXN];

int main(void) {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vector<llint>prefiksor(2*n+2);
    for (int i = 0; i < n; ++i) {
        llint x; cin >> x;
        prefiksor[i + 1] = prefiksor[i] ^ x;    }

    for (int i = 0; i <= n; ++i) 
        prefiksor[i + n + 1] = prefiksor[i];

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        llint l, r; cin >> l >> r; --l; --r;
        r = l % (n + 1) + (r - l + 1) % (n + 1); l %= n + 1; 
        cout << (prefiksor[r] ^ prefiksor[l]);    }

    return 0; }
