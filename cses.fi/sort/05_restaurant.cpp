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
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[x]; a[y];
        a[x]++;
        a[y]--;
    }
    int total = 0, maxTotal = 0;
    for(auto i : a) {
        total += i.second;
        if(total > maxTotal)
            maxTotal = total;
    }
    cout << maxTotal << '\n';
    return 0;
}