#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
    }
    long long sum = 0, cTime = 0;
    sort(a.begin(), a.end());
    for(auto i : a) {
        sum += i.second - i.first - cTime;
        cTime += i.first;
    }
    cout << sum << '\n';
    return 0;
}