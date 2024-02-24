#include <bits/stdc++.h>
using namespace std;

long long utakmice[3];
int timovi[3][100100];
int gubitaka[100100];
int sudije[100100][3];
int najbolja_pozicija[100100];
set< pair<int, int> > bio;
vector<int> best[8];

void mec(int a, int b, int p) { // slucaj kad su im najbolje pozicije jednake
    if (a == b || najbolja_pozicija[a] != p || najbolja_pozicija[b] != p)
        return;

    pair<int, int> par = make_pair(min(a, b), max(a, b));
    if (bio.count(par)) return;
    bio.insert(par);

    pair<int, int> p0(min(sudije[a][0], sudije[b][0]), max(sudije[a][0], sudije[b][0]));
    pair<int, int> p1(min(sudije[a][1], sudije[b][1]), max(sudije[a][1], sudije[b][1]));
    pair<int, int> p2(min(sudije[a][2], sudije[b][2]), max(sudije[a][2], sudije[b][2]));
    if (p2 < p0 && p2 < p1) {
        ++utakmice[2];
        gubitaka[a] += (sudije[a][2] > sudije[b][2]);
        gubitaka[b] += (sudije[b][2] > sudije[a][2]);     }
    else if (p1 < p0) {
        ++utakmice[1];
        gubitaka[a] += (sudije[a][1] > sudije[b][1]);
        gubitaka[b] += (sudije[b][1] > sudije[a][1]);     }
    else {
        ++utakmice[0];
        gubitaka[a] += (sudije[a][0] > sudije[b][0]);
        gubitaka[b] += (sudije[b][0] > sudije[a][0]);     } }

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < n; j++) {
            int tim; cin >> tim; --tim;
            timovi[i][j] = tim;
            sudije[tim][i] = j; }
		
    for (int i = 0; i < n; i++) {
        najbolja_pozicija[i] = min(sudije[i][0], min(sudije[i][1], sudije[i][2]));
        int mask = 0;
        for(int j = 0; j < 3; j++)
            if (sudije[i][j] == najbolja_pozicija[i])
                mask |= (1 << j);
        best[mask].push_back(najbolja_pozicija[i]);    }
		
    for(int mask = 0; mask < 8; mask++)
        sort(best[mask].begin(), best[mask].end());

    for (int i = 0; i < n; i++) { // Slucaj 1: najbolja pozicija pobednika je veca od najbolje pozicije gubitnika
        for (int mask = 1; mask < 8; ++mask) {
            int boljih = lower_bound(best[mask].begin(),
                    best[mask].end(), najbolja_pozicija[i])
                    - best[mask].begin();
            int sudija = -1;
            for(int j = 0; j < 3; j++)
                if ((mask >> j) & 1)
                    if (sudija == -1 || sudije[i][j] < sudije[i][sudija])
                        sudija = j;
            utakmice[sudija] += boljih;
            gubitaka[i] += boljih; } }

    for (int i = 0; i < n; i++) {  // Slucaj 2: najbolja pozicija pobednika jednaka je najboljoj poziciji gubitnika.
        mec(timovi[0][i], timovi[1][i], i);
        mec(timovi[0][i], timovi[2][i], i);
        mec(timovi[1][i], timovi[2][i], i); }

    cout << utakmice[0] << ' ' << utakmice[1] << ' ' << utakmice[2] << '\n';
    for (int i = 0; i < n; i++) 
        cout << n - 1 - gubitaka[i] << ' ';
    cout << endl;
    return 0; }
