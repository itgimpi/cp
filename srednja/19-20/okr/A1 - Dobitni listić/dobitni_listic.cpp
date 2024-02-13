#include <bits/stdc++.h>
using namespace std;

int main()
{
    unsigned long long n;
    vector<unsigned long long> a;
    vector<unsigned long long> res;
    cin >> n;
    a.resize(n-1);
    for(unsigned long long i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    res.resize(n);
    res[0] = a[0];
    for(unsigned long long i = 1; i < n - 1; i++) {
        res[i] = a[i-1] * a[i] / __gcd(a[i-1], a[i]);
        cout << res[i] << endl;
        if(res[i] == res[i-1] || res[i] > 1000000000000000000) {
            cout << -1 << '\n';
            return 0;
        }
    }
    res[n-1] = a[n-1]
    for(unsigned long long i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
    return 0;
}