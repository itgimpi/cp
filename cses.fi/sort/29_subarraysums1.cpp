#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    long long m;
    cin >> n >> m;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int l = 0, sol = 0;
    long long sum = 0;
    for(int r = 0; r < n; r++) {
        sum += a[r];
        while(sum > m)
            sum -= a[l++];
        if(sum == m)
            sol++;
    }
    cout << sol << '\n';
    return 0;
}
