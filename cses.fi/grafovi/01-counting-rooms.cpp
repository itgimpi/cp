#include <bits/stdc++.h>
using namespace std;

// https://cses.fi/problemset/task/1192

/* test primer dat u zadatku
unos:
5 8
########
#..#...#
####.#.#
#..#...#
########

izlaz:
3 */

void BFS(vector<vector<char>>* sobe, int i, int j, int n, int m) {
    vector<pair<int, int>> frontier; // pair<int, int> se ovde koristi za pamcenje polja
    pair<int, int> temp_polje; // s obzirom da se mora iz frontiera izvaditi poslednji elemenat,
    // moramo ga cuvati u ovoj pomocnoj promenljivi
    frontier.push_back(make_pair(i, j)); // BFS funkcionise na osnovu "frontiera", prstena koji se siri tokom prolaza kroz matricu
    // kada ne bismo menjali elemente u matrici, bio bi nam potreban i vektor posecenih polja, ali nam sada to nije potrebno
    sobe->at(i).at(j) = '#';
    // .at() je vektorska funkcija koja ce biti koriscena u ovom resenju zbog toga sto je
    // bolje koristiti umesto [] sa vektorima, iako isti cilj postizu
    while(!frontier.empty()) { 
        // najranije ubaceno polje u frontier se izbaci
        temp_polje = frontier.at(frontier.size() - 1);
        frontier.pop_back();
        // i gleda se da li je neko od susednih polja prazno, ako jeste ubacuje se u frontier
        if(temp_polje.first != 0) { // da ne bi doslo do sobe->at(-1), sto izaziva segfault
            if(sobe->at(temp_polje.first - 1).at(temp_polje.second) == '.') {
                frontier.push_back(make_pair(temp_polje.first - 1, temp_polje.second));
                sobe->at(temp_polje.first - 1).at(temp_polje.second) = '#';
            }
        }
        if(temp_polje.first != n - 1) {
            if(sobe->at(temp_polje.first + 1).at(temp_polje.second) == '.') {
                frontier.push_back(make_pair(temp_polje.first + 1, temp_polje.second));
                sobe->at(temp_polje.first + 1).at(temp_polje.second) = '#';
            }
        }
        if(temp_polje.second != 0) {
            if(sobe->at(temp_polje.first).at(temp_polje.second - 1) == '.') {
                frontier.push_back(make_pair(temp_polje.first, temp_polje.second - 1));
                sobe->at(temp_polje.first).at(temp_polje.second - 1) = '#';
            }
        }
        if(temp_polje.second != m - 1) {
            if(sobe->at(temp_polje.first).at(temp_polje.second + 1) == '.') {
                frontier.push_back(make_pair(temp_polje.first, temp_polje.second + 1));
                sobe->at(temp_polje.first).at(temp_polje.second + 1) = '#';
            }
        }
    }
    // da je ovo klasicni BFS, morala bi se vracati neka vrednost,
    // ali nas cilj je ovde samo da popunimo pronadjenu sobu, samim tim
    // ova funkcija moze biti void
}

int main()
{
    // optimizacija unosa, neophodna za neke zadatke
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cerr.tie(0);

    int n, m; // visina i duzina mape
    int br_soba = 0; // broj soba
    cin >> n >> m;
    vector<vector<char>> sobe(n, vector<char>(m)); // mapa
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> sobe[i][j];
        }
    }

    // resenje zadatka
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(sobe[i][j] == '.') { // nalazenje soba
                br_soba++;
                BFS(&sobe, i, j, n, m); // pustamo BFS kako bi popunili sobu
            }
        }
    }
    
    // ispis resenja
    cout << br_soba << endl;

    return 0;
}
