---
hide:
  - toc
---

# 1 - Minimalan trud

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Mika je odlučio da neodgovorno pristupi kvalifikacijama, i da se potrudi što je manje moguće oko prvog kruga, a da se ipak kvalifikuje
za okružno takmičenje. Otišao je kod vračare i gledanjem u pasulj saznao koliko će bodova imati u drugom i trećem krugu kvalifikacija. Pošto
pokušava da izbegne što više posla, Mika je odlučio da vas pita koliki je **minimalan broj bodova** koje mora da osvoji u prvom krugu da bi se kvalifikovao?

Podsećamo da se na okružno takmičenje kvalifikuju svi takmičari koji
**na dva najbolja kruga kvalifikacija imaju ukupno barem 256 bodova**.

## Opis ulaza
U prvom redu se nalaze dva cela broja $B$ i $C$: brojevi bodova koje
će Mika osvojiti u drugom i trećem krugu kvalifikacija.

## Opis izlaza
Ispisati najmanji broj bodova koji Mika mora da osvoji u prvom krugu,
tako da se kvalifikuje na okružno takmičenje.

## Ograničenja
* $0 \leq B, C \leq 500$

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim 20 poena: $B + C < 256$.
* U test primerima vrednim 30 poena: $C = 0$.
* U test primerima vrednim 50 poena nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
100 150
```

#### Izlaz
```
106
```

#### Objašnjenje
Ako Mika osvoji 106 bodova u prvom krugu, najbolja dva kruga će biti prvi i treći, i u zbiru će na njima imati tačno potrebnih 256 bodova.

### Primer 2
#### Ulaz
```
300 0
```

#### Izlaz
```
0
```

#### Objašnjenje
Miki nisu potrebni dodatni bodovi, jer će ih osvojiti dovoljno u drugom krugu.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Dimitrije Erdeljan | Dimitrije Erdeljan | Aleksa Milojević |

Ako Mika u drugom i trećem krugu zajedno ima barem 256 bodova, odnosno
$B+C \geq 256$, sigurno će se kvalifikovati, tako da može da osvoji 0
bodova u prvom krugu.

U suprotnom, u krajnjem zbiru će učestvovati prvi krug i bolji od
preostala dva, i minimalan broj bodova je onaj koji daje ukupno 256.
Dakle, znamo da $A + \text{max}(B, C) = 256$, odnosno $A = 256 -
\text{max}(B, C)$.

``` cpp title="01_minimalni_trud.cpp" linenums="1"
#include <iostream>

using namespace std;

int main() {
    int b, c;
    cin >> b >> c;
    if(b + c >= 256) {
        cout << 0 << endl;
    } else {
        cout << 256 - max(b, c) << endl;
    }
    return 0;
}

```
