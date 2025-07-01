#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, x;
    cin >> n >> m >> x;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int total = 0;
    for(int i = 0, j = 0; i < n && j < m; ) {
        if(abs(a[i] - b[j]) <= x) {
            total++;
            i++;
            j++;
        }
        else if(a[i] < b[j])
            i++;
        else
            j++;
    }
    cout << total << '\n';
    return 0;
}