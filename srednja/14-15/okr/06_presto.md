---
hide:
  - toc
---

# A3 - Presto

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mačak Cvrle je nakon dugog i iscrpljujućeg lova na prepisivače odlučio da ode u baštu da se odmori. Bašta je podeljena na jedinična polja i ima oblik pravougaone matrice dimenzija $N\times M$. Polje u $i$-tom redu i $j$-toj koloni se nalazi na visini $H_{i,j}$. Kako je mačak uspešno odradio jako težak zadatak, odlučio je da u ovoj bašti sebi napravi presto.

Presto je polje u bašti koje se nalazi na manjoj ili jednakoj visini u odnosu na sva polja u tom redu, i većoj ili jednakoj visini u odnosu na sva polja u toj koloni. Cvrle želi od vas da mu pomognete tako što ćete mu reći koliko najmanje polja u bašti mora da promeni visinu da bi se pojavio bar jedan presto (nove visine ne moraju biti celi brojevi).

## Ulaz
U prvom redu standardnog ulaza nalaze se prirodni brojevi $N$ i $M$, koji predstavljaju broj redova i broj kolona bašte, redom. U svakom od narednih $N$ redova ulaza nalazi se $M$ celih brojeva, razdvojenih razmakom – u $i$-tom od ovih redova $j$-ti broj predstavlja $H_{i,j}$.

## Izlaz
U prvi i jedini red standardnog izlaza ispisati ceo broj $x$, koji predstavlja minimalan broj izmena.

## Ograničenja:
- $1 \leq N,M \leq 300$
- $0 \leq H_{i,j} \leq 10^9$

U primerima vrednim 50 poena važiće 1≤N,M≤100.

## Primer:
### Ulaz
```
3 4
1 9 3 0
6 2 7 5
8 4 6 3
```

### Izlaz
```
1
```

### Objašnjenje primera
Jedan način da napravimo presto je da promenimo visinu polja u drugom redu i drugoj koloni sa $2$ na $8$. Nakon toga, polje u istom tom redu i poslednjoj koloni postaje presto.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | - | Dimitrije Dimić |


``` cpp title="06_presto.cpp" linenums="1"
#include <iostream>

using namespace std;

int main()
{
	return 0;
}
```
