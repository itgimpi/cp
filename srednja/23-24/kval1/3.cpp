#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, s, t, x, y;
    cin >> n >> m >> s >> t;
    s--; t--;
    vector<vector<int>> veze(400005);
    for(int i = 0; i < m; i++) {
        cin >> x >> y; x--; y--;
        veze[x].push_back(y+n);
        veze[y].push_back(x+n);
        veze[x+n].push_back(y);
        veze[y+n].push_back(x);
        // ni sam ne znam sto ovaj kod, ali priblizava se 4:00,
        // procitajte objasnjenje na https://olympicode.rs/takprog/2023_2024/kv1/03_presedanja/#__tabbed_1_2
    }

    // BFS, ali trazimo samo "neparne" cvorove
    queue<pair<int, int>> frontier;
    bool visited[400005]; // posecenost
    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }
    frontier.push(make_pair(s, 0));
    while(!frontier.empty()) { // dok nije t poseceno
        // iteracija BFS
        int p = frontier.front().first;
        int d = frontier.front().second;
        frontier.pop();
        if(visited[p])
            continue;
        visited[p] = true;

        if(p == t) {
            cout << d / 2 << endl;
            break;
        }

        for(int i = 0; i < veze[p].size(); i++) {
            frontier.push(make_pair(veze[p][i], d+1));
        }
    }
    return 0;
}
