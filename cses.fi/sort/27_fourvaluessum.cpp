#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    long long m;
    cin >> n >> m;
    vector<pair<long long, int>> a;
    for(int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a.emplace_back(x, i + 1);
    }
    if(n < 4) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < n - 3; i++) {
        for(int j = i + 1; j < n - 2; j++) {
            int l = j + 1, r = n - 1;
            while(l != r) { 
                long long sum = a[i].first + a[j].first + a[l].first + a[r].first;
                if(sum == m) {
                    cout << a[i].second << ' ' << a[j].second << ' ' <<
                        a[l].second << ' ' << a[r].second << '\n';
                    return 0;
                }
                if(sum > m)
                    r--;
                else
                    l++;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
