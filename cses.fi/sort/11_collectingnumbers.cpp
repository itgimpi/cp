#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n), p(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    int count = 1;
    for(int i = 2; i <= n; i++) {
        if(p[i] < p[i - 1])
            count++;
    }
    cout << count << '\n';
    return 0;
}
