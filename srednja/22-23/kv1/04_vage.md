---
hide:
  - toc
---

# 4 - Vage

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Miladin prosto ne može da veruje koliko se ugojio. Nije verovao svojoj vagi, pa je kupio novu. Ali onda nije verovao ni novoj vagi, pa je kupio još jednu. Ovaj proces se nastavio dok konačno nije imao $N$ vaga u svom posedu. Tada je odlučio da mora na objektivan način proveriti da li su u pravu njegove vage ili on.

Poređao je sve svoje vage u jedan niz, tako da za vagu koja je $i$-ta sleva kažemo da ima indeks $i$. Nakon toga, za svaku vagu saznao je koje težine ona može da izmeri. Preciznije, za svako $i$, saznao je da vaga sa indeksom $i$ može da izmeri težine između $d_i$ i $u_i$, uključujući i njih (za ostale težine izbacuje grešku).

Za svoje dalje proračune, potrebni su mu odgovori na $M$ pitanja oblika: 

- Za dato $l$, $r$ i $x$, koliko vaga sa indeksima od $l$ do $r$ (računajući i ta dva) može da izmeri težinu $x$?

Pomozite Miladinu sa ovim proračunima kako bi se što pre prebacio na salate. 

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva cela broja $N$ i $M$ - broj vagi koje je prikupio i broj pitanja na koje mu je potreban odgovor. 

Linija $i$ od narednih $N$ linija sadrži $2$ cela broja $d_i$ i $u_i$ - donju i gornju težinsku granicu koju može da izmeri vaga sa indeksom $i$. 

Narednih $M$ linija sadrže po tri cela broja $l_i$, $r_i$ i $x_i$, tim redom - opise pitanja. 

## Opis izlaza
Na standardni izlaz ispisati odgovore na pitanja istim redom kao što su data, svaki u svom redu.

## Primer 1
### Ulaz
```
3 4
21 34
100 100
56 78
2 3 25
1 2 100
1 3 50
2 3 70
```

### Izlaz
```
0
1
0
1
```

## Primer 2
### Ulaz
```
8 5
1 2
4 7
7 12
1 8
7 7
4 6
6 9
9 10
2 6 6
4 6 7
5 8 12
1 8 10
2 7 7
```

### Izlaz
```
3
2
0
2
5
```


## Objašnjenje primera
Prvi primer:

- Prvo pitanje: Nijedna vaga sa indeksom od $1$ do $2$ ne može da izmeri težinu $25$.
- Drugo pitanje: Vaga $2$ može da izmeri težinu $100$.
- Treće pitanje: Nijedna vaga sa indeksom od $1$ do $3$ ne može da izmeri težinu $50$.
- Četvrto pitanje: Vaga $3$ može da izmeri težinu $70$.

Drugi primer:

- Prvo pitanje: između indeksa $2$ i $6$ vage sa indeksima $2$, $4$ i $6$ mogu da izmere težinu $6$.
- Drugo pitanje: između indeksa $4$ i $6$ vage sa indeksima $4$ i $5$ mogu da izmere težinu $7$.
- Treće pitanje: između indeksa $5$ i $8$ nijedna vaga ne može da izmeri težinu $12$.
- Četvrto pitanje: između indeksa $1$ i $8$ vage sa indeksima $3$ i $8$ mogu da izmere težinu $10$.
- Peto pitanje: između indeksa $2$ i $7$ vage sa indeksima $2$, $3$, $4$, $5$ i $7$ mogu da izmere težinu $7$.

## Ograničenja

- $1 \leq N, M \leq 2 \cdot 10^5$.
- $0 \leq d_i \leq u_i \leq 10^9$, za $1 \leq i \leq N$.
- $1 \leq l_i \leq r_i \leq N$, za $1 \leq i \leq M$.
- $0 \leq x_i \leq 10^9$, za $1 \leq i \leq M$.

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 15 poena: $N, M \leq 1000$.
- U testovima vrednim 15 poena: $d_i = u_i$, za $1 \leq i \leq N$.
- U testovima vrednim 20 poena: Ne postoji $x$ koje mogu da izmere dve različite vage.
- U testovima vrednim 20 poena: $u_i \leq 20$,  za $1 \leq i \leq N$.
- U testovima vrednim 30 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Mladen Puzić | Aleksa Milisavljević |

## Rešenje kada $N, M \leq 1000$
Za svako pitanje možemo jednostavno proći kroz sve bitne vage i proveriti da li mogu izmeriti trenutno $x_i$. 

Vremenska složenost je $O(NM)$, a memorijska $O(N)$.

## Rešenje kada $d_i=u_i$
U ovom slučaju potrebno je odrediti, za svako pitanje, koliko vaga kojima je $d_i$ jednako $x_i$ ima indeks od $l_i$ do $r_i$. Pošto nam nisu bitne konkretne vrednosti $d_i$, $u_i$ i $x_i$, već samo da li su jednaki, ove vrednosti možemo kompresovati, na primer koristeći *std::map*, tako da sve budu najviše $N$. Kada to uradimo, možemo za svaki različit element u nizu $d_i$ da napravimo novi niz, koji sadrži, sortirano rastuće, sve indekse vaga kojima odgovara ta vrednost $d_i$. 

