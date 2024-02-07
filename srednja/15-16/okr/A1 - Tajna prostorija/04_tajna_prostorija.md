---
hide:
  - toc
---

# A1 - Tajna prostorija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Egipćani su veoma poznati po njihovim piramidama koje i dan danas predstavljaju pravu enigmu za istoričare. Međutim, istoričari veruju da su na pragu velikog otkrića, ali im je potrebna vaša pomoć. Naime, proučavajući unutrašnjost jedne od piramida, oni su naišli na zid na kome su u jednom redu ispisani razni brojevi. Dobro poznata teorija o jednoj od najpoznatijih kraljica Egipta, svemoćnoj Tamari, glasi da je Tamara bila opčinjena nizovima brojeva gde svi brojevi u nizu imaju bar jednu istu cifru. Istoričari veruju da je niz brojeva napisan na zidu koji su našli baš delo kraljice Tamare i da predstavlja zagonetku čije rešenje vodi do Tajne prostorije gde se nalazi skriveno svo kraljičino blago. 

Istoričari su ubeđeni da je rešenje zagonetke najduži podniz uzastopnih elemenata datog niza brojeva za koji važi da postoji bar jedna cifra koja se nalazi u svim brojevima tog podniza. Pošto oni nisu uspeli da nađu ovaj podniz, oni su vas zamolili za pomoć.

## Opis ulaza
U prvom redu standardnog ulaza se nalazi ceo broj $N$ koji predstavlja dužinu niza brojeva napisanog na zidu. U drugom redu se nalazi $N$ celih brojeva koji predstavljaju brojeve niza.

## Opis izlaza
U prvi i jedini red standardnog izlaza ispisati jedan ceo broj koji predstavlja dužinu najdužeg podniza uzastopnih brojeva datog niza za koji važi da postoji bar jedna cifra koja se nalazi u svim brojevima tog podniza.

## Primer 1
### Ulaz
```
5
123 222 334 443 538
```

### Izlaz
```
3
```
## Primer 2
### Ulaz
```
3
13 456 3
```

### Izlaz
```
1
```
## Objašnjenja primera
U prvom test primeru podniz [334, 443, 538] je dužine 3 i svi njegovi elementi sadr-
že cifru 3. Ne postoji podniz dužine 4 čiji brojevi imaju bar jednu istu cifru.

U drugom test primeru nikoja dva susedna broja nemaju zajedničku cifru, pa je rešenje za taj test primer 1.

## Ograničenja
* $1 ≤ N ≤ 10^6$.
* Svi brojevi u datom nizu brojeva su između $1$ i $10^9$.

## Napomena
Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena važi $1 ≤ N ≤ 100$.
* U test primerima vrednim 30 poena važi $1 ≤ N ≤ 1000$.
* U test primerima vrednim 20 poena važi da su svi brojevi u datom nizu jednocifreni.
* U test primerima vrednim 30 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Boris Grubić | Boris Grubić | Aleksandar Višnjić | Aleksandar Ivanović |

## Prvi podzadatak:
Različitih uzastopnih podnizova ima $\frac{N\cdot(N-1)}{2}$. Možemo zasebno za svaki od njih i svaku cifru izračunati da li se ta cifra pojavljuje u svakom njegovom članu. Vremenska složenost: $O(maxC\cdot N^3)$, gde je $maxC$ broj različitih cifara, u ovom slučaju $10$, memorijska složenost: $O(N)$.

## Drugi podzadatak:
Slično kao u prethodnom podzadatku proveravaćemo istu stvar za svaki podniz, ali efikasnije. Umesto da iznova računamo odgovor za podniz $A_i...A_j$, koristićemo prethodni odgovor za $A_i...A_{j-1}$. Preciznije, ako znamo da se cifra $c$ pojavljuje u podnizu $A_i...A_{j-1}$, potrebno je proveriti samo još element $A_j$. Lako se proverava da li $A_j$ sadrži cifru $c$ (možemo unapred odrediti skup cifara za svaki član niza $A$, ili proći u tom trenutku kroz sve cifre, što je sporija opcija) i na osnovu prethodnog odgovora imamo i sledeći. Dakle, fiksiramo cifru $c$ i levu granicu intervala $l$, pa se krećemo na desno dokle god se cifra $c$ još uvek nalazi u elementima. Vremenska složenost: $O(maxC\cdot N^2)$, memorijska složenost: $O(N)$.

## Treći podzadatak:
Potrebno je naći najduži podniz jednakih elemenata. To radimo sledećim algoritmom: 
Podesimo brojač na $1$. Idemo redom od početka do kraja niza. Ako je trenutni element jednak prethodnom, povećavamo brojač za $1$. U suprotnom ga resetujemo na $1$. Rešenje zadatka je maksimalna vrednost brojača u bilo kom trenutku.  Vremenska složenost: $O(N)$, memorijska složenost: $O(N)$ ili $O(1)$.

## Glavno rešenje:

Postavićemo isto pitanje kao u drugom podzadatku: "Da li je cifra $c$ prisutna u svakom elementu podniza $A_i...A_j$?", ali ćemo koristiti sličan algoritam kao iz trećeg podzadatka i to paralelno nad $10$ različitih nizova nula i jedinica. Te nizove ne pravimo fizički, već ih zamišljamo na sledeći način: $i$-ti član u $c$-tom nizu označava da li element $A_i$ sadrži cifru $c$. Podniz jedinica $[i,j]$ u nekom takvom nizu označava da $A_iA_{i+1}...A_j$ imaju zajedničku cifru.  Efikasna implementacija dovodi do vremencke složenosti $O(maxC\cdot N)$, memorijske $O(maxC)$.

``` cpp title="04_tajna_prostorija.cpp" linenums="1"
#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[1000005];
int has[1000005][10];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        int x = a[i];
        while (x > 0) {
            has[i][x % 10] = true;
            x /= 10;
        }
    }

    int res = 1;
    for (int dig = 0; dig < 10; ++dig) {
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (has[i][dig]) ++cur;
            else {
                res = max(res, cur);
                cur = 0;
            }
        }
        res = max(res, cur);
    }
    
    printf("%d\n", res);
    return 0;
}

```
