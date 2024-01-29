#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1667

/* unos:
5 5
1 2
1 3
1 4
2 3
5 4

izlaz:
3
1 4 5
*/

// za ovaj zadatak se koristi primov ili kruskalov algoritam
int main()
{
    // optimizacija unosa i izlaza, neophodna za neke zadatke
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, a, b; // n - broj cvora, m - broj veza
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
    }
    return 0;
}
