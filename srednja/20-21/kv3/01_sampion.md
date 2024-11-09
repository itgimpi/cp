---
hide:
  - toc
---

# 1 - Šampion

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Sedmostruki svetski šampion, Džonas Njubauer sprema se za sledeće svetsko prvenstvo u Klasičnom Tetrisu. Pošto zna da njegova konkurencija vredno vežba, uključujući i njegovog mladog rivala Džozefa koji se skoro pojavio na Tetris sceni, slobodnom procenom je zaključio da mu je potrebno još ukupno $T$ minuta igranja kako bi obezbedio svoju osmu titulu. Smislio je sledeći plan treniranja.

Naizmenično će igrati Tetris $X$ minuta, pa $Y$ minuta odmarati oči i piti kafu. Kada završi sa odmorom, ponovo će se vratiti na igranje Tetrisa i tako u krug dok ukupno ne odigra tačno planiranih $T$ minuta (prestaje da trenira u trenutku kada završi $T$-ti minut igranja).

Koliko mu je ukupno potrebno minuta od početka treninga (računajući i vreme za odmor između igranja) kako bi odigrao $T$ minuta Tetrisa?

Bum! Tetris za Džonasa! <3

## Opis ulaza
U jedinoj liniji ulaza nalaze se tri cela pozitivna broja $X$, $Y$ i $T$. 

## Opis izlaza
U jedinoj liniji izlaza ispisati koliko minuta je potrebno od početka treninga kako bi Džonas odigrao $T$ minuta Tetrisa.

## Ograničenja
- $1 \leq X, T \leq 10^{15}$ (Džonas je vrlo posvećen Tetrisu, **pogledajte napomenu**)
- $1 \leq Y \leq 1000$

Test primeri su podeljeni u 3 disjunktne grupe:

-   U test primerima vrednim $20$ poena: $T \leq 2\cdot X$, $1 \leq X, T \leq 10^9$
-   U test primerima vrednim $30$ poena: $1 \leq X, T \leq 1000$
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz
```
5 4 8
```

#### Izlaz
```
12
```

#### Objašnjenje
Džonas će odigrati $5$ minuta Tetrisa, nakon čega će odmoriti $4$ minuta. Posle toga, odigraće još $3$ minuta Tetrisa i time završiti $8$ minuta igranja.
### Primer 2

#### Ulaz
```
3456 1 1800
```

#### Izlaz
```
1800
```

#### Objašnjenje
Džonas će odigrati svih $1800$ minuta pre nego što mu bude bila potrebna pauza. 

### Primer 3
#### Ulaz
```
305 534 13413413003
```

#### Izlaz
```
36897880205
```

## Napomena
* Zbog veličine brojeva, koristite 64-bitne tipove celih brojeva (npr. u C++ tip `long long`).

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Mladen Puzić | Pavle Martinović |

## Rešenje za $T \leq 2\cdot X$ i $1 \leq X, T \leq 10^9$:
Postoje samo dve moguće situacije: ako važi $T \leq X$, onda će Džonas neće morati da pauzira i rešenje je $T$. Ako $X< T \leq 2\cdot X$, Džonas će morati da napravi jednu pauzu, pa je rešenje u tom slučaju $T+Y$.

## Rešenje za $1 \leq X, T \leq 1000$:
Možemo simulirati Džonasovo igranje, ili minut po minut ili u blokovima od $X+Y$ minuta. Ovo rešenje je presporo da bi radilo za $100$ poena.

## Glavno rešenje:
Primetimo da će za svakih odigranih punih $X$ minuta, Džonas pauzirati $Y$ minuta. Takvih blokova će biti $\lfloor \frac{T}{X} \rfloor$, gde je $\lfloor x \rfloor$ ceo deo od $x$. Onda će rešenje biti $\lfloor \frac{T}{X} \rfloor \cdot (X+Y) + T\%X$, gde je $T\%X$ ostatak pri deljenju $T$ sa $X$ (odnosno ono što mu ostane da odigra nakon poslednje pauze). Jedini izuzetak ovoj formuli jeste situacija kada $X$ deli $T$. Tada nećemo imati pauzu u poslednjem bloku, pa je potrebno da od prethodne formule oduzmemo $Y$.

``` cpp title="01_sampion.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    long long X, Y, T; cin >> X >> Y >> T;
    long long rez = 0;
    if(T%X == 0) rez = (T/X)*(X+Y)-Y;
    else rez = (T/X)*(X+Y) + T%X;
    cout << rez;
    return 0;
}

```
