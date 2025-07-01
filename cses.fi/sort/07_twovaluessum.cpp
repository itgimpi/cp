#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = make_pair(x, i + 1);
    }
    sort(a.begin(), a.end());
    pair<int, int> *ptr1 = &a[0], *ptr2 = &a[n-1];
    while(ptr1 < ptr2) {
        if((*ptr1).first + (*ptr2).first == m) {
            cout << (*ptr1).second << ' ' << (*ptr2).second << '\n';
            return 0;
        }
        else if((*ptr1).first + (*ptr2).first > m)
            ptr2--;    
        else
            ptr1++;
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}