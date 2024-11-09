---
hide:
  - toc
---

# 1 - Kvadrati

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Takmičari nas često pitaju *Šta je kvadrat?*, ali retko ko pita *Kako je kvadrat?*  U ovom zadatku tražimo odgovor na treće pitanje: ako imamo koordinate dve različite tačke, koliko postoji kvadrata kojima su te dve tačke temena, a stranice kvadrata su paralelne nekoj od koordinatnih osa (pravi $x = 0$ ili $y = 0$)? 

Često postavljena pitanja:

- Pitanje: Kako je kvadrat?
- Odgovor: Dobro je, hvala na pitanju.
- Pitanje: Šta je kvadrat?
- Odgovor: Kako vas nije sramota.

## Opis ulaza
U prvoj liniji ulaza nalaze se dva cela broja $x_1$ i $y_1$ -- koordinate prve tačke.
U drugoj liniji ulaza nalaze se još dva cela broja $x_2$ i $y_2$ -- koordinate druge tačke.

## Opis izlaza
U jedinoj liniji izlaza ispisati broj kvadrata kojima su stranice paralelne koordinatnim osama i date tačke su im temena. 

## Ograničenja
- $-10^9 \leq x_1, y_1, x_2, y_2 \leq 10^9$
- date tačke će biti različite, odnosno neće važiti i $x_1 = x_2$ i $y_1 = y_2$

Test primeri su podeljeni u 3 disjunktne grupe:

-   U test primerima vrednim $20$ poena: $-50 \leq x_1, y_1, x_2, y_2 \leq 50$
-   U test primerima vrednim $30$ poena: $-200 \leq x_1, y_1, x_2, y_2 \leq 200$
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz

```
1 1
3 3
```

#### Izlaz
```
1
```

#### Objašnjenje
Jedini odgovarajući kvadrat koji postoji je $\{(1, 1), (3, 3), (1, 3), (3, 1)\}$:

![](https://petljamediastorage.blob.core.windows.net/competitions/kvadrati-sl1.PNG)
### Primer 2
#### Ulaz
```
56 34
105 34
```

#### Izlaz
```
2
```

#### Objašnjenje
Dva odgovarajuća kvadrata koja postoje su $\{(56, 34), (105, 34), (56, 83), (105, 83)\}$ i $\{(56, 34), (105, 34), (56, -15), (105, -15)\}$:

![](https://petljamediastorage.blob.core.windows.net/competitions/kvadrati-sl2.PNG)

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Lazar Milenković | Pavle Martinović |

Primetimo najpre da ako su zadata dva temena na istoj stranici kvadrata, tada mora važiti da je $x_1 = x_2$ ili $y_1 = y2$. Tada postoje dva kvadrata koji ispunjavaju uslove, a oni su centralno simetrični u odnosu na zadatu stranicu. Ako su zadata dva antipodalna (dijametralno suprotna) temena, neophodno je proveriti da važi da je $|x_1 - x_2| = |y_1 - y_2|$. U ovom slučaju postoji tačno jedan kvadrat. U svim ostalim slučajevima rešenje je $0$.

``` cpp title="01_kvadrati.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if(x1 == x2 || y1 == y2) cout << 2 << endl;
    else if(abs(x1-x2) == abs(y1-y2)) cout << 1 << endl;
    else cout << 0 << endl;
    return 0;
}

```
