#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1193

/*
5 8
########
#.A#...#
#.##.#B#
#......#
########

izlaz:
YES
9
LDDRRRRRU
*/

int main()
{
    // optimizacija unosa i izlaza, neophodna za neke zadatke
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cerr.tie(0);

    int n, m; // visina i duzina lavirinta
    pair<int, int> pocetak;
    pair<int, int> kraj;
    vector<vector<char>> lavirint;
    cin >> n >> m;
    lavirint.resize(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> lavirint.at(i).at(j);
            if(lavirint.at(i).at(j) == 'A') {
                pocetak.first = i;
                pocetak.second = j;
            }
            if(lavirint.at(i).at(j) == 'B') {
                kraj.first = i;
                kraj.second = j;
            }
        }
    }

    // BFS
    vector<pair<int, int>> frontier;
    pair<int, int> temp_pair;
    int temp_var;
    frontier.push_back(pocetak);

    // Cilj ovog BFS-a je, za razliku od proslog zadatka, da pronadje put od A do B.
    // Ovo ce postici time sto ce za svako polje zapisati polje od kojeg je doslo do tog polja.
    while(true) {
        temp_pair = frontier.at(0);
        frontier.erase(frontier.begin());
        if(temp_pair.first != 0) {
            if(lavirint.at(temp_pair.first - 1).at(temp_pair.second) == '.') {
                frontier.push_back(make_pair(temp_pair.first - 1, temp_pair.second));
                lavirint.at(temp_pair.first - 1).at(temp_pair.second) = 'U';
            }
            else if(lavirint.at(temp_pair.first - 1).at(temp_pair.second) == 'B') {
                lavirint.at(temp_pair.first - 1).at(temp_pair.second) = 'U';
                break;
            }
        }
        if(temp_pair.first != n - 1) {
            if(lavirint.at(temp_pair.first + 1).at(temp_pair.second) == '.') {
                frontier.push_back(make_pair(temp_pair.first + 1, temp_pair.second));
                lavirint.at(temp_pair.first + 1).at(temp_pair.second) = 'D';
            }
            else if(lavirint.at(temp_pair.first + 1).at(temp_pair.second) == 'B') {
                lavirint.at(temp_pair.first + 1).at(temp_pair.second) = 'D';
                break;
            }
        }
        if(temp_pair.second != 0) {
            if(lavirint.at(temp_pair.first).at(temp_pair.second - 1) == '.') {
                frontier.push_back(make_pair(temp_pair.first, temp_pair.second - 1));
                lavirint.at(temp_pair.first).at(temp_pair.second - 1) = 'L';
            }
            else if(lavirint.at(temp_pair.first).at(temp_pair.second - 1) == 'B') {
                lavirint.at(temp_pair.first).at(temp_pair.second - 1) = 'L';
                break;
            }
        }
        if(temp_pair.second != m - 1) {
            if(lavirint.at(temp_pair.first).at(temp_pair.second + 1) == '.') {
                frontier.push_back(make_pair(temp_pair.first, temp_pair.second + 1));
                lavirint.at(temp_pair.first).at(temp_pair.second + 1) = 'R';
            }
            else if(lavirint.at(temp_pair.first).at(temp_pair.second + 1) == 'B') {
                lavirint.at(temp_pair.first).at(temp_pair.second + 1) = 'R';
                break;
            }
        }
        if(frontier.empty()) {
            cout << "NO" << endl;
            return 0;
        }
    }
    temp_pair = kraj;
    string resenje;
    // Sada samo moramo pratiti put od kraja do pocetka i dobicemo resenje.
    while(lavirint.at(temp_pair.first).at(temp_pair.second) != 'A') {
        resenje.push_back(lavirint.at(temp_pair.first).at(temp_pair.second));
        switch(lavirint.at(temp_pair.first).at(temp_pair.second)) {
            case 'U':
                temp_pair.first++;
                break;
            case 'D':
                temp_pair.first--;
                break;
            case 'L':
                temp_pair.second++;
                break;
            case 'R':
                temp_pair.second--;
                break;
            default:
                cout << "error" << endl;
                return 0;
        }
    }
    // ispis resenja
    cout << "YES" << endl;
    cout << resenje.size() << endl;
    // obrnut je redosled resenja, tako da ga moramo ispraviti
    for(int i = 0; i < resenje.size(); i++) { cout << resenje.at(resenje.size() - 1 - i); }
    cout << endl;
    return 0;
}
