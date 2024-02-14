#include <bits/stdc++.h>
using namespace std;

int br_poj(const vector<int>& a, int x) { // broj pojavljivanja ako se zna da postoji element u nizu
    auto lower = lower_bound(a.begin(), a.end(), x);
    auto upper = upper_bound(a.begin(), a.end(), x);
    return upper - lower;
}

int br_manjih(const vector<int>& a, int x) {
    return a.end() - upper_bound(a.begin(), a.end(), x);
}

int br_vecih(const vector<int>& a, int x) {
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}

// https://arena.petlja.org/competition/20202021okruzno-vezba#tab_133645
int main()
{
    int n, r, l;
    int radix[1000001];
    for(int i = 0; i < 1000001; i++) {
        radix[i] = 0;
    }
    vector<int> a;
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        radix[a[i]]++;
    }
    sort(a.begin(), a.end());
    
    return 0;
}
