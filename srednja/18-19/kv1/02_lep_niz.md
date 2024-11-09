---
hide:
  - toc
---

# 2 - Lep niz

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Aleksa je za rođendan od svoje mame dobio niz od $N$ celih brojeva. Takođe, od tate je dobio $C$ tokena za aktivaciju čarobne moći. Aleksa može iskoristiti čarobnu moć tako da poveća tačno jedan broj u nizu za 1, i to ga košta 1 token. On može koristiti moć proizvoljno mnogo puta na svakom elementu niza, ali sveukupno ne može iskoristiti moć više od $C$ puta.

Neka je lepota niza definisana kao suma $K$-tih stepena svih brojeva u nizu.

Aleksa zna da će ga drugari iz odeljenja ceniti onoliko koliko je lep niz koji on ima. Pomozite Aleksi da maksimizuje lepotu njegovog niza, kao i da izračuna najmanji broj čarobnih moći koje mora da iskoristi kako bi dostigao tu vrednost lepote niza. 

**Napomena: u ovom zadatku, podrazumevati da je $0^0 = 0$.**

## Opis ulaza

U prvoj liniji standardnog ulaza dati su celi brojevi $N$, $C$, i $K$, redom.
U sledećoj liniji je dato $N$ celih brojeva, razdvojenih razmakom, koji predstavljaju elemente niza.

## Opis izlaza

U prvoj liniji standardnog izlaza treba ispisati dva cela broja, gde prvi predstavlja maksimalnu dostižnu vrednost lepote niza, a drugi minimalan broj moći koje se moraju iskoristiti kako bi se dostigla ta vrednost.

## Primer 1

### Ulaz

~~~
3 1 2
-5 3 -4
~~~

### Izlaz

~~~
57 1
~~~

## Primer 2

### Ulaz

~~~
3 0 0
0 0 0
~~~

### Izlaz

~~~
0 0
~~~

## Objašnjenje primera

U prvom test primeru, optimalno je da povećamo broj 3 na 4, Rešenje je $25 + 16 + 16 = 57$.

U drugom test primeru, $C = 0$, te ne možemo menjati nijedan element niza. Rešenje je $0 + 0 + 0 = 0$. (videti napomenu)

## Ograničenja

U svim podzadacima:

- $1 \leq N \leq 100.000$
- $0 \leq C \leq 1.000.000.000$
- Svi elementi niza su po apsolutnoj vrednosti manji ili jednaki $100.000$
- $0 \leq K \leq 2$

Test primeri su podeljeni u 3 disjunktne grupe:

- U test primerima vrednim 30 poena: $N \leq 5$, $C \leq 5$
- U test primerima vrednim 36 poena: $N \leq 1000$, $C \leq 1000$
- U test primerima vrednim 34 poena:  Bez dodatnih ograničenja

## Napomena

U ovom zadatku, podrazumevati da je $0^0 = 0$. Ostali stepeni se ponašaju uobičajeno.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Vladimir Milenković | Vladimir Milenković | Aleksa Milisavljević | Ivan Stošić |


## Analiza
Zadatak rešavamo razmatranjem vrednosti $K$:

+  Ako je $K=0$, vrednost svakog stepena će biti 1, osim vrednosti $0^0$. U tom slučaju treba da prebrojimo koliko ima 0 u nizu i svaku koju možemo povećamo za 1.
+  Ukoliko je $K=1$, lepota niza je suma njegovih elemenata. Tada je svejedno koji ćemo element povećati, pa samo primenimo svih $C$ operacija na bilo koji element.
+  Ukoliko je $K=2$ i ukoliko budemo primenjivali ijednu operaciju, primenićemo svih $C$ operacija na najveći. To važi, jer pretpostavimo da smo ukupno primenili $D$ operacija i to $D_i$ na element $A_i$ i neka najveći ima vrednost $a$ tada je konačna suma: 

$$
\sum_{i=1}^n (A_i + D_i)^2 = \sum_{i = 1}^{n} (A_i^2 + 2 \cdot A_i \cdot D_i + D_i^2) = 
$$

$$
\sum_{i = 1}^{n} (A_i^2 + 2 \cdot A_i \cdot D_i) +\sum_{i = 1}^{n} D_i^2 \leq \sum_{i = 1}^{n} (A_i^2 + 2 \cdot a \cdot D_i) + \sum_{i = 1}^{n} D_i^2 =
$$

$$
\sum_{i = 1}^{n} A_i^2 + 2 \cdot a \cdot D + \sum_{i = 1}^{n} D_i^2 \leq \sum_{i = 1}^{n} A_i^2 + 2 \cdot a \cdot D + D^2,
$$

što je tačno jednako lepoti niz, kada bi na najveći dodali $D$. Dakle ukoliko primenjujemo neke operacije, svakako ih primenjujemo na najveći. Međutim, primetimo da se tada lepota promenila za $2 \cdot a \cdot D + D^2$ što maksimum dostiže ili za $D=0$ ili za $D=C$, pa ako budemo primenjivali neku operaciju, primenićemo svih $C$ na najveći.


## Smernice za algoritam
Primetimo da, ukoliko je $K=2$, dovoljno je da proverimo da li povećavanjem najvećeg elementa za $C$, povećavamo njegovu apsolutnu vrednost, ukoliko je povećavamo, primenićemo svih $C$ operacija na njega, u suprotnom, nećemo primeniti ni jednu operaciju. Primetimo da, ukoliko apsolutna vrednost ostaje ista, nećemo primeniti ni jednu operaciju, jer težimo da minimizujemo broj operacija.

``` cpp title="02_lep_niz.cpp" linenums="1"
/*
Vladimir VladaMG98 Milenkovic
Problem: Dodavanje u kutije
Kvalifikacije 2018/19, prvi krug, drugi zadatak
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
long long pw(int a, int b){
	long long ret = 1;
	while(b--) ret *= a;
	return ret;
}
int arr[MAXN];
int n, c, k;
long long soln(){
	long long sol = 0;
	for(int i = 1; i <= n; i++){
		sol += pw(arr[i], k);
	}
	return sol;
}
int main(){
	scanf("%d %d %d", &n, &c, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
	}
	if(k == 0){
		//I should change as many zeros I can to ones
		int operations_made = 0;
		int n_zeros = 0;
		for(int i = 1; i <= n; i++){
			if(arr[i] == 0) n_zeros++;
		}
		operations_made = min(n_zeros, c);
		int zeros_left = n_zeros - operations_made;
		int answer = n - zeros_left;
		printf("%d %d\n", answer, operations_made);
	} else if(k == 1){
		long long ans = soln();
		printf("%lld %d\n", ans + c, c);
	} else if(k == 2){
		int mx = arr[1]; int ind_mx = 1;
		for(int i = 2; i <= n; i++){
			if(arr[i] > mx){
				mx = arr[i];
				ind_mx = i;
			}
		}
		int operations;
		if(abs(mx + c) > abs(mx)){
			arr[ind_mx] += c;
			operations = c;
		} else operations = 0;
		printf("%lld %d\n", soln(), operations);
	}
	return 0;
}
```
