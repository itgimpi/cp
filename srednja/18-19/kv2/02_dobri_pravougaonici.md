---
hide:
  - toc
---

# 2 - Dobri pravougaonici

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 256MB |

Ozloglašeni gospodar svih glodara, Ćrle, namerava da pokori ceo svet. Međutim, dobar deo Perine farme će da posluži za sada.

Perinu farmu možemo predstaviti kao matricu $M$ dimenzije $N \times N$ gde polje $M_{ij}$ sadrži jedan broj -- sortu jabuke koju Pera uzgaja na tom polju. Poznato je da Pera obeležava sorte nekim brojevima izmeđi $1$ i $K$.

Čudni su putevi pacovski, te Ćrletova regularna vojska može da pokori jedino _pogodne_ teritorije. Kažemo da je teritorija pogodna ako je pravougaonog oblika, sadrži samo jednu sortu jabuke i ta sorta se nalazi samo u okviru te teritorije.

Unajmljivanje elitnih štakora košta previše, te Ćrleta zanima koliko pogodnih teritorija ima Perina farma (ni on sam ne zna zašto). Pošto je Ćrle previše zauzet jedenjem sira, zamolio vas je da to odredite umesto njega.

## Opis ulaza

U prvom redu standardnog ulaza nalaze se dva prirodna broja $N$ i $K$ - dimenzija Perine farme, i broj sorti jabuka koje Pera poznaje. U $(i+1)$-voj liniji ($1 \leq i \leq N$) standardnog ulaza nalazi se $N$ brojeva odvojenih razmacima koji predstavljaju $i$-tu vrstu Perine farme ($j$-ti broj predstavlja $M_{ij}$). 

## Opis izlaza

U prvom redu standardnog izlaza ispisati jedan broj - broj pogodnih teritorija koje Perina farma sadrži.

## Primer 1

### Ulaz

~~~
5 10
3 2 2 1 4
3 2 2 7 4
8 2 2 1 3
8 8 9 9 9
8 8 1 5 1
~~~

### Izlaz

~~~
5
~~~

## Objašnjenje primera

Pogodne teritorije su one teritorije koje sadrže brojeve 2, 4, 5, 7 i 9.

## Ograničenja

U svim test primerima važi:

* $1 \leq N \leq 2000$.
* $1 \leq K \leq 10^6$.
* $1 \leq M_{ij} \leq K$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 20 poena: $N \leq 20$.
* U test primerima vrednim 20 poena: $N \leq 100$, $K \leq .100$
* U test primerima vrednim 20 poena: $N \leq 100$.
* U test primerima vrednim 20 poena: $K = 2$.
* U test primerima vrednim 20 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Momčilo Topalović | Vladimir Milenković | Vladimir Milenković |

## Analiza
Primetimo da je $K <= 1000000$, pa ukoliko mi možemo da u $O(1)$ proverimo da li su svi brojevi jednaki nekom broju u istom pravougaoniku, mi možemo rešiti zadatak u $O(K)$, što je složenost koja je dovoljno dobra. Ukoliko posmatramo sve vrednosti koje su jednake nekom broju $A$, jedini kandidat za dobar pravougaonik koji sadrži samo brojeve $A$ je najmanji pravougaonik koji sadrži sve njih (ukoliko bi bio neki veći, sigurno bi postojao broj koji nije jednak tom broju, ukoliko bi bio neki manji, postojao bi broj jednak tom broju koji nije u njemu). Sada, provera da li je taj pravouganik dobar je ekvivalentna proveri da li je površina tog pravougaonika jednaka broju pojavljivanja broja $A$ u matrici (zato što svako pojavljivanje tog broja mora biti u tom pravougaoniku).

## Smernice za algoritam
Prvo, želimo da unapred izračunamo, za svaki broj, koji je njegov odgovorajući pravougaonik. On će se prostirati od najmanjeg reda u kom postoji taj broj do najvećeg, i od najmanje kolone u kojoj postoji taj broj, do najveće. Takođe, možemo izračunati i broj pojavljivanja svakog broja. Onda, jednom petljom, idemo po svih brojevima od $1$ do $K$ i proveravamo da li je kandidat pravouganik dobar, u $O(1)$.

Što se tiče složenosti, treba nam $O(N^2)$ za preprocesiranje, i $O(K)$ za sve provere, tako da je ukupna složenost $O(N^2 + K)$.

``` cpp title="02_dobri_pravougaonici.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 1000010;
int min_x[MAXK], min_y[MAXK], max_x[MAXK], max_y[MAXK];
int cnt[MAXK];
int main(){
	int n, m, k;
	cin >> n >> k;
	assert(n <= 5000);
	assert(k <= 1000000);
	m = n;
	for(int i = 1; i <= k; i++){
		min_x[i] = INT_MAX;
		min_y[i] = INT_MAX;
		max_x[i] = INT_MIN;
		max_y[i] = INT_MIN;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int value;
			cin >> value;
			assert(1 <= value);
			assert(value <= k);
			cnt[value] += 1;
			min_x[value] = min(min_x[value], i);
			max_x[value] = max(max_x[value], i);
			min_y[value] = min(min_y[value], j);
			max_y[value] = max(max_y[value], j);
		}
	}
	int ans = 0;
	for(int i = 1; i <= k; i++){
		if(cnt[i] == 0) continue;
		if((max_x[i] - min_x[i] + 1) * (max_y[i] - min_y[i] + 1) == cnt[i]){
			ans += 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```
