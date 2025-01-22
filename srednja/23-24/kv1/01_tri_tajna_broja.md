---
hide:
  - toc
---

# 1 - Tri tajna broja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |


Komisija je krišom odabrala tri tajna nenegativna cela broja $X$, $Y$ i $Z$, tako da $0 \leq X \leq Y \leq Z$. 

Da bi sprečila takmičare da se dokopaju ovih tajnih brojeva, Komisija će uz njih takmičarima saopštiti i vrednosti $X+Y$, $X+Z$, $Y+Z$ i $X+Y+Z$. Dakle, Komisija će takmičarima dati sedam vrednosti $X$, $Y$, $Z$, $X+Y$, $X+Z$, $Y+Z$ i $X+Y+Z$ u nekom redosledu. 

Pronađite $X$, $Y$ i $Z$.

## Opis ulaza
U prvom i jedinom redu standardnog ulaza, nalazi se sedam celih brojeva $X$, $Y$, $Z$, $X+Y$, $X+Z$, $Y+Z$ i $X+Y+Z$ u nekom proizvoljnom redosledu (tj. prvi broj iz standardnog ulaza ne mora da bude jedank $X$).

## Opis izlaza
U prvom i jedinom redu standardnog izlaza, ispisati $X$, $Y$ i $Z$. Primetite da važi $0 \leq X \leq Y \leq Z$.

## Primer 1

### Ulaz

```
12 8 5 17 9 3 14
```

### Izlaz

```
3 5 9
```

### Objašnjenje
Na ulazu su redom dati brojevi $X + Z = 12$, $X + Y = 8$, $Y = 5$, $X + Y + Z = 17$, $Z = 9$, $X = 3$, $Y + Z = 14$

## Ograničenja
* $0 \leq X \leq Y \leq Z \leq 10^8$

Test primeri su podeljeni u četiri disjunktne grupe:

* U testovima vrednim 25 poena: $0 = X = Y < Z$.
* U testovima vrednim 25 poena: $0 \leq X \leq Y \leq Z < 100$.
* U testovima vrednim 25 poena: Brojevi iz ulaza su dati u neopadajućem redosledu.
* U testovima vrednim 25 poena: Bez dodatnih ograničenja.

## Napomena

Garantuje se da zadatak ima rešenje i da je to rešenje jedinstveno.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Vladimir Milovanović | Aleksa Milisavljević | Aleksa Milisavljević | Aleksandar Višnjić |

## Rešenje kada $0 = X = Y < Z$

Sedam datih brojeva su $X$, $Y$, $Z$, $X+Y$, $X+Z$, $Y+Z$ i$X+Y+Z$. Kako je $X = 0$ i $Y=0$, to su ovih sedam vrednosti zapravo  $0$, $0$, $Z$, $0$, $Z$, $Z$ i $Z$. Za rešavanje ovog podzadatka, dovoljno je pronaći neku vrednost koja nije nula (ta vrednost mora biti jednaka $Z$) i ispisati dve $0$ (tj. $X$ i $Y$) i tu vrednost (tj. $Z$).


## Rešenje kada $0 \leq X \leq Y \leq Z < 100$

U ovom slučaju možemo iterirati po svim mogućim vrednostima za $X$, $Y$ i $Z$. Ukupno postoji do $10^6$ mogućnosti za $X$, $Y$ i $Z$. Potom je dovoljno da proverimo da li skup vrednosti $X$, $Y$, $Z$, $X+Y$, $X+Z$, $Y+Z$ i$X+Y+Z$ za izabrano $X$, $Y$ i $Z$ odgovara vrednostima sa ulaza. Ovo možemo postići na primer sortiranjem oba skupa i poređenjem svake vrednosti.

## Glavno rešenje

Za glavno rešenje, dovoljno je da primetimo da je najmanja vrednost sa ulaza upravo jednaka $X$. Zaista, važi da je $X \leq Y, Z, X+Y, X+Z, Y+Z, X+Y+Z$. Slično tome, druga najmanja vrednost je jednaka $Y$, jer $Y \leq Z, X+Y, X+Z, Y+Z, X+Y+Z$. Konačno, najveća vrednost sa ulaza mora biti jednaka jednaka $X+Y+Z$, jer $X+Y+Z \geq X,Y,Z, X+Y, X+Z, Y+Z, X+Y+Z$. Dakle dovoljno je pronaći dve najmanje vrednosti (one redom odgovaraju $X$ i $Y$), i oduzeti ih od najveće vrednosti (što odgovara $(X+Y+Z) - X - Y = Z$).

U pretposlednjem podzadatku, niz je dat sortiran i dve najmanje vrednosti odgovaraju prva dva elementa niza, dok najveća vrednost odgovara poslednjem elementu niza. Za poslednji zadatak, možemo da sortiramo niz ili da prolaskom kroz njega odredimo ove vrednosti.

``` cpp title="01_tri_tajna_broja.cpp" linenums="1"
#include<bits/stdc++.h>
#define ll long long
#define inf 1e18
using namespace std;
int nums[7];
int main() {
    for(int i=0;i<7;i++) {
        scanf("%d",&nums[i]);
    }
    sort(nums,nums+7);
    cout<<nums[0]<<" "<<nums[1]<<" "<<nums[6]-nums[0]-nums[1]<<endl;
    return 0;
}

```
