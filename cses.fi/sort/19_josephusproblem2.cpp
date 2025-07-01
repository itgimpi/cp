#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
    tree_order_statistics_node_update> indexed_set;

// P.S. Competitive Programmer's Handbook - strana 44
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    indexed_set josephus;
    for(int i = 1; i <= n; i++) {
        josephus.insert(i);
    }
    int ptr = k % n;
    while(josephus.size() > 0) {
        auto it = josephus.find_by_order(ptr);
        cout << *it << ' ';
        josephus.erase(it);
        if(josephus.size() > 0)
            (ptr += k) %= josephus.size();
    }
    cout << '\n';
    return 0;
}