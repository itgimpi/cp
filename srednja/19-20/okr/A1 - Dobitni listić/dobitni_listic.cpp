#include <bits/stdc++.h>
using namespace std;

// resenje dobija 100 poena na petlji
// https://arena.petlja.org/sr-Latn-RS/competition/20192020okruzno-vezba#tab_130056
int main()
{
    unsigned long long n;
    vector<unsigned long long> a;
    vector<unsigned long long> res;
    cin >> n;
    a.resize(n-1);
    for(unsigned long long i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    res.resize(n);
    res[0] = a[0];
    for(unsigned long long i = 1; i < n - 1; i++) {
        res[i] = a[i-1] * a[i] / __gcd(a[i-1], a[i]);
        if(res[i] > 1000000000000000000 || __gcd(res[i], res[i-1]) != a[i-1]) {
            cout << -1 << '\n';
            return 0;
        }
    }
    for(unsigned long long i = 0; i < n - 1; i++) {
        cout << res[i] << ' ';
    }
    cout << a[n-2] << '\n'; // poslednji broj je uvek poslednji element od niza A
    return 0;
}