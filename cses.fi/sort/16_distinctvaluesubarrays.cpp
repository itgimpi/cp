#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i + 1];
    }
    map<int, int> pos;
    int minI = 0;
    unsigned long long sum = 0;
    for(int i = 1; i <= n; i++) {
        pos[a[i]];
        if(pos[a[i]] != 0 && pos[a[i]] > minI) {
            minI = pos[a[i]];
        }
        pos[a[i]] = i;
        sum += i - minI;
    }
    cout << sum << '\n';
    return 0;
}
