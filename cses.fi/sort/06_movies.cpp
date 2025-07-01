#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    map<int, int> a;
    a[0] = 0;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[x]; a[y];
        if(a[y] < x)
            a[y] = x;
    }
    int total = 0;
    for(auto &i : a) {
        if(i.second != 0) {
            i.second = max(total, a[i.second] + 1);
            total = i.second;
        }
    }
    cout << total << '\n';
    return 0;
}