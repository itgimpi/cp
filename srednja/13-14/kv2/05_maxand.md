---
hide:
  - toc
---

# 5 - MaxAND

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Mićko i dalje nije imao priliku da igra “Flappy Bird” pa još uvek vredno radi i vežba zadatke. Trenutno se malo zaglavio kod sledećeg problema:

Dat je niz $A$ dužine $N$ koji se sastoji od pozitivnih celih brojeva $A_i$ ($A_i$ je $i$-ti član niza). Od datih brojeva odabrati tačno $K$ tako da je *bitwise AND* izabranih brojeva što veći. Drugim rečima treba odabrati brojeve $A_{i_1}, A_{i_2}, \ldots, A_{i_k}$ tako da je $A_{i_1} \text{ AND } A_{i_2} \text{ AND } \ldots \text{ AND } A_{i_k}$ najveće moguće i $i_x \neq i_y$ za $1\leq x < y \leq k$.

Pomozite mu da što pre reši ovaj zadatak jer mu je Momčilo na četu upravo poslao link ka igri.

## Ulaz
U prvom redu standardnog ulaza nalaze se dva cela broja, $N$ i $K$. U drugom redu nalaze se $N$ brojeva $A_i$ razdvojeni razmakom.

## Izlaz
U jednoj liniji u bilo kom redosledu ispisati $K$ traženih brojeva razdvojenih razmakom. Ukoliko postoji više rešenja, štampati bilo koje od njih.

## Primer 1
### Ulaz
```
5 3
14 10 1 6 6
```

### Izlaz
```
6 14 6
```

## Objašnjenje primera
$6 \text{ AND } 14 \text{ AND } 6=6$. Veći *bitwise AND* neka $3$ broja od datih $5$ nije moguće dobiti.

## Ograničenja

* $1\leq K \leq N \leq 10^6$.
* $1\leq A_i \leq 10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $30$ poena važi $1\leq K\leq N\leq 20$.
* U test primerima vrednim $20$ poena važi $1\leq K \leq N\leq 5.000$.
* U test primerima vrednim $50$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dimitrije Dimić | Marko Ilić | Boris Grubić |

## Rešenje za $n \le 20$
U ovom podzadatku možemo proći kroz svih $2^n$ izbora elemenata i za one izbore koji sadrže tačno $k$ elemenata izračunati njihovu *bitwise AND* vrednost. Na kraju treba ispisati onaj izbor koji daje maksimalnu vrednost *bitwise AND*.

## Rešenje za $1 \le k \le n \le 5000$

## Glavno rešenje
Ako posmatramo određeni bit i ako su nam fiksirani viši bitovi, onda nam je uvek bolje da na tom bitu bude jedan, jer i u slučaju kada su svi bitovi manje vrednosti od njega jedan, a on nula, suma vrednosti tih bitova je manja od vrednosti posmatranog bita. Zato treba posmatrati bitove od viših ka nižim. Ideja je da u svakom momentu imamo niz koji će nam sadržati kandidate za rešenje. U početku su to svi elementi. Kada posmatramo odrećeni bit, ako imamo manje od $k$ brojeva koji imaju jedan na tom bitu, onda svakako ne možemo imati jedan u rešenju na tom bitu, pa elementi koji imaju jedan na tom bitu u ovom slučaju nemaju nikakvu prednost u odnosu na one koji imaju nulu, pa će samim tim svi elementi u nizu kandidata "preživeti". U slučaju da imamo $k$ ili više elemenata sa jedinicom na posmatranom bitu, onda će samo oni ostati kao kandidati. Na kraju treba ispisati bilo kojih $k$ elemenata iz niza kandidata.


``` cpp title="05_maxand.cpp" linenums="1"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX_N = 1000005;

int n, k;
int a[MAX_N];
bool mark[MAX_N];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	for (int i = 0; i < n; ++i) mark[i] = true;
	for (int i = 29; i >= 0; --i) {
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			if (mark[j] && ((a[j] >> i) & 1) == 1)
				++cnt;
		}

		if (cnt >= k) {
			for (int j = 0; j < n; ++j)
				if (mark[j] && ((a[j] >> i) & 1) == 0)
					mark[j] = false;
		}
	}

	for (int i = 0; i < n && k > 0; ++i)
		if (mark[i]) {
            printf("%d ", a[i]);
			--k;
		}
    printf("\n");
	return 0;
}

```
