#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<long long, int> sums;
    long long total = 0, sol = 0;
    sums[0] = 1;
    for(int i = 0; i < n; i++) {
        total = ((total + a[i]) % n + n) % n;
        sums[total];
        sol += sums[total];
        sums[total]++;
    }
    cout << sol << '\n';
    return 0;
}
