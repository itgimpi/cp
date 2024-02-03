---
hide:
  - toc
---

# A3 - Formula

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mračnoj Komisiji ponovo ponestaje vremena! Potrebno je objaviti konačne rezultate Galaktičkih kvalifikacija za takmičenje iz hiperprogramiranja. Ovo takmičenje se sastoji od $N$ rundi, a za konačan skor svakog takmičara se uzima $K$-ta vrednost u sortiranom nizu skorova koje je ostvario na svim rundama. Na primer, ako je $K=1$, konačan rezultat je najmanja od svih vrednosti.

Međutim, Mračna Komisija i dalje koristi prastaru Inteligentnu aplikaciju za bodovanje, kod koje se za računanje konačnog rezultata mogu koristiti mala slova engleske abecede i dvoargumentne funkcije $\min$ i $\max$ (minimum i maksimum dva broja), koje se pišu $(x,y)$ i $[x,y]$, redom. Vaš zadatak je da pronađete formulu koja tačno nalazi konačan skor za proizvoljne (ne nužno sortirane) skorove u pojedinačnim rundama.  Argumenti ovih funkcija $x,y$ se odvajaju zarezom i mogu biti bilo koje formule. Moguće je proizvoljno ugnježdavati formule. Rezultat $i$-te runde je označen $i$-tim malim slovom engleskog alfabeta.

## Opis ulaza
U prvom i jedinom redu standardnog ulaza nalaze se prirodni brojevi $N$ i $K$, redom, odvojeni razmakom.

## Opis izlaza
U jedini red standardnog izlaza ispisati traženu formulu. Ukoliko ima više rešenja, štampati bilo koje. **Ispisana formula ne sme imati više od 30000 karaktera i ne sme sadržati razmake niti bilo koje karaktere osim prvih $N$ malih slova engleske abecede, običnih i uglastih zagrada i zareza.**

## Primer 1
### Ulaz
```
2 2
```

### Izlaz
```
[a,b]
```

## Primer 2
### Ulaz
```
3 2
```

### Izlaz
```
[[(a,b),(b,c)],(c,a)]
```

## Objašnjenje primera
U prvom primeru traži se drugi, odnosno najveći skor. Jasno je da je ova vrednost upravo jednaka maksimumu skorova prve i druge runde. U drugom primeru kako god da zamenimo vrednosti simbola $a,b,c$ brojevima dobiće se srednji broj po vrednosti.

## Ograničenja

* $1 \leq N \leq 12$.
* $1 \leq K \leq N$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede 20 poena važi $K=1$ ili $K=N$.
* U test primerima koji vrede 25 poena važi $K = 2$.
* U test primerima koji vrede 55 poena nema dodatnih ograničenja.

## Napomena

Prvih dvanaest slova engleske abecede su: `abcdefghijkl`.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Ivan Stošić | Ivan Stošić | Nikola Spasić |

Posmatrajmo sve $K$-elementne podskupove skupa simbola $x_1, \ldots, x_n$, gde je $x_i$ $i$-to slovo engleske abecede. U svakoj zameni simbola konkretnim vrednostima, svaki od ovih podskupova će imati maksimalni element. Primetimo da vrednost tog maksimalnog elementa ne može biti manja od $K$-te vrednosti po veličini od svih $N$ vrednosti. Štaviše, tačno jedan od tih podskupova će sadržati $K$-ti element po veličini od svih kao svoj maksimum, i to onaj podskup koji sadrži najmanjih $K$ elemenata. Dakle, ovaj maksimum će biti ujedno i minimalni maksimum po svim $K$-elementnim podskupovima.

Rešenje je, dakle, naći maksimum za sve $K$-elementne podskupove a zatim minimum svih tih vrednosti. Izračunajmo dužinu formule u zavisnosti od $K, N$. Postoji $\binom{N}{K}$ $K$-elementnih podskupova. Zapis maksimuma za svakog od njih će se sastojati od $4K-3$ karaktera. Zatim, neophodno je izračunati minimum svih ovih vrednosti za šta je potrebno još $3(\binom{N}{K}-1)$ karaktera. Dakle, ukupan broj karaktera je $(4K-3)\binom{N}{K} + 3(\binom{N}{K}-1)$. Ovaj izraz se može uprostiti i iznosi $4K\binom{N}{K} - 3$. "Najgori" slučaj je $N=12, K=6$ ili $N=12, K=7$ i tada je broj karaktera $22173$, što je svakako manje od $30000$.

## Smernice za algoritam

Svi $K$-elementni podskupovi nekog skupa mogu se generisati rekurzivnom funkcijom ili u jeziku C++ funkcijom `next_permutation` primenjenom na niz koji se sastoji od $N-K$ nula i $K$ jedinica, tim redom.



``` cpp title="06_formula.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cerr.tie(nullptr);

	cin >> n >> k;

	vector<string> terms;
	int a[20] = {0};

	for (int i=n-k; i<n; i++) {
		a[i] = 1;
	}

	do {
		string s(k-1, '[');

		int j = 0;

		for (int i=0; i<n; i++) {
			if (a[i]) {
				if (!j) {
					j = 1;
					s += 'a' + i;
				} else {
					s += ',';
					s += 'a' + i;
					s += ']';
				}
			}
		}
		terms.push_back(s);
	} while (next_permutation(a, a+n));

	string p(terms.size() - 1, '(');

	int j = 0;

	for (string q : terms) {
		if (!j) {
			j = 1;
			p += q;
		} else {
			p += ',';
			p += q;
			p += ')';
		}
	}

	cout << p << '\n';
}
```
