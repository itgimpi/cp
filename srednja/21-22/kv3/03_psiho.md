---
hide:
  - toc
---

# 3 - Psiho

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Zovete se Patrik Bajtmen. Imate dvadeset i sedam godina. Brinete o sebi balansiranom dijetom, strogim režimom treninga. Ujutru, ako vam je lice naduveno, stavićete ledenu masku dok radite zadatke iz programiranja. Možete da ih uradite hiljadu trenutno...

Radite u jednoj programerskoj firmi, i želite da stignete do vrha, samog vrha. Hijerarhija firme je u obliku stabla, odnosno svaka osoba, sem direktora, ima tačno jednog nadređenog. U firmi radi $N$ osoba i one su numerisane od $1$ do $N$. Za svaku osobu znate njihovog nadređenog, sem osobe $1$, koja predstavlja direktora. 

Opsednuti ste vizit kartama i zato pratite kuda one prolaze kroz kompaniju. Odavno ste primetili da one uvek idu uz hijerarhiju, odnosno *na gore* (osoba je uvek daje svom nadređenom). Tačno $M$ vizit karti će biti pušteno u cirkulaciju i za svaku znate u kom minutu će se to desiti, kao i koja osoba će to uraditi. 

Sve osobe koje trenutno poseduju nečiju vizit kartu proslediće je narednog minuta svom nadređenom. Preciznije, ukoliko se neka vizit karta u minutu $t$ nalazi kod osobe $a$, u minutu $t+1$ nalaziće se kod osobe koja je nadređena osobi $a$. Ako se ta vizit karta nalazi kod šefa, on će je skloniti u svoju kolekciju, na bezbedno. Ukoliko nekoj osobi (uključujući direktoru) u istom trenutku stigne više od jedne vizit karte, ta osoba će uzeti neke dve vizit karte, uporediti ih i obe baciti u đubre. To će ponavljati dokle god mu ne ostane najviše jedna vizit karta. Na primer, ako u trenutku $t$ nekoj osobi stigne $5$ vizit karti, ta osoba će prvo uzeti dve, uporediti ih, pa baciti, i onda ponovo to uraditi sa sledeće dve karte. Preostalu vizit kartu proslediće nadređenom u trenutku $t+1$. U slučaju da joj je stiglo $4$ vizit karte, nakon poređenja joj ne bi ostala ni jedna, pa ne bi imala šta da prosledi.

Vas, Patrika Bajtmana, zanima koliko vizit karti je bačeno u đubre. Zašto? Zato što ste vi srbijanski psiho.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva  cela broja $N$ i $M$ - broj osoba u firmi i broj vizit karti koje će biti u cirkulaciji.

U drugom redu standardnog ulaza nalazi se niz celih brojeva $p_2,  p_3, \ldots, p_N$ dužine $N-1$, gde $p_i$ predstavlja oznaku osobe koja je nadređena osobi $i$. 

Narednih $M$ linija sadrže po dva cela broja $t_i$ i $v_i$ - minut u kojem se pojavila $i$-ta vizit karta i oznaka osobe kod koje se pojavila. I ova vizit karta se računa u karte koje su *stigle* kod osobe $v_i$ u trenutku $t_i$.

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati ceo broj koji predstavlja broj vizit karti koje su bačene u đubre. 

## Primer 1
### Ulaz
```
6 6
1 2 2 2 4 
3 6
7 3
7 5
8 5
7 1
4 4
```

### Izlaz
```
4
```

### Objašnjenje
Prva i šesta vizit karta će se naći u isto vreme kod osobe $4$ i one će se odbaciti. Slično, druga i treća vizit karta će se naći kod osobe $2$ i onda će ih odbaciti. Četvrta i peta vizit karta će neometano doći do direktora.

## Primer 2
### Ulaz
```
5 10
1 1 1 1 
4 4
3 3
3 4
2 2
2 3
2 4
1 2
1 3
1 4
1 5
```

### Izlaz
```
8
```

### Objašnjenje
Prva vizit karta neometano stiže do direktora. Druga i treća vizit karta stižu kod direktora u trenutku $4$ i on ih odbacuje. Četvrta, peta i šesta karta stižu kod direktora u trenutku $3$ i on uzima dve nasumične i odbacuje ih, a treću čuva za kolekciju. Sedma, osma, deveta i deseta se sve odbacuju, stižu u trenutku $2$.

## Ograničenja

