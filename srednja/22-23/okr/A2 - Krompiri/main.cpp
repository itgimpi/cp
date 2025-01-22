#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, total = 0;
    cin >> n >> m;
    vector<tuple<int, int, int>> red(n), kol(m), potezi;
    for(int i = 0; i < n; i++) {
        cin >> get<1>(red[i]) >> get<0>(red[i]);
        get<2>(red[i]) = i + 1;
    }
    for(int i = 0; i < m; i++) {
        cin >> get<1>(kol[i]) >> get<0>(kol[i]);
        get<2>(kol[i]) = i + 1;
    }
    sort(red.begin(), red.end());
    sort(kol.begin(), kol.end());
    while(!kol.empty() && !red.empty()) {
        total += min(get<1>(kol.back()), get<1>(red.back()));
        if(get<1>(kol.back()) < get<1>(red.back())) {
            
        }
    }
    return 0;
}