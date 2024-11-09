---
hide:
  - toc
---

# 2 - Uzgajivači jabuka

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Možda niste znali, ali uzgajanje jabuka je postalo vrlo isplativ i unosan biznis u svetu. Na svetu postoji $N$ uzgajivača jabuka, $i$-ti uzgajivač zarađuje $A_i$ dolara godišnje. Ipak stvari nisu tako jednostavne zbog Svetske poreske agencije uzgajivača jabuka (u nastavku teksta SPAUJ). SPAUJ želi da uvede fiksan godišnji porez za sve uzgajivače jabuka (fiksan procenat od zarade koji bi uzgajivači plaćali). Uzgajivači su shvatili da ako porez bude suviše visok oni uopšte neće raditi, samo da SPAUJ ne bi zaradio neki dolar od njih. Konkretnije, ako porez bude **striktno veći** od $P_i$ procenata, $i$-ti uzgajivač će odustati od posla.

Nas interesuje koliko najviše može zaraditi SPAUJ godišnje u dolarima ako optimalno postavi porez. 

## Opis ulaza
* U prvoj liniji standardnog ulaza nalazi se prirodan broj $N$, broj uzgajivača javuka u svetu.

* U svakoj od narednih $N$ linija standardnog ulaza nalazi se po dva broja, $A_i$ i $P_i$, početna zarada $i$-tog uzgajivača i maksimalan porez u procentima koji $i$-ti uzgajivač želi prihvatiti.   

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati maksimalnu godišnju zaradu SPAUJ-a.

## Ograničenja
* $1 \leq N \leq 2\cdot 10^5$
* $1 \leq A_i \leq 10^6$
* $0 \leq P_i \leq 100$
* Elementi niza $P$ su nenegativni realni brojevi sa najviše dve decimale.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim $20$ poena: $N \leq 1000$
* U test primerima vrednim $20$ poena: elementi niza $P$ su celi brojevi  
* U test primerima vrednim $20$ poena: svi elementi niza $A$ su jednaki
* U test primerima vrednim $40$ poena nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
4
100001 83.2
40001 20
90001 77.32
300001 1.88
```

#### Izlaz
```
146909.5464
```

#### Objašnjenje
Za SPAUJ je optimalno da postavi porez od $77.32\%$. U tom slučaju bi drugi i četvrti uzgajivač odustali od posla, dok bi prvi i treći dali $77.32\%$ od svoje zarade. Na ovaj način, SPAUJ bi zaradio $(100001 + 90001) \cdot 77.32\% = 146909.5464$ dolara godišnje. 

## Napomene
* Da bi se rezultat priznao kao tačan, apsolutna greška mora biti manja od $10^{-2}$.
* Zbog veličine rezultata, koristite 64-bitne tipove realnih brojeva (npr. u C++ tip `double`).

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Aleksa Plavšić | Mladen Puzić | Mladen Puzić |

Glavna ideja u ovom zadatku je da će SPAUJ uvek odabrati kao stopu poreza jedan od elemenata niza $P$. Da bismo to dokazali, pretpostavimo suprotno, da nam je optimalno uzeti za porez $x$ posto, gde je $x$ različito od svih elemenata niza $P$. Uzmimo prvi veći element niza $P$ i označimo ga sa $y$. Može se lako primetiti da će za oba ta izbora (i $x$ i $y$) isti uzgajivači nastaviti da rade, ali pošto važi $x < y$, SPAUJ će uzeti veći procenat novca od tih uzgajivača ako izabere $y$. Samim tim, $x$ nije optimalno što je u kontradikciji sa našom pretpostavkom. Dakle, jedine opcije za porez su elementi niza $P$.

### Rešenje kad su elementi niza $P$ celi brojevi:
Na osnovu prethodnog zaključka možemo videti da je potrebno proveriti samo sve celobrojne procente, odnosno da porez bude ceo broj od $0$ do 100. To znači da ćemo najviše $101$ put proći kroz niz, što je svakako dovoljno brzo. Vremenska složenost je $O(N)$. 

### Rešenje za $N \leq 1000$:
Proverimo prolaskom kroz niz svaki od $N$ elemenata niza $P$. Vremenska složenost je $O(N^2)$.

### Rešenje kad su svi elementi niza $A$ jednaki:
Za rešenje ovog podzadatka morate pitati vračaru Miljanu.

### Glavno rešenje:
Sortiramo sve uzgajivače po vrednosti niza $P$ opadajuće (dakle, sortiramo nizove $A$ i $P$ zajedno). Sada za dati element niza $P$ možemo u $O(1)$ proveriti koliko bi SPAUJ zaradio za takav porez koristeći prefiksnu sumu nad nizom $A$ (niz u kojem za svako $i$ čuvamo sumu prvih $i$ elemenata). Vremenska složenost je $O(NlogN)$, zbog sortiranja.

``` cpp title="02_jabuke.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const int maxN = 2e5 + 10;

int id[maxN], a[maxN];
double p[maxN];

bool cmp(int x, int y)
{
    return p[x] > p[y];
}

int main()
{
    int n;

    scanf("%d",&n);

    for (int i = 1;i<=n;i++){
        scanf("%d%lf",&a[i], &p[i]);
        id[i] = i;
    }

   sort(id + 1, id + n + 1, cmp);

   long long sum = 0;
   double ans = 0;

   for (int i = 1;i<=n;i++)
   {
       sum+=a[id[i]];
       ans = max(ans, p[id[i]] * sum);
   }

   printf("%.3lf", ans/100.00);
}

```
