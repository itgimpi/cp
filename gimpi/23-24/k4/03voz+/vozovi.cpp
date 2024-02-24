#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
vector <int> dp;
int binary(int x) {
    int lo = 0, hi = dp.size(), mid;
    while(lo < hi) {
        mid = (lo + hi) / 2;
        if(dp[mid] < x) 
            lo = mid + 1;
        else 
            hi = mid; }
    return lo; }

void dodaj(int x) {
    int ind = binary(x);
    if(ind == dp.size()) 
        dp.push_back(x);
    else 
        dp[ind] = x;   }

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vector<int>a(n);
    vector<int>l(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--; }
    int b;
    for(int i = 0; i < n; i++) {
        cin >> b;
        l[a[i]] = b; }
    for(int i = 0; i < n; i++)
        dodaj(l[i]);

    cout << dp.size();
    return 0; }

