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

// ovaj zadatak je vrlo slican kao 02-labyrinth, samo sto se ne koristi
// matrica char-ova nego graf
int main()
{
    // optimizacija unosa i izlaza, neophodna za neke zadatke
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, a, b; // n - broj cvora, m - broj veza
    vector<vector<int>> graf;
    vector<int> dosli; // od kojeg cvora smo dosli do cvora x, potrebno za putanju
    cin >> n >> m;
    graf.resize(n);
    dosli.resize(n);
    for(int i = 0; i < n; i++) {
        dosli.at(i) = -1;
    }
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graf[a-1].push_back(b-1);
        graf[b-1].push_back(a-1);
    }

    // BFS
    vector<int> frontier;
    frontier.push_back(0);
    int tren_cvor; // trenutni cvor koji se razmatra

    // Cilj ovog BFS-a je, za razliku od proslog zadatka, da pronadje put od prvog cvora do poslednjeg
    // za svaki cvor cemo zapisati od kojeg cvora je doslo do tog
    while(true) {
        tren_cvor = frontier.at(0);
        frontier.erase(frontier.begin());
        for(int i = 0; i < graf.at(tren_cvor).size(); i++) {
            if(dosli.at(graf.at(tren_cvor).at(i)) == -1) {
                dosli.at(graf.at(tren_cvor).at(i)) = tren_cvor;
                frontier.push_back(graf.at(tren_cvor).at(i));
            }
            if(graf.at(tren_cvor).at(i) == n-1) {
                goto kraj; // dosli smo do poslednjeg cvora, kraj algoritma
            }
        }
        if(frontier.empty()) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    kraj:
    // Sada samo moramo pratiti put od kraja do pocetka i dobicemo resenje.
    tren_cvor = n-1;
    vector<int> putanja; putanja.push_back(n-1);
    while(tren_cvor != 0) {
        tren_cvor = dosli.at(tren_cvor);
        putanja.push_back(tren_cvor);
    }

    // ispis resenja
    // obrnut je redosled resenja, tako da ga moramo ispraviti
    cout << putanja.size() << endl;
    for(int i = putanja.size() - 1; i >= 0; i--) {
        cout << putanja.at(i) + 1 << " ";
    }
    cout << endl;
    return 0;
}
