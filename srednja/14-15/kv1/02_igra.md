---
hide:
  - toc
---

# 2 - Igra

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Đurica i Draganče se i pod stare dane takmiče ko je vrsniji haker. Prethodnih decenija su to uvek pokušavali da odrede igrajući razne, često vrlo komplikovane igre. Sada porede svoje veštine pri radu sa upadima na računarske mreže.

Odabrane su mreže računara koji su poređani u niz. Mreža se sastoji od $N$ računara, pri čemu se svaki od njih nalazi u **posebnoj klasi** u mreži, te važi da, ukoliko se bilo koji računar iz klase isključi, tada nijedan računar iz te klase više ne može da funkcioniše, te se automatski isključuje. Đurica i Draganče su od ovoga napravili igru: na izmenično će isključivati neki od krajnjih uključenih računara u nizu. Đurica igra prvi. Pobednik je onaj igrač nakon čijeg poteza su svi računari isključeni. Zbog činjenice da jedna partija ove igre nije reprezentativna, Đurica i Draganče su odlučili da odigraju tri partije.

Međutim, oni su zauzeti drugim poslovima i ne mogu sada da se igraju, pa su ostavili takmičarima ovaj posao. Neophodno je odrediti koji igrač će pobediti u kojoj rundi. Ukoliko ispravno odredite ko ima pobedničku strategiju, oni će vas nagraditi poenima na kvalifikacijama za okružno takmičenje.

## Opis ulaza
U prvom, trećem i petom redu standardnog ulaza se nalaze redom prirodni brojevi $N_1$, $N_2$ i $N_3$, brojevi računara u odgovarajućim partijama. U drugom, četvrtom i šestom redu se nalaze nizovi prirodnih brojeva $A$, $B$, $C$ čije su dužine redom $N_1$, $N_2$, $N_3$, pri čemu vrednost nekog elementa $A[i]$ (odnosno $B[i]$, $C[i]$) predstavlja redni broj klase u kojoj se nalazi $i$-ti računar iz prve runde (odnosno druge, treće).

## Opis izlaza
U tri reda standardnog izlaza ispisati brojeve koji predstavljaju ko ima pobedničku strategiju u prvoj, drugoj i trećoj partiji (tim redom). Ukoliko je u nekoj rundi pobednik Đurica, ispisa ti 1; u suprotnom, ispisati 2.

## Primer 1
### Ulaz
```
4
6 1 6 1
3
2 5 2
2
1 1
```

### Izlaz 
```
2
2
1
```

### Objašnjenje primera
U prvoj partiji, ma kako Đurica igrao na početku, ostaće uključena dva računara koji se nalaze u istoj klasi. Draganče ih u narednom potezu isključuje.

## Ograničenja
* $1 \leq N_1, N_2, N_3 \leq 1000$.
* Klase kojima računari pripadaju su predstavljene prirodnim brojevima ne većim od $10^9$.
* U test primerima ukupno vrednim $20$ poena važi: $1 \leq N_1, N_2, N_3 \leq 2$.
* U test primerima ukupno vrednim $20$ poena važi: $1 \leq N_1, N_2, N_3 \leq 20$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Ivan Stošić | Miloš Purić | Boris Grubić |

## Rešenje za $1 \leq N \leq 2$:
$N$ je dovoljno malo da možemo efikasno proveriti svaki mogući potez igrača i na taj način utvrditi ko pobeđuje u igri. Vremenska složenost: $O(N)$, memorijska složenost: $O(N)$.

## Rešenje za $1 \leq N \leq 20$:
Možemo simulirati igru isprobavajući svaki mogući sled poteza. U svakom potezu igrač može isključiti neki od dva računara sa kraja niza, pa bi ovakav pristup imao vremensku složenost $O(2^N)$ i memorijsku složenost $O(N)$.

## Glavno rešenje:
Nakon svakog poteza jednog od igrača, broj različitih klasa iz kojih postoje upaljeni računari se smanji za jedan. Dakle, ukoliko je na početku broj različitih klasa računara paran, u igri će pobediti Draganče, a u suprotnom Đurica. Pošto brojevi u nizu mogu biti nešto veći, možemo koristiti strukturu poput *C++ map*-e za brojanje različitih vrednosti, pa bi vremenska složenost rešenja bila $O(N \cdot \log(10^9))$ a memorijska složenost $O(N)$.


**Alternativno rešenje možete videti na sledećoj [adresi]().**

``` cpp title="02_igra.cpp" linenums="1"
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int A[1005],N,t,i,br;

int main(){
    for (t=1; t<=3; t++){
        scanf("%d",&N);
        for (i=1; i<=N; i++) scanf("%d",A+i);
        sort(A+1,A+N+1);
        br = 1;
        for (i=2; i<=N; i++) if (A[i]!=A[i-1]) br++;
        printf("%d\n",2-br%2);
    }
    return 0;
}
```
