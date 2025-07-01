#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long total = 0, maxTotal = LONG_MIN;
    for(int i = 0; i < n; i++) {
        if(total < 0)
            total = a[i];
        else
            total += a[i];
        if(total > maxTotal)
            maxTotal = total;
    }
    cout << maxTotal << '\n';
    return 0;
}