- $1 \leq N, M \leq 10^5$
- $1 \leq p_i \leq N$, $p_i < i$, za $2 \leq i \leq N$
- $1 \leq t_i \leq 10^9$, za $1 \leq i \leq M$
- $1 \leq v_i \leq N$, za $1 \leq i \leq M$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 15 poena: $N, M \leq 1000$.
- U testovima vrednim 20 poena: $p_i = i-1$, za $2 \leq i \leq N$.
- U testovima vrednim 20 poena: $t_i = 1$, za $1 \leq i \leq M$ .
- U testovima vrednim 40 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Mladen Puzić | Igor Pavlović |

## Rešenje za $N, M \leq 1000$
Ovde je moguće primeniti razna sporija rešenja, npr. možemo održavati skup *aktivnih* vizit karti, odnosno onih koje nisu još odbačene ili sačuvane od strane direktora. Svakog trenutka, sve aktivne vizit karte šaljemo nadređenom i onda simuliramo poređenje vizit karti. Vremenska složenost: $O(N\cdot M)$, memorijska složenost: $O(N+M)$.

## Rešenje za $p_i = i-1$
U ovom slučaju hijerarhija kompanije je linearna, tj. samo put od svakog zaposlenog do direktora. Najbitnija obzervacija u ovom zadatku jeste da možemo ignorisati sva susretanja vizit karti pre direktora. Ako su se dve karte susrele pre direktora, zajedno će i stići kod direktora, gde će se svakako porediti i odbaciti.

Ovo nam govori da je dovoljno da za svaki trenutak odredimo koliko vizit karti stiže kod direktora tad. Karta koja se pojavila u trenutku $t_i$ kod osobe $p_i$ će kod direktora stići u trenutku $t_i+p_i-1$, pa koristeći npr. strukturu *map* ili obično sortiranje, odrediti sve što nam je potrebno da izračunamo koliko karata će biti odbačeno (ukoliko u trenutku $t$ stiže $x$ karata kod direktora, tada on odbacuje $\lfloor \frac{x}{2} \rfloor \cdot 2$ vizit karti. Vremenska složenost: $O(N+MlogM)$, memorijska složenost: $O(N+M)$. 

## Rešenje za $t_i = 1$
Rešenje je slično glavnom rešenju, samo što je moguće izbeći mapu/sortiranje, i lakše je primetiti pogrebu za dubinama zaposlenih.

## Glavno rešenje:
Poput rešenja kada $p_i = i-1$, ignorišemo poređenja sem kod direktora. Jedina razlika je što ovaj put moramo drugačije da izračunamo u kom trenutku će se neka karta naći kod direktora. Potrebno je da izračunamo *dubinu* svakog zaposlenog, odnosno koliko je sekundi potrebno da vizit karta od osobe $i$ stigne do direktora (označimo to sa $d_i$). 

Za ovo je moguće koristiti grafovske algoritme, ali pošto važi $p_i < i$ to nije neophodno. Dovoljno je da to uradimo koristeći sledeće formule: $d_1 = 0$
 i $d_i = d_{p_i} + 1$. Kada to izračunamo, vreme kada će neka karta doći do direktora je $t_i + d_{v_i}$. Vremenska složenost: $O(N+MlogM)$, memorijska složenost: $O(N+M)$.


``` cpp title="03_psiho.cpp" linenums="1"
#include <bits/stdc++.h>
#define PRINT(x) cerr<<#x<<'='<<x<<endl;
#define NL(x) " \n"[(x)]
#define lld long long
#define pil pair<int,lld>
#define pli pair<lld,int>
#define pll pair<lld,lld>
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define mid ((l+r)/2)
#define endl '\n'
#define all(a) begin(a),end(a)
#define sz(a) int((a).size())
#define LINF 1000000000000000LL
#define INF 1000000000
#define EPS 1e-9
using namespace std;
int solve(int N, int M, vector<int> p, vector<pair<int, int> > cards) {
    int dub[N+1];
    dub[1] = 0;
    for(int i = 2; i <= N; i++) {
        dub[i] = dub[p[i-2]] + 1;
    }
    map<int, int> cnt;
    for(auto x : cards) {
        cnt[x.first + dub[x.second]]++;
    }
    int rez = 0;
    for(auto x : cnt) {
        rez += x.second - x.second%2;
    }
    return rez;
}
int main() {
    ios::sync_with_stdio(false); //cin.tie(0);
    int N, M; cin >> N >> M;
    vector<int> p;
    int cnt = 0;
    for(int i = 0; i < N-1; i++) {
        int x; cin >> x;
        p.push_back(x);
    }
    vector<pair<int, int> > cards;
    for(int i = 0; i < M; i++) {
        int t, v; cin >> t >> v;
        cards.push_back({t, v});
    }
    cout << solve(N, M, p, cards) << endl;
    return 0;
}

```
