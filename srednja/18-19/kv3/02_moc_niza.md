---
hide:
  - toc
---

# 2 - Moć niza

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |

Dat je niz $A_{i}$ koji se sastoji od $N$ cifara. Moć niza definišemo kao razliku kvadrata najveće cifre u njemu i kvadrata najmanje cifre u njemu. U jednoj operaciji možete da izbrišete proizvoljnu cifru u nizu. Primeniti najviše $K$ operacija, tako da moć niza koji ostane bude najmanja moguća i ispisati tu moć. Primetite da u nizu posle brisanja može da ostane i samo jedna cifra, u tom slučaju ona je istovremeno i najveća i najmanja, pa je rezultat $0$.

## Opis ulaza

U prvom redu nalaze se brojevi $N$, dužina niza i $K$ najveći broj operacija koje možete primeniti. U drugom redu nalazi se niz od $N$ cifara.

## Opis izlaza

Ispisati najmanju moć niza koji se dobija primenom najviše $K$ operacija na početni niz.

## Primer 1

### Ulaz

~~~
5 4
5 9 6 9 1
~~~

### Izlaz

~~~
0
~~~

## Primer 2

### Ulaz

~~~
5 3
5 9 6 8 1
~~~

### Izlaz

~~~
11
~~~

## Objašnjenje primera
U prvom primeru, izbrisaćemo cifre $9$, $6$, $9$ i $1$.
Tako će nam ostati niz $5$,  kojem je moć $5^2-5^2 = 0$.
U drugom primeru, izbrisaćemo cifre $9$, $8$ i $1$.
Tako će nam ostati niz $5$ $6$,  kojem je moć $6^2 - 5^2 = 11$.

## Ograničenja
* $1 \leq K < N \leq 10^5$
* $0 \leq A_{i} \leq 9$

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 30 poena: $N=3$.
* U test primerima vrednim 20 poena: $N \leq 15$.
* U test primerima vrednim 10 poena: $N \leq 10^3$, $K=1$.
* U test primerima vrednim 10 poena: Sve cifre su ili $1$ ili $2$.
* U test primerima vrednim 30 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Aleksa Milisavljević | Vladimir Milenković | Aleksa Plavšić |

## Analiza

### Način 1

Primetimo da različitih cifara koje mogu da se pojavljuju u broju može da ima najviše 10, tako da možemo uraditi zadatak sledećim postupkom: fiksiramo najmanju i najveću cifru (njihove vrednosti) koje ostaju u broju, i vidimo da li u $K$ operacija možemo izbrisati sve cifre koje su manje od najmanje i veće od najveće. Ukoliko možemo, razlika kvadrata te dve cifre je jedan od kandidata za rešenje, a nama od svih kandidata treba onaj maksimalni.

### Način 2

Ukoliko sortiramo (nekim $O(N \log N)$ algoritmom) sve cifre našeg broja, primetimo da će u optimalnom rešenju biti uzastopni podniz tog sortiranog niza (dužine $N - K$). Takvih podnizova ima $O(N)$, pa možemo proći kroz sve i izabrati onaj koji daje maksimalnu razliku kvadrata.

## Smernice za algoritam

Ukoliko koristimo prvi način potreban nam je brojač pojavljivanja svake cifre u broju kako ne bismo svaki put kad brojimo prolazili kroz ceo broj - složenost implementacije može varirati, ali postoji 10 cifara, tako da bilo šta što koristi nekoliko petlji te dužine prolazi. Ukoliko koristimo drugi način, u ukupnoj složenosti dominira složenost sortiranja - $O(N \log N)$ za neki standardni sort, $O(N)$ ukoliko koristimo counting sort.

``` cpp title="02_moc_niza.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int a[maxn];
int n;
int k;
int br[10];
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++) br[a[i]]++;
	int mk=100;
	int s=0;
	for(int i=0;i<=9;i++) {
		s=0;
		for(int j=i;j<=9;j++) {
			s+=br[j];
			if(s+k>=n) mk=min(mk,j*j-i*i);
		}
	}
	printf("%d",mk);
	return 0;
}

```
