#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> prefix(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> prefix[i];
        prefix[i] += prefix[i-1];
    }

    multiset<long long> s;
    long long maxVal = LLONG_MIN;
    for(int i = a; i <= b; i++) {
        s.insert(prefix[i]);
        maxVal = max(maxVal, prefix[i]);
    }
    for(int i = 1; i + a <= n; i++){
        s.erase(prefix[i + a - 1]);
        s.insert(prefix[min(i + b, n)]);
        maxVal = max(maxVal, *s.rbegin() - prefix[i]);
    }
    cout << maxVal << '\n';
}