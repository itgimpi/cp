---
hide:
  - toc
---

# 1 - Pikado

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 512MB |


Miloš, naš omiljeni heroj, koji je od prošlog susreta pomislio da je dobra ideja da se preseli u dvodimenzionalni univerzum, je odlučio da krene da igra Pikado. Pikado je igra u kojoj igrač baca iz ruke strelice ka meti koja je podeljena na više polja. Međutim, u dvodimenzionalnom univerzumu meta ne izgleda kao krug, već je predstavljena kao duž. 

Miloševa meta se sastoji od centralnog polja, $N$ polja koja se nalaze levo od centra, i $N$ polja koja se nalaze desno od centra. Centralno polje je obeleženo brojem $0$, polja levo od centra su obeležena brojevima $-N, \ldots, -3, -2, -1$, dok su polja desno od centra obeležena brojevima $1,2,3,\dots,N$.

Miloš će da baci tačno $N$ strelica u metu, i za svaku će da zabeleži u koje polje je udarila. Može se računati na to da je Miloš dovoljno precizan da pogodi metu tokom svakog bacanja. 

Svako polje na tabli se sve više troši što više strelica udari u njega. Miloš smatra da neko polje treba da se zameni ako ga je pogodilo barem $K$ strelica.  Kako je on loš u matematici, zamolio vas je da mu kažete oznake svih polja koja treba da zameni.

## Opis ulaza

U prvoj liniji standardnog ulaza, nalaze se prirodni brojevi $N$ i $K$.

U drugom redu, nalazi se $N$ celih brojeva $A_1, A_2, \dots,A_N$, gde $A_i$ predstavlja oznaku polja koje je Miloš pogodio tokom $i$-tog bacanja.

## Opis izlaza

U prvi red standardnog izlaza, ispisati broj polja koja treba zameniti.
U drugom redu ispisati oznake svih takvih polja. Oznake se mogu ispisati u bilo kom redosledu.

## Primer 1

### Ulaz

```
6 2
1 2 -6 2 4 4
```

### Izlaz

```
2
2 4
```

## Primer 2

### Ulaz

```
6 2
1 -1 0 -1 -1 0
```

### Izlaz

```
2
-1 0
```

## Ograničenja

- $1 \leq N, K \leq 10^6$
- $-N \leq A_i \leq N$

Test primeri su podeljeni u 3 disjunktne grupe:

- U test primerima vrednim $25$ poena: $N \leq 1000$.
- U test primerima vrednim $25$ poena: $A_i \in \{-1, 0, 1\}$.
- U test primerima vrednim $50$ poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Pešić | Lazar Milenković | Filip Ćosović | Nikola Pešić |


## Analiza
Potrebno je naći sve elemente niza $A$ koji se pojavljuju bar $K$ puta u nizu. Elementi niza $A$ su u intervalu $[-N,N]$ tako da postoji $2 \cdot N+1$ različitih vrednosti koje se mogu pojaviti u nizu. Možemo iskoristiti pomoćni niz $B$ dužine $2 \cdot N+1$ koji predstavlja broj pojavljivanja svakog elementa u početnom nizu.  

Na početku niz $B$ ima vrednost $0$ na svakoj poziciji. Jednim prolaskom kroz niz $A$, kada naiđeimo na element $A_i$ povećavamo broj pojavljivanja tog elementa za $1$. Pošto ne možemo pristupiti negativnim indeksima broj pojavljivanja elementa koji ima vrednost $X$ pamtimo u nizu $B$ na poziciji $X+N$. Tako je interval $[-N,N]$ preslikan u interval $[0, 2 \cdot N]$ što nam omogućava da koristimo niz. 

Prolaskom kroz niz $B$ prebrojavamo i ispisujemo sve brojeve koji su se pojavili bar $K$ puta u nizu. Ako za neko $j$ važi da je $B[j] \geq K$ to znači da se broj $j-N$ pojavio bar $K$ puta. 

Implementacija korišćenjem niza je složenosti $O(N)$. Može se koristiti i struktura zasnovana na pretraživačkom stablu (`std::map` složenosti $O(N \log N)$) ili heš tabela (`std::unordered_map` očekivane složenosti $O(N)$) što nam omogućava rešenje i kada su elementi niza $A$ mnogo veliki i nemamo dovoljno memorije da napravimo niz koji obuhvata sve potencijalne vrednosti.

``` cpp title="01_pikado.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 16;

int n, k, cnt[MAXN * 2];
vector<int> sol;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        string inFileName = argv[1];
        string outFileName = inFileName.substr(0, inFileName.length() - 2) + "out";
        freopen(inFileName.c_str(), "r", stdin);
        freopen(outFileName.c_str(), "w", stdout);
    }
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x + MAXN]++;
    }
    for (int i = 0; i < 2 * MAXN; i++) {
        if (cnt[i] >= k) {
            sol.push_back(i - MAXN);
        }
    }
    cout << sol.size() << endl;
    for (auto x : sol) {
        cout << x << " ";
    }
    return 0;
}

```
