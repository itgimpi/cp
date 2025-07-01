#include <bits/stdc++.h>
using namespace std;

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<unsigned long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int total = 0;
    unsigned long long *ptr1 = &a[0], *ptr2 = &a[n-1];
    for(; ptr1 <= ptr2; total++) {
        if(*ptr1 + *ptr2 > m)
            ptr2--;
        else {
            ptr1++;
            ptr2--;
        }
    }
    cout << total << '\n';
    return 0;
}