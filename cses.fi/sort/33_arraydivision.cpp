#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    unsigned long long k;
    cin >> n >> k;
    vector<unsigned long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    unsigned long long lower = 0, upper = 0;
    for(int i = 0; i < n; i++) {
        if(lower < a[i])
            lower = a[i];
        upper += a[i];
    }
    while(upper - lower > 1) {
        unsigned long long test = (upper + lower) / 2;
        unsigned long long currSum = 0;
        int subArrays = 1;
        for(int i = 0; i < n; i++) {
            if(currSum + a[i] > test) {
                currSum = 0;
                subArrays++;
                if(subArrays > k)
                    break;
            }
            currSum += a[i];
        }
        if(subArrays > k)
            lower = test;
        else
            upper = test;
    }
    if(upper - lower == 1) {
        unsigned long long currSum = 0;
        int subArrays = 1;
        for(int i = 0; i < n; i++) {
            if(currSum + a[i] > lower) {
                currSum = 0;
                subArrays++;
                if(subArrays > k) {
                    lower = upper;
                    break;
                }
            }
            currSum += a[i];
        }
    }
    cout << lower << '\n';
    return 0;
}
