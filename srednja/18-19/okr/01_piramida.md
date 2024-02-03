---
hide:
  - toc
---

# B1 - Piramida

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

U enigmatici, piramida je tip mozgalice koji treba da se popuni sa $P$ reči u $P$ redova. Da bi se pravilno popunila, počinje se od prve reči koja se sastoji od samo jednog slova. Svaka naredna reč ima jedno slovo više od prethodne i može da se dobije dodavanjem jednog slova, a zatim proizvoljnim menjanjem redosleda dobijenih slova.

Vama je dat niz od $N$ stringova koji se sastoje od velikih slova engleske abecede. Ovi stringovi ne moraju nužno biti reči nekog jezika, već mogu biti proizvoljni nizovi slova. Pritom, $k$-ti string ima dužinu tačno $k$. Vaš zadatak je da odredite najveći prirodan broj $P$ takav da prvih $P$ stringova čini piramidu.

## Opis ulaza

Prva linija standardnog ulaza sadrži jedan prirodan broj $N$ - broj stringova. Narednih $N$ linija sadrži po jedan string ($k$-ti string će biti dužine tačno $k$), odnosno niz velikih slova engleske abecede.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati najveći prirodan broj $P$ takav da prvih $P$ stringova čini piramidu.

## Primer 1

### Ulaz

~~~
7
A
AR
RAK
TRKA
KARTA
ARTIKL
AKROLIT
~~~

### Izlaz

~~~
5
~~~

## Primer 2

### Ulaz

~~~
3
A
BC
DEF
~~~

### Izlaz

~~~
1
~~~

### Objašnjenje primera

U prvom primeru, najveća piramida koja može da se dobije se sastoji od prvih $5$ stringova. Naime, reč _ARTIKL_ ne može da se dobije dodavanjem jednog slova reči _KARTA_ i menjanjem redosleda slova u rezultatu.

U drugom primeru najduža piramida se sastoji samo od prve reči.

## Ograničenja

U svim test primerima važi: $N \leq 2500$. Test primeri su podeljeni u 4 disjunktne grupe:

* U test primerima vrednim 20 poena: $N \leq 10$.
* U test primerima vrednim 20 poena: $N \leq 100$.
* U test primerima vrednim 20 poena: Svi stringovi sadrže samo slova _A_ i _B_.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

## Napomena

Engleska abeceda se sastoji od sledećih slova: `ABCDEFGHIJKLMNOPQRSTUVWXYZ`. _ASCII_ vrednosti ovih karaktera su od $65$ za veliko slovo _A_ do $90$ za veliko slovo _Z_.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Ivan Stošić | Dragan Urošević | Aleksa Plavšić |

## Analiza

Lako se zaključuje da se problem svodi na utvrđivanje da li par uzastopnih stringova mogu biti uzastopni redovi piramide. Provera da li dva stringa mogu biti uzastopni redovi se svodi na utvrđivanje broja pojavljivanja pojedinih slova engleskog alfabeta (nad kojim su stringovi napisani). 
Ako sa $n_x[A], n_x[B], n_x[C], ..., n_x[Z]$ označimo broj pojavljivanja, redom, slova $A, B, C, ..., Z$ u stringu $x$, a sa $n_y[A], n_y[B], n_y[C], ..., n_y[Z]$ označimo broj pojavljivanja, redom, slova $A, B, C, ..., Z$ u stringu $y$, onda stringovi $x$ i $y$ mogu biti uzastopni redovi piramide ako i samo ako važi

$$
|n_y[A]-n_x[A]| + |n_y[B]-n_x[B]| + |n_y[C]-n_x[C]+...+|n_y[Z]-n_x[Z]| = 1.
$$
 
##  Smernice za algoritam

Implementacija se svodi na proveru da li parovi uzastopnih stringova mogu biti redovi piramide. A ta provera se svodi na određivanje broja pojavljivanja pojedinih slova u ta dva stringa. Prebrajanje se može izvesti jednim prolazom kroz odgovarajući string. Postupak se prekida u trenutku kada se stigne do para uzastopnih stringova koji ne mogu biti uzastopni redovi piramide ili kada se stigne do poslednjeg para stringova.

``` cpp title="01_piramida.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

bool moze(string s, string t) {
	vector<int> f(26, 0);
	for (char x : s)
		f[x - 'A']++;
	for (char x : t)
		f[x - 'A']--;
	return count(f.begin(), f.end(), 0) == 25;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cerr.tie(nullptr);

	int n, sol = 1;
	string s;

	cin >> n >> s;
	for (int i=2; i<=n; i++) {
		string t;
		cin >> t;
		if (moze(s, t)) {
			sol = i;
			s = t;
		} else {
			break;
		}
	}

	cout << sol << '\n';
}
```
