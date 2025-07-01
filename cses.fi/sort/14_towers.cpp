#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
    multiset<int> towers;
    int count = 0;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        auto it = towers.lower_bound(a + 1);
        if(it == towers.end()) {
            count++;
            towers.insert(a);
        }
        else {
            towers.erase(it);
            towers.insert(a);
        }
    }
    cout << count << '\n';
    return 0;
}