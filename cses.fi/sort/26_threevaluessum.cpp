#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n, m;
    cin >> n >> m;
    vector<pair<long long, int>> a;
    for(int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a.emplace_back(x, i + 1);
    }
    sort(a.begin(), a.end());
    if(n < 3) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for(int i = 0; i < a.size() - 2; i++) {
        int l = i + 1, r = n - 1;
        while(l != r) {
            long long sum = a[i].first + a[l].first + a[r].first;
            if(sum == m) {
                cout << a[i].second << ' ' << a[l].second << ' ' << a[r].second << '\n';
                return 0;
            }
            if(sum > m)
                r--;
            else
                l++;
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
