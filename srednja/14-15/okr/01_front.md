---
hide:
  - toc
---

# B1 - Front

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |

Mali Perica je, zahvaljujući vašoj pomoći na prethodnom nivou takmičenja, uspeo da pomogne malom Acku da dobije beta ključ za najnoviju igricu kompanije Mećava. Kako je i sam krenuo da igra ovu igricu, jako mu se svidela, pa je odlučio da isproba i neke starije naslove ovog izdavača.

Igrica koju je sledeću odabrao je klasik ”Ratni Zanat”, a protivnik mu je njegov kolega mali Nikolaj. U ovoj igrici se dva igrača takmiče za prevlast nad protivničkom bazom. Baze se nalaze na suprotnim krajevima mape (Nikolajeva u donjem levom uglu mape, Peričina u gornjem desnom), i mogu se napadati ili braniti pomoću vojnika (koji se u svakom momentu nalaze na nekom paru $(x, y)$ koordinata na mapi).

Perica je u ključnom trenutku pogledao Nikolajev monitor i uspešno prepisao sve pozicije na kojima je Nikolaj rasporedio svoje vojnike, **sortirane u neopadajućem poretku po x koordinati**. Da bi isplanirao efikasan napad, Pericu sada zanima koliko Nikolajevih vojnika je na najranjivijim položajima, tj. na frontu.

Vojnik $V(x, y)$ se nalazi na frontu ukoliko ne postoji nijedan drugi vojnik $V'(x', y')$ takav da važi $x \leq x', y \leq y'$

tj. ukoliko ne postoji nijedan drugi vojnik koji je ”gore-desno” u odnosu na tog vojnika.

## Ulaz
U prvom redu standardnog ulaza nalazi se prirodan broj $N$, koji predstavlja broj Nikolajevih vojnika. U svakom od narednih $N$ redova nalaze se dva cela broja $x_i$ i $y_i$, koji predstavljaju koordinate Nikolajevog tekućeg vojnika. Svi vojnici će biti sortirani u neopadajućem poretku po x koordinati.

## Izlaz
U prvi i jedini red standardnog izlaza ispisati prirodan broj $F$, koji predstavlja broj Nikolajevih vojnika koji se nalaze na frontu.

## Ograničenja:
- $1 \leq N \leq 10^6$
- $0 \leq x_i,y_i \leq 10^9$
- Nikoja dva vojnika neće biti na istoj poziciji.
- $x_1 \leq x_2 \leq \ldots x_N$

Test primeri su podeljeni u tri disjunktne grupe:

- U testovima vrednim 30 poena: $N \leq 500$; $x_i,y_i \leq 1000$; neće biti vojnika sa istom $x$ koordinatom.
- U testovima vrednim 40 poena: $N \leq 1000$
- U testovima vrednim 30 poena: Bez dodatnih ograničenja.

## Primer:
### Ulaz
```
6
0 1
1 5
3 5
3 2
4 4
```

### Izlaz
```
3
```

### Objašnjenje
Front se sastoji od sledećeg skupa vojnika: $\{ (3, 5), (4,4), (5,1) \}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Uroš Vukićević | Aleksandar Ivanović |

## Rešenje za $N\leq20$ i  $x_i,y_i\leq1000$:
Sa obzirom da su vrednosti $x_i$ i $y_i$ male možemo svaku tačku da sačuvamo u matrici $mat$ gde je  $mat[i][j]=1$ ako je uneta tačka sa koordinatama $i$ i $j$, a $mat[i][j] = 0$ u suprotnom. Sada za svaku unetu tačku možemo proveriti da li postoji neka tačka u matrici koja je *gore-desno* od date tačke i tako izbrojati tačke na frontu. Vremenska složenost: $O(N\cdot maxX^2)$, memorijska složenost: $O(N + maxX^2)$, gde je $maxX$ najveća dozvoljena koordinata (u ovom slučaju $1000$).

## Rešenje za $N\leq1000$:
Zbog toga što su $x_i,y_i\leq10^9$ (ne možemo da napravimo toliku matricu) moramo da proverimo broj tačaka na frontu bez matrice.  Broj tačaka na frontu možemo izbrojati tako što ćemo za svaku tačku proći  kroz sve ostale tačke i proveriti da li postoji neka koja je *gore-desno* od nje. Vremenska složenost: $O(N^2)$, memorijska složenost: $O(N)$

## Glavno rešenje:
Znamo da će se za svaku $x$ koordinatu najviše jedna tačka nalaziti na frontu. Pošto su tačke poređane po $x$ koordinati, krećemo sa kraja niza (odnosno, možemo zamisliti zdesna nalevo) i pratimo koja je najveća $y$ koordinata koju smo do sad videli (neka to bude $maxy$), kao i poslednju $x$ koordinatu za koju je $maxy$ ostvareno (nazovimo to $maxx$). Za trenutno $x_i$ dodamo jedan na rezultat ukoliko je $y_i > maxy$ i $x_i \neq maxx$. Pritom održavamo vrednosti $maxx$ i $maxy$.  Vremenska složenost: $O(N)$, memorijska složenost: $O(N)$

``` cpp title="01_front.cpp" linenums="1"
/* 
 Author: Petar 'PetarV' Velickovic
 Task: Front
*/

#include <stdio.h>
#include <algorithm>

#define MAX_N 1000001

using namespace std;

int n;
int X[MAX_N], Y[MAX_N];
int currX, currmY, maxY;
int sol;

int main()
{
    scanf("%d", &n);
    for (int i=0;i<n;i++) scanf("%d%d", &X[i], &Y[i]);
    
    currX = X[n - 1], currmY = Y[n - 1], maxY = -1;
    for (int i=n-1;i>=0;i--)
    {
        if (X[i] == currX) currmY = max(currmY, Y[i]);
        else
        {
            if (currmY > maxY) maxY = currmY, sol++;
            currmY = Y[i];
            currX = X[i];
        }
    }
    if (currmY > maxY) sol++;
    
    printf("%d\n", sol);
    return 0;
}

```
