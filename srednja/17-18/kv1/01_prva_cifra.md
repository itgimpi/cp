---
hide:
  - toc
---

# 1 - Prva cifra

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |

Mabu i Džo mnogo vole da prodaju palačinke. Kako je u ovim hladnim decembarskim danima potražnja za palačinkama značajno opala oni su primorani da kratke zimske dane dodatno prekrate zamišljajući različite brojeve. Mabu je zamislio prirodan broj $A$, dok je Džo zamislio prirodan broj $B$.

Za neki prirodan broj $X$  kažemo da je *lepši* od prirodnog broja $Y$ ako je prva cifra sleva broja $X$ veća od prve cifre sleva broja  $Y$, ili ako su im prve cifre sleva jednake i broj $X$ je veći od broja $Y$.

Mabua i Džoa interesuje koji je od datih brojeva $A$ i $B$ *lepši*.

## Opis ulaza
U prvoj i jedinoj liniji standardnog ulaza nalaze se dva **različita** broja $A$ i $B$, brojevi koje su zamislili Mabu i Džo redom.

## Opis izlaza
Na standardni izlaz je potrebno ispisati *lepši* od brojeva $A$ i $B$.

## Primer 1
### Ulaz
```
4506 29985
```

### Izlaz
```
4506
```

## Primer 2
### Ulaz
```
777 778
```

### Izlaz
```
778
```



## Objašnjenje primera 
U prvom primeru  $A = 4506$  i $B = 29985$. Prva cifra sleva broja $A$ je veća od prve cifre sleva broja $B$ ($4 > 2$), tako da je broj $A$ *lepši* od broja $B$.

U drugom primeru $A =777$  i $B= 778$. Prva cifra sleva broja $A$ je jednaka prvoj cifri sleva broja $B$ (obe iznose $7$), kako važi $778 > 777$ odnosno $B > A$, broj $B$ je lepši od broja $A$.

## Ograničenja

* $1 \leq A,B \leq 10^9$.
* Brojevi $A$ i $B$ su različiti.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede $20$ poena brojevi $A$ i $B$ imaju jednak broj cifara.
* U test primerima koji vrede $20$ poena sve cifre u broju $A$ su jednake i sve cifre u broju $B$ su jednake.
* U test primerima koji vrede $20$ poena važi $A = B + 1$ ili $B = A + 1$.
* U test primerima koji vrede $40$ peona nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Aleksa Plavšić | Dušan Zdravković | Dušan Zdravković |

Zadatak je osmišljen tako da bude najlakši u ovom krugu kvalifikacija. Potrebno je uraditi upravo ono što piše u tekstu - uporediti prvu cifru brojeva, a ukoliko su iste, onda uporediti cele brojeve.

## Smernice za algoritam

Elegantno rešenje je učitati brojeve kao stringove, i uporediti prvi karakter stringa, a ukoliko je prvi karakter isti, onda prebaciti string u broj (npr. koristeći atoi funkciju u C++, ili StrToInt funkciju u Pascalu) i uporediti brojeve jednostavnim poređenjem.

Ukoliko brojeve učitamo u Integer formatu, prvu cifru broja možemo dobiti jednostavnom funkcijom (primer dat u C++):

```
int prvaCifra(int a) {
while (a >= 10) {
a /= 10;
}
return a;
}
```

``` cpp title="01_prva_cifra.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int x,y,x1,y1;

    cin>>x>>y;

    x1=x;
    y1=y;

    while(x1>=10) x1/=10;
    while(y1>=10) y1/=10;

    if (x1>y1 || ((x1==y1) && (x>y))) cout<<x<<"\n"; else
        cout<<y<<"\n";

   return 0;
}

```
