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
    unsigned long long minA = INT_MAX;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        minA = min(a[i], minA);
    }
    unsigned long long lowerRange = 0, upperRange = m * minA;
    while(upperRange - lowerRange > 1) {
        unsigned long long testVal = (upperRange + lowerRange) / 2, sum = 0;
        for(int i = 0; i < n; i++) {
            sum += testVal / a[i];
        }
        if(sum < m)
            lowerRange = testVal;
        else
            upperRange = testVal;
    }
    if(upperRange - lowerRange == 1) {
        unsigned long long sum = 0;
        for(int i = 0; i < n; i++) {
            sum += lowerRange / a[i];
        }
        if(sum < m)
            lowerRange = upperRange;
    }
    cout << lowerRange << '\n';
    return 0;
}