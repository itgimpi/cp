#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i + 1];
    }
    map<int, int> pos;
    map<int, bool> cont;
    int minI = 0, distinct = 0;
    unsigned long long sum = 0;
    for(int i = 1; i <= n; i++) {
        pos[a[i]] = i;
        cont[a[i]];
        if(!cont[a[i]]) {
            distinct++;
            cont[a[i]] = true;
            if(distinct > k) {
                while(true) {
                    minI++;
                    if(minI == pos[a[minI]]) {
                        cont[a[minI]] = false;
                        distinct--;
                        break;
                    }
                }
            }
        }
        sum += i - minI;
    }
    cout << sum << '\n';
    return 0;
}
