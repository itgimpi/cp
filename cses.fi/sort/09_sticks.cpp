#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long m = a[n/2], r = 0;
    for(int i = 0; i < n; i++) {
        r += abs(a[i]-m);
    }
    cout << r << '\n';
    return 0;
}