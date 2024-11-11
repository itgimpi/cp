#include <bits/stdc++.h> // OK
using namespace std;
/* K = 2. Broj traženih parova "potpuno razlicitih" takmicara možemo dobiti kao broj svih parova, minus broj parova koji imaju jednak prvi zadatak, minus broj parova koji imaju jednak drugi zadatak, plus broj parova koji imaju jednaka oba zadatka (jer smo takve parove dvaput oduzeli).

Za K = 3 formula je malo složenija: nakon oduzimanja parova koji imaju isti prvi, pa drugi, pa treci zadatak, dodajemo parove koji imaju jednaka dva zadatka (prvi i drugi, pa prvi i treci, pa drugi i treci)
jer smo ih dvaput oduzeli, i na kraju ponovo oduzimamo parove koji imaju jednaka sva tri zadatka jer
smo ih prethodno triput oduzeli i triput pribrojili.

Za proizvoljno K, koristi se formula uključivanja: 
oduzimaju se parovi koji se 1 od 4 podudaraju u podskupu s neparnim brojem zadataka, 
a dodaju oni koji se podudaraju u podskupu s parnim brojem zadataka.
Za svakog takmičara se naprave 2K "signatura", od kojih se svaka sastoji od njegovih poena za odredjeni podskup zadataka (npr. prvi, treci i cetvrti zadatak). 
Za odredjeni podskup, odgovarajuce signature svih takmičara možemo sortirati i tako pronaci broj parova takmičara koji se u njima podudaraju, jer ce jednake signature biti uzastopne u sortiranom nizu. 
Taj broj parova oduzimamo ili dodajemo konacnom rezultatu zavisno od parnosti podskupa, tj. parnosti broja zadataka u signaturi. */

int poeni[50000][4];
vector< vector<int> > signature[1 << 4]; // 16, 00001 -> 10000

int main() {
    ios::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++)
            cin >> poeni[i][j];
        for (int maska = 1; maska < 1 << k; maska++) {
            vector<int> t;
            for(int j = 0; j < k; j++)
                if ((maska >> j) & 1)
                    t.push_back(poeni[i][j]);
            signature[maska].push_back(t); }  }

    long long sol = (long long)n * (n - 1) / 2;
    for (int maska = 1; maska < 1 << k; maska++) {
        sort(signature[maska].begin(), signature[maska].end());
        long long parova = 0;
        long long istih = 0;
        vector<int> prev;
        for (auto &t : signature[maska]) {
            if (t == prev)
                ++istih;
            else {
                parova += istih * (istih - 1) / 2;
                istih = 1;
                prev = t; } }

        parova += istih * (istih - 1) / 2;
        if (__builtin_popcount(maska) & 1) // 
            sol -= parova;
        else
            sol += parova;     }
    cout << sol << endl;
    return 0; }