Sada, kad je potrebno da odgovorimo na pitanje, možemo koristeći binarnu pretragu da nađemo koliko elemenata u nizu indeksa koji odgovara vrednosti $x_i$ se nalazi na intervalu $[l_i, r_i]$.

Vremenska složenost je $O((N+M)logN)$, a memorijska $O(N)$.

## Rešenje kada ne postoji $x$ koje mogu da izmere dve različite vage
Ovaj uslov se drugačije može napisati da su intervali $[d_i, u_i]$ disjunktni. Sortirajmo intervale po levoj granici, takođe čuvajući indeks svakog intervala. Nakon toga rešavamo pitanja jedno po jedno, tako što binarnom pretragom tražimo poslednji interval kome je leva granica manja od trenutnog $x_i$.  

Ukoliko se $x_i$ ne nalazi u tom intervalu ili se indeks tog intervala ne nalazi u intervalu $[l_i, r_i]$, rezultat za trenutno pitanje je $0$. U suprotnom, rezultat je $1$.

Vremenska složenost je $O((N+M)logN)$, a memorijska $O(N)$.

## Rešenje kada $u_i \leq 20$
Ovaj slučaj se rešava slično slučaju kada važi $d_i = u_i$, s tim što, umesto da ubacimo svaki indeks u niz indeksa samo za vrednost $d_i$, mi ćemo ga ubaciti u niz indeksa za svaku vrednost u intervalu $[d_i, u_i]$. Nakon toga, odgovor na pitanje nalazimo na isti način kao ranije. Potrebno je posebno paziti za slučaj kada $x_i > 20$. 

Vremenska složenost je $O(N\cdot max(u_i) + MlogN)$, a memorijska $O(N)$.

## Glavno rešenje
Kako bismo rešili zadatak za sve bodove, potrebno je da na pitanja odgovaramo *offline*, odnosno u drugačijem redosledu nego što su data, pa ćemo ih na kraju ispisati u tačnom redosledu. Na pitanja ćemo odgovarati u redosledu rastuće po $x_i$ (ukoliko više pitanja ima isto $x_i$, nije bitno na koje odgovaramo prvo). 

Znamo da nam je vaga $j$ bitna samo ako važi $d_j \leq x_i \leq u_j$. Dakle, kako idemo kroz pitanja rastuće po $x_i$, postoje dve vrste događaja: 

- Vaga $j$ postaje bitna prvi put kada postavljamo pitanje za koje važi $x_i \geq d_j$;
- Vaga $j$ prestaje da bude bitna pri put kada postavljamo pitanje za koje važi $x_i \geq u_j+1$.

Ubacimo svih $2N$ događaja u jedan niz i sortirajmo ga rastuće po njihovim granicama za $x_i$. Sada možemo zajedno prolaziti kroz niz pitanja i niz događaja metodom dva pokazivača i održavati niz nula i jedinica dužine $N$ koji na $i$-toj poziciji sadrži $1$ ako i samo ako je vaga sa indeksom $i$ trenutno bitna. Naravno, ovaj niz ćemo menjati svaki put kada na red dođe neki novi događaj.

Kako bismo efikasno odgovorili na pitanje, potrebno je da efikasno nađemo zbir na intervalu $[l_i, r_i]$ ovog niza, u trenutku kada smo obradili sve događaje koji dolaze pre ovog pitanja. Za ovo možemo koristiti segmentno ili Fenvikovo stablo kako bismo ostvarili dobru složenost.

Vremenska složenost je $O((N+M)logN)$, a memorijska $O(N)$.

``` cpp title="04_vage.cpp" linenums="1"
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#define MAXN 200010
using namespace std;
int N, M, l[MAXN], r[MAXN], rez[MAXN];
vector<pair<int, pair<int, int> > > delta; // {granica, {tip, indeks}}
vector<pair<int, int> > q; // {x, indeks}
int bit[MAXN];
void update(int idx, int val) {
  while(idx < MAXN) {
    bit[idx] += val;
    idx += idx&-idx;
  }
}
int query(int idx) {
  int rez = 0;
  while(idx > 0) {
    rez += bit[idx];
    idx -= idx&-idx;
  }
  return rez;
}
int main() {
  //ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  scanf("%d%d", &N, &M); //cin >> N >> M;
  for(int i = 1; i <= N; i++) {
    int d, u; scanf("%d%d", &d, &u); //cin >> d >> u;
    delta.push_back({d, {+1, i}});
    delta.push_back({u+1, {-1, i}});
  }
  for(int i = 1; i <= M; i++) {
    int x; scanf("%d%d%d", &l[i], &r[i], &x); //cin >> l[i] >> r[i] >> x;
    q.push_back({x, i});
  }
  sort(delta.begin(), delta.end());
  sort(q.begin(), q.end());
  int idx = 0;
  for(int i = 0; i < M; i++) {
    while(idx < delta.size() && delta[idx].first <= q[i].first) {
      update(delta[idx].second.second, delta[idx].second.first);
      idx++;
    }
    rez[q[i].second] = query(r[q[i].second]) - query(l[q[i].second]-1);
  }
  for(int i = 1; i <= M; i++) {
    printf("%d\n", rez[i]);
    //cout << rez[i] << endl;
  }
  return 0;
}

```
