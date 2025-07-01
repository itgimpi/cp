#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    if(a[0] != 1) {
        cout << 1 << '\n';
        return 0;
    }
    for(int i = 1; i < n; i++) {
        if(a[i] > a[i - 1] + 1) {
            cout << a[i - 1] + 1 << '\n';
            return 0;
        }
        a[i] += a[i - 1];
    }
    cout << a[n - 1] + 1 << '\n';
    return 0;
}
