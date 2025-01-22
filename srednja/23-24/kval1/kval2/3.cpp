#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q, x, y;
    scanf("%d", &n);
    vector<int> a(n + 2);
    vector<int> suf(n + 2);
    vector<int> pref(n + 2);
    for(int i = 0; i < n; i++) {
        scanf("%d", a[i]);
    }
    a[0] = 0;
    a[n + 1] = min(a[n], a[n-1]);
    suf[n+1] = 0;
    suf[n] = a[n];
    for(int i = n - 1; i >= 0; i--) {
        suf[i] = min();
    }
    for(int i = 2; i < n - 1; i++) {

    }
    scanf("%d", &q);
    for(int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);

    }
    return 0;
}
