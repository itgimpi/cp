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
    int minLimit = 0, maxPartition = 1;
    map<int, int> s;
    s[a[0]] = 1;
    for(int i = 1; i < n; i++) {
        s[a[i]];
        if(s[a[i]] != 0 && s[a[i]] >= minLimit)
            minLimit = s[a[i]];
            s[a[i]] = i + 1;
        maxPartition = max(maxPartition, i - minLimit + 1);
    }
    cout << maxPartition << '\n';
    return 0;
}