---
hide:
  - toc
---

# 2 - Tabla

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 16MB |

Srbi je dosadila njegova omiljena igra, šah. Pokušao je da igra “Flappy Bird”, ali mu nije bio zanimljiv. Zato je odlučio da napravi novu verziju šaha, koja će se igrati na mnogo većoj tabli, dimenzija $N\times M$.

Pošto mora da kupi farbu kako bi obojio crna polja, moli vas da mu pomognete i izračunate koliko će crnih polja imati njegova šahovska tabla. Zna se da će gornji levi ugao table biti obojen u crno.

## Ulaz
U prvom redu standardnog ulaza se nalaze dva cela broja, $N$ i $M$.

## Izlaz
U prvom redu standardnog izlaza, ispisati broj crnih polja na Srbinoj novoj tabli.

## Primer 1
### Ulaz
```
10 10
```

### Izlaz
```
50
```

## Ograničenja

* $1 \leq N, M \leq 10^9$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $50$ poena važi $1 \leq N, M \leq 1.000$.
* U test primerima vrednim $50$ poena nema dodatnih ograničenja.



#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Mladen Puzić | Nikola Stojiljković |

﻿## Rešenje za $N, M\leq1000$:
Tabla dimenzija $N$ i  $M$ ima $N\cdot M$ polja. U ovom slučaju, to je dovoljno malo polja da ih možemo sve obići i proveriti da li su crna. Ako numerišemo redove brojevima od $1$ do $N$ od gore na dole, a kolone brojevima od $1$ do $M$ sleva nadesno, polje u redu $i$ i koloni $j$ je crno ukoliko važi da je $i+j$ neparno. Vremenska složenost: $O(N\cdot M)$, memorijska složenost: $O(1)$.

## Glavno rešenje:
Ograničenja su sad prevelika da bismo prošli kroz svako polje, ali to nam zapravo nije neophodno. Ukoliko je makar jedno od $N$ i $M$ parno, jasno je da je rešenje $\frac{N\cdot M}{2}$, jer je u svakom redu (ukoliko je $M$ parno), odnosno koloni (ukoliko je $N$ parno), jednak broj crnih i belih polja.
Slično tome, kada su oba neparna, može se zaključiti da je rešenje $\lceil \frac{N\cdot M}{2} \rceil$, gde je $\lceil x \rceil$ gornji ceo deo broja $x$ (najmanji celi broj veći ili jednak broju $x$). Vremenska složenost: $O(1)$, a memorijska: $O(1)$. Pri računanju rezultata, obavezno obratiti pažnju da ne dođe do prekoračenja pri množenju $32$-bitnih brojeva, tj. potrebno je koristiti $64$-bitne podatke (npr. *long long* u C++).

``` cpp title="02_tabla.cpp" linenums="1"
#include <stdio.h>

int main() {

    long long n,m;

    scanf("%lld%lld", &n, &m);

    printf("%lld\n", (n*m+1)/2);

    return 0;
}

```
