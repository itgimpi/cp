#include <bits/stdc++.h>
using namespace std;

// switch se moze zameniti sa if else
int main()
{
    int n, max_1 = 0, max_2 = 0, maxi_1 = 0, maxi_2 = 0;
    vector<int> a;
    map<int, int> mapa;
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mapa[a[i]];
        mapa[a[i]]++;
    }
    for(auto b : mapa) {
        if(b.second > max_1) {
            max_2 = max_1;
            maxi_2 = maxi_1;
            max_1 = b.second;
            maxi_1 = b.first;
        }
    }
    switch(max_1) {
        case 2:
            if(a[0] != maxi_1 || a[a.size() - 1] != maxi_1) {
                cout << (a.size() - 2) / 2 + (a.size() - 2) % 2;
            }
            else {
                cout << (a.size() - max_2) / 2 + (a.size() - max_2) % 2;
            }
            break;
        default:
            cout << (a.size() - max_1) / 2 + (a.size() - max_1) % 2;
            break;
    }
    return 0;
}
