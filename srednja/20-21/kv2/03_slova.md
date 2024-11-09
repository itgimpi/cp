---
hide:
  - toc
---

# 3 - Slova

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Šetajući gradom, naišli ste na natpis sačinjen od $N$ slova engleskog alfabeta. Iz nekog razloga, zapitali ste se **na koliko je načina moguće obrisati sva slova osim 26, tako da su preostala slova sva različita i poređana redom**?

Pošto ovaj broj može biti veoma velik, potrebno je ispisati samo njegov ostatak pri deljenju sa $10^9 + 7$.

## Opis ulaza
U prvom redu nalazi se broj slova u natpisu $N$.

U drugom redu nalazi se $N$ velikih slova koja (redom) čine natpis.

## Opis izlaza
Ispisati broj načina da se iz natpisa obrišu sva slova osim 26, tako da su preostala slova poređana redom (tj. tako da ostane `ABCDEFGHIJKLMNOPQRSTUVWXYZ`) po modulu $10^9 + 7$.

## Ograničenja
* $1 \leq N \leq 10^6$

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 10 poena: $N \leq 26$
* U test primerima vrednim 20 poena: $N \leq 27$
* U test primerima vrednim 30 poena: $N \leq 3000$
* U test primerima vrednim 40 poena nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
29
AABACDEFGHIJKLMNOPQRSTUVWXYZZ
```

#### Izlaz
```
4
```

#### Objašnjenje
Mogući načini su:

* Obrisati prvo i treće `A` i prvo `Z`.
* Obrisati prvo i treće `A` i drugo `Z`.
* Obrisati drugo i treće `A` i prvo `Z`.
* Obrisati drugo i treće `A` i drugo `Z`.

### Primer 2
#### Ulaz
```
78
AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ
```

#### Izlaz
```
865810542
```

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Dimitrije Erdeljan | Lazar Milenković | Tadija Šebez |

## Rešenja za male primere
Ako je dužina stringa $26$, potrebno je jednostavno proveriti da je zadati string zaista sačinjen od svih slova 'A' do 'Z' u rastućem poretku. Kada je dužina $27$, isti uslov treba da je ispunjen kada se izbaci jedno slovo.

## Kvadratno rešenje
Problem možemo posmatrati kao prebrojavanje (ne nužno uzastopnih) podnizova zadatog natpisa koji čine rastući niz slova od A do Z. Mogući pristup jeste posmatrati jednostavniji potproblem koji se sastoji od prebrojavanja kraćih rastućih podnizova koji se završavaju nekim slovom. Neka $dp_{i, j}$ predstavlja broj rastućih podnizova koji se završavaju na poziciji $i$ i koji su dužine $j$.

Broj podnizova koji se završavaju na poziciji $i$ i imaju dužinu $1$ je $1$ ako je slovo na toj poziciji u natpisu A i $0$ u suprotnom. Ako pretpostavimo da znamo rešenje za sve pozicije pre trenutne, lako možemo izračunati $dp$ vrednosti za trenutnu poziciju. Naime, $dp_{i, j}$ je $0$ za svako $j$ sem za redni broj slova koji je na $i$-tom mestu u natpisu. Za ovo $j$ potrebno je prebrojati sve natpise dužine $j-1$ koji se završavaju pre pozicije $i$. Drugim rečima $dp_{i, j} = \sum_{1\le k <i}dp_{k, j-1}$. Konačno rešenje je suma svih sekvenci koje su dužine 26, odnosno $\sum_{1\le i \le n}dp_{i, 26}$.

## Rešenje u linearnom vremenu
Prethodno rešenje možemo optimizovati čuvanjem sume svih prethodnih vrednosti. Vrednosti u tabeli bile bi određene na sledeći način.

$$
dp_{i, j} =  
\begin{cases}
dp_{i-1, j} + dp_{i-1, j-1}, & \text{ako je na $i$-toj poziciji $j$-to slovo alfabeta}\\
dp_{i-1, j}, & \text{u suprotnom samo prepisujemo prethodnu vrednost}
\end{cases}
$$

Ovakva tabela može se održavati u linearnom vremenu. Primetimo na kraju da pošto uvek ispitujemo samo prethodno polje, memoriju možemo smanjiti korišćenjem samo jednog niza dužine 26.

``` cpp title="03_slova.cpp" linenums="1"
#include <cstdio>

const int N = 1000005;
const int MOD = 1000000007;

int ways[26];
char s[N];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", &s);

    for(int i = 0; i < 26; i++)
        ways[i] = 0;

    for(int i = 0; i < n; i++) {
        int j = s[i] - 'A';
        ways[j] += (j > 0) ? ways[j - 1] : 1;
        if(ways[j] >= MOD) ways[j] -= MOD;
    }

    printf("%d\n", ways['Z' - 'A']);
    return 0;
}

```
