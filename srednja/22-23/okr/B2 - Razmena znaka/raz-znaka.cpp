#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    bool ok;
    vector<int> a, b;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> n;
        a.resize(n);
        b.resize(n);
        for(int j = 0; j < n; j++) {
            cin >> a[j];
            if(j & 1) { a[j] = -a[j]; }
        }
        for(int j = 0; j < n; j++) {
            cin >> b[j];
            if(j & 1) { b[j] = -b[j]; }
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ok = true;
        for(int j = 0; j < n; j++) {
            if(a[j] != b[j]) {
                ok = false;
            }
        }
        if(ok) { cout << "DA" << '\n'; }
        else { cout << "NE" << '\n'; }
    }
    return 0;
}
