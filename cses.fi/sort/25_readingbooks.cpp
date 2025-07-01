#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long sum = 0;
    for(int i = 0; i < n - 1; i++) {
        sum += a[i];
    }
    if(a[n-1] <= sum)
        cout << sum + a[n-1] << '\n';
    else
        cout << a[n - 1] * 2 << '\n';
    return 0;
}
