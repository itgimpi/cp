---
hide:
  - toc
---

# 2 - Transformacija matrice

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 128MB |

Nakon duge igre sa brojevima, Mabu i Džo su rešili da promene temu njihove zabave. Sada su na red došle matrice! Mabu je napisao na papiru kvadratnu matricu $A$, dok je Džo napisao kvadratnu matricu $B$. Obe kvadratne matrice su iste dimenzije i ona iznosi $n$ (svaka matrica ima tačno $n$ vrsta i $n$ kolona).

Kada su napisali matrice na papiru, Mabu je odjednom poželeo da promeni svoju matricu u onu koju je Džo napisao (želeo je da transformiše matricu $A$ u matricu $B$). Za ovaj poduhvat Mabu sme da koristi sledeće dve operacije proizvoljan broj puta u proizvoljnom redosledu:

$1.$ Promena vrednosti jednog elementa u matrici $A$ - element može da se zameni proizvoljnom vrednošću

$2.$ Rotacija matrice $A$ za $90$ stepeni u desno.

Mabua interesuje minimalan broj operacija koje mora da izvrši na matrici $A$ kako bi dobio matricu $B$.  

## Opis ulaza
Prva linija standardnog ulaza sadrži prirodan broj $n$ , dimenziju kvadratnih matrice koje su napisali Mabu i Džo.

Sledećih $n$ linija standarnog ulaza sadrži po $n$ prirodnih brojeva koji predstaljaju matricu $A$. 

Poslednjih $n$ linija standarnog ulaza sadrži po $n$ prirodnih brojeva koji predstaljaju matricu $B$.

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati minimalan broj operacija potrebnih da se matrica $A$ transformiše u matricu $B$.

## Primer $1$
### Ulaz
```
2
1 2
3 8
6 1
8 5
```

### Izlaz
```
3
```

## Primer $2$
### Ulaz
```
1
5
5
```

### Izlaz
```
0
```

## Objašnjenje primera
U prvom primeru matricu $A$ možemo transformisati u matricu $B$ sa najmanje $3$ koraka.

$1.$ Promena vrednosti polja ($2$, $1$) , $A_{2,1} = 6$.

$2.$ Rotacija matrice za $90$ stepeni u desno.

$3.$  Promena vrednosti polja ($2$, $2$) , $A_{2,2} = 5$.

U drugom primeru matrice $A$ i $B$ imaju samo po jedan element i on ima vrednost $5$ u obe matrice. Nije potrebno izvršiti neku operaciju, tako da je rešenje $0$.

## Ograničenja

* $1 \leq n \leq 1000$.
* $1 \leq A_{i,j}, B_{i,j} \leq 10^9$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim $20$ poena važiće ograničenje $n = 2$.
* U test primerima vrednim $20$ poena za optimalno rešenje biće potrebne samo operacije prvog tipa.
* U test primerima vrednim $30$ poena važiće ograničenje $1 \leq n \leq 50$.
* U test primerima vrednim $30$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Aleksa Plavšić | Dušan Zdravković | Slobodan Mitrović |

Prvo što je potrebno primetiti u zadatku je da redosled operacija koje izvršavamo nad prvom matricom nije bitan. Tj. isto će biti ukoliko prvo promenimo vrednost jednog elementa, pa onda rotiramo matricu, ili ukoliko prvo rotiramo, pa onda zamenimo vrednost. To znači da prvo možemo raditi operacije rotacije, pa tek onda posle toga operacije promene vrednosti.

Takođe, možemo primetiti da nikada nećemo rotirati matricu više od 3 puta, jer ako je rotiramo 4 puta, onda dolazimo u istu poziciju kao na početku. Time smo zadatak sveli na 4 slučaja, u zavisnosti od toga koliko puta smo rotirali matricu (0 do 3 puta). Svaki put kada je rotiramo, proverićemo koliko se elemenata razlikuje, a broj različitih elemenata plus broj trenutnih rotacija do sada nam daje koliko je ukupno potrebno operacija za taj slučaj. Na kraju, zapamtićemo najmanji broj potrebnih operacija koji nam je trebao u nekom od ta 4 slučaja.

## Smernice za algoritam

Za rotaciju kvadratne matrice $A$ veličine $NxN$ za 90 stepeni u desno je potrebno da primetimo da će na mesto polja $(x,y)$ doći polje $(y, N+1-x)$, ukoliko su polja indeksirana počev od 1. Tj. ukoliko želimo da dobijemo matricu $A'$ koja je rotirana verzija matrice $A$, možemo je izračunati preko formule: $A'[x][y] = A[y][N+1-x]$.

``` cpp title="02_transformacija_matrice.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const int maxN=1005;

int a[maxN][maxN],b[maxN][maxN];
int n;

int calc(int a[][maxN],int b[][maxN], int n) //funkcija koja racuna broj polja koja se razlikuju u matricama a i b
{
   int diff=0;

   for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
        if (a[i][j]-b[i][j]) diff++;

    return diff;
}

void rotate(int a[][maxN], int n)
{
    int c[maxN][maxN];

    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        c[j][n-i+1]=a[i][j];

    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        a[i][j]=c[i][j];
}

int main()
{
    scanf("%d",&n);

    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        scanf("%d",&a[i][j]);

    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        scanf("%d",&b[i][j]);

     int ans=calc(a,b,n);

     rotate(a,n);

     ans=min(ans,calc(a,b,n)+1);

     rotate(a,n);

     ans=min(ans,calc(a,b,n)+2);

     rotate(a,n);

     ans=min(ans,calc(a,b,n)+3);

     printf("%d\n",ans);

    return 0;
}

```
