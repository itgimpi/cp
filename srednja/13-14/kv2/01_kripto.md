---
hide:
  - toc
---

# 1 - Kripto

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 16MB |

Mali Perica bez prestanka igra igricu ”Flappy Bird” još otkako je komisija odlučila da je uvede kao razbibrigu za takmičare između kvalifikacija. Kako je igra veoma frustrirajuća, a Perica nestrpljiv da napreduje na rang listi takmičara (da bi povećao svoje šanse da ode na IOFB – međunarodnu olimpijadu u ”Flappy Bird”-u), odlučio je da iskoristi svoje hakerske sposobnosti i pošalje HTTP zahtev za promenu skora. Međutim, nije slutio da je komisija uvela novu zaštitu protiv hakera – zahtevi sa nerealistično velikim skorovima se moduluju (uzima se ostatak pri deljenju) sa nekom vrednošću pre nego što se upisuju u bazu podataka.

Perica je uspeo da sazna modul koji komisija koristi – međutim još uvek nije savladao samu operaciju modulovanja, tako da vas je zamolio da mu pomognete da odredi koliko poena će biti upisano za neki konkretan zahtev.

## Ulaz
U prvom i jedinom redu standardnog ulaza nalaze se dva cela broja $N$ i $M$, koji predstavljaju skor koji je Perica poslao u svom zahtevu i komisijin modul, redom.

## Izlaz
U prvom i jedinom redu standardnog izlaza treba ispisati vrednost koja će biti upisana u bazu podataka za dati zahtev.

## Primer 1
### Ulaz
```
15 7
```

### Izlaz
```
1
```

## Objašnjenje primera
Perica zahteva da mu se upiše broj $15$, međutim komisija smatra sve skorove sa $7$ ili više poena nerealnim – tako da će zapravo biti upisana vrednost jednaka ostatku pri deljenju $15$ sa $7$, u ovom slučaju $1$.

## Ograničenja

* $0 \leq N \leq 10^{100000}$.
* $1 \leq M \leq 10^{18}$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $20$ poena važi $N \leq 10^9$.
* U test primerima vrednim $20$ poena važi $N \leq 10^{18}$.
* U test primerima vrednim $60$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Petar Veličković | Boris Grubić |

Problem Kripto spada u kategoriju lakših zadataka na drugim Kvalifikacijama. Zbog jednostavnosti formulacije u tekstu zadatka, nije teško prevesti problem u formalno matematički oblik; jedna od mogućih formi je:

*Za data dva cela broja $N$ i $M$, odrediti celi broj $X$ tako da važi $0\leq X < M$ i $N\equiv X (mod M)$.*

Nepažljivom čitaocu se ovo može činiti kao trivijalan zadatak, i bez obaziranja na ograničenja promenljivih (ili možda bez razumevanja tih ograničenja) dobijamo sledeći C++ kod:

```cpp
int N, M;
scanf("%d%d", &N, &M);
printf("%d\n", N % M);
```

Ovakvo rešenje, međutim, donosi samo oko $20$ bodova; celobrojni tip *int* ne podržava brojeve veće od oko $2\cdot 10^9$. Pažljiviji rešavaoci su primetili da je bolje koristiti 64-bitni tip *long long*, koji je ujedno i najveći celobrojni tip koji nam programski jezik nudi. Rešenje se tako transformiše u sledeći oblik:

```cpp
long long N, M;
scanf("%lld%lld", &N, &M);
printf("%lld\n", N % M);
```

Ovakvo rešenje donosi $40$ bodova; dok je ovaj tip svakako većeg kapaciteta, u zadatku možemo da očekujemo brojeve koje imaju i do $100000$ cifara, dok *long long* može da podrži cele brojeve samo do oko $9\cdot 10^{18}$. Jedno moguće rešenje za ovaj problem je kreiranje sopstvene klase za velike brojeve, i zatim implementiranje fukncija deljenja i množenja nad tim tipovima da bi se došlo do operacije modulovanja; ali pažljivim opservacijama možemo dosta pojednostaviti ovaj pristup. Najpre primetimo da, pošto je modul uvek unutar 64-bitne promenljive, da će i rešenje stati u 64-bitni ceo broj. Zatim bi trebalo broj $N$ transformisati u neki oblik koji će nam omogućiti da rešenje računamo u koracima, a da nam ono nikad ne iskoči iz tih granica. Konkretno, ukoliko je $N = \overline{c_k c_{k-1}\ldots c_1 c_0 }$, gde je $k$ broj cifara broja $N$, a $c_i$ njegova $i$-ta značajna cifra, posmatrajmo sledeći polinom, u dve različite forme:

$$
P(x) = c_k x^k+c_{k-1} x^{k-1}+\ldots+c_1 x+c_0
$$

$$
= c_0+x(c_1+x(c_2+x(\ldots+x(c_{k-1}+x(c_k+x\cdot 0))\ldots))).
$$

Ukoliko je $x=10$, onda je ovo očigledno jednako broju $N$. Druga forma nam daje postupan način za računanje ovog modula; možemo, počevši od nule, u svakom momentu da množimo broj sa $10$ i da mu dodamo sledeću cifru broja $N$ (idući sleva nadesno), održavajući sve vreme rezultat po modulu $M$. Ovo možemo uraditi uz pomoć identiteta vezanih za modul zbira i proizvoda dva cela broja:

$$
(a\equiv x (mod M)) \land (b\equiv y (mod M)) \Rightarrow a+b \equiv x+y (mod M)
$$

$$
(a\equiv x (mod M)) \land (b\equiv y (mod M)) \Rightarrow a\cdot b \equiv x\cdot y (mod M)
$$

Konačno rešenje se onda može izraziti u vidu rekurentne veze:

$$
X_0 = 0
$$

$$
X_{i+1} = (((10 mod M)\cdot X_i) mod M+c_{k-i} mod M) mod M
$$

gde je X_{k+1} traženo rešenje. Vremenska složenost ovog rešenja je $O(k)$, dakle $O(log⁡ N)$, i ono je dovoljno za osvajanje $100$ bodova.

**Napomena:** primetite da je u rešenju korišćena promenljiva tipa *unsigned long long*; ovo je urađeno zato što je moguće iskočiti iz opsega *long long* promenljive prilikom množenja sa 10, međutim test primeri nisu sankcionisali ovu grešku; moguće je osvojiti *100* poena i bez korišćenja ovog tipa:

``` cpp title="01_kripto.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Kripto
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

#define MAX_N 100005

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

int len;
char N[MAX_N];
lld M;

inline llu kripto()
{
    llu ret = 0LL;
    for (int i=0;i<len;i++)
    {
        ret *= (10 % M);
        ret %= M;
        ret += ((N[i] - '0') % M);
        ret %= M;
    }
    return ret;
}

int main()
{
    scanf("%s%lld", N, &M);
    len = strlen(N);
    printf("%lld\n", kripto());
    return 0;
}
```
