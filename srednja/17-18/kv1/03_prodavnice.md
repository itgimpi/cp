---
hide:
  - toc
---

# 3 - Prodavnice

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Jedan grad ima $n$ stanovnika i samo jednu ulicu koju možemo prestaviti $x$-osom. Za svakog stanovnika je poznata koordinata njegove kuće na $x$-osi, (moguće je da nekoliko kuća ima istu koordinatu). U ovaj grad dolazi poznati sajber-prevarant Džimi Rudar koji planira da otvori tačno dve prodavnice opreme za rudarenje bitkoina - u jednoj će prodavati pijuke a u drugoj ašove. Džimi Rudar zna da će, nakon otvaranja prodavnica, svaki stanovnik pojuriti u njemu najbližu prodavnicu da kupi opremu a ukoliko su obe prodavnice podjednako udaljene, stanovnik će slučajno odabrati jednu od njih (njima nije bitno da li im treba pijuk ili ašov, bitno da se rudare bitkoini). 

Džimi želi da optimalno izgradi prodavnice i već je napravio $m$ potencijalnih planova: svaki plan je par brojeva $(A_i, B_i)$ i označava da Džimi želi da sagradi prodavnicu pijuka na koordinati $A_i$ i prodavnicu ašova na koordinati $B_i$ na $x$-osi. Džimi ima molbu za vas: za svaki od $m$ potencijalnih planova, izračunajte ukupnu razdaljinu koju bi prešli svi stanovnici ukoliko bi prodavnice bile izgrađene na koordinatama zadatim u tom planu. Ukoliko ovo odradite, dobijate $5$kg bitkoina od Džimija! Podsetimo se da je rastojanje između tačaka $X$ i $Y$ na $x$-osi jednako $|X - Y|$.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva prirodna broja $n$ i $m$, broj kuća i broj upita, redom. U narednom redu nalazi se $n$ prirodnih brojeva $X_i$ koji predstavljaju koordinate kuća. U narednih $m$ redova nalaze se po dva prirodna broja $A_i$ i $B_i$ koji predstavljaju plan za izgradnju prodavnica na tim koordinatama.

## Opis izlaza
Ispisati $m$ prirodnih brojeva, u svakom redu po jedan, koji predstavljaju odgovore na datih $m$ upita u odgovarajućem redosledu.

## Primer 1
### Ulaz
```
5 2
12 50 70 1 10
10 100
60 8
```

### Izlaz
```
81
33
```

## Primer 2
### Ulaz
```
3 1
1000000000 1000000000 1000000000
1 2
```

### Izlaz
```
2999999994
```

## Objašnjenje primera
U prvom test primeru, prvi plan predviđa izgradnju prodavnice pijuka i ašova na koordinatama $10$ i $100$, redom. U tom slučaju, prvi stanovnik (sa koordinatom $12$) ide u prodavnicu pijuka i prelazi rastojanje $|10 - 12| = 2$; drugi stanovnik (koordinata $50$) takođe ide u prodavnicu pijuka i prelazi rastojanje $|50 - 10| = 40$; treći stanovnik ide u prodavnicu ašova i prelazi rastojanje $|70 - 100| = 30$; četvrti stanovnik prelazi rastojanje $9$ dok peti prelazi rastojanje $0$. Ukupno pređeno rastojanje je $2 + 40 + 30 + 9 + 0 = 81$. U slučaju drugog plana (prodavnice na koordinatama $60$ i $8$) ukupno pređeno rastojanje je $4 + 10 + 10 + 7 + 2 = 33$.

## Ograničenja

* $1 \leq n \leq 10^5$.
* $1 \leq m \leq 10^5$.
* $1 \leq X_i \leq 10^9$.
* $1 \leq A_i, B_i \leq 10^9$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima koji vrede $20$ poena važiće $1 \leq N, M \leq 1000$.
* U test primerima koji vrede $15$ poena važiće $A_i = B_i$ za svako $i$.
* U test primerima koji vrede $15$ poena važiće $A_i \leq min X$ i $max X \leq B_i$ za svako $i$.
* U test primerima koji vrede $20$ poena važiće $1 \leq A_i, B_i, X_i \leq 10^6$.
* U test primerima koji vrede $30$ poena nema dodatnih ograničenja.





#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Aleksa Plavšić i Ivan Stošić |

Jasno je da je za svaki upit $(A, B)$ potrebno izračunati vrednost izraza $\sum_{i=1}^n \min(|x_i - A|, |x_i - B|)$ tj. sumu rastojanja do najbliže prodavnice. Direktno računanje ove sume za svaki upit daje rešenje složenosti $O(nm)$ što je dovoljno samo za $20$ poena.

Posmatrajmo slučaj kada uvek važi $A_i = B_i$ tj. kada je potrebno izračunati $\sum_{i=1}^n |x_i - A|$. Za početak, prirodan korak je sortiranje niza $x$ -- nadalje pretpostavljamo da je $x_1 \leq x_2 \leq \ldots \leq x_n$. Za datu vrednost $A$ možemo binarnom pretragom u složenosti $O(\log n)$ odrediti najveću vrednost $ind$ za koju važi $x_{ind} < A$ (ili ustanoviti da takva vrednost ne postoji ako je $A \leq x_1$). Sada važi

$$
\sum_{i=1}^n |x_i - A| = \sum_{i = 1}^{ind} (A - x_i) + \sum_{i=ind+1}^n (x_i - A) = ind \cdot A - s_{ind} + (s_n - s_{ind}) - (n - ind)\cdot A
$$

gde je $s$ niz *prefiksnih suma* niza $x$, tj. $s_i = x_1 + x_2 + \ldots + x_i$. Prema tome, ukoliko na početku (pre svih upita) sortiramo niz $x$ i izračunamo niz prefiksnih suma, možemo za svaki upit odraditi binarnu pretragu i vratiti rezultat iz prethodne jednačine (bez sumiranja). Složenost ovog pristupa je $O(n \log n + m \log n)$.

Prethodni algoritam se jednostavno modifikuje i u slučaju kada je $A_i \neq B_i$. U tom slučaju, za upit $(A, B)$ (npr. neka je $A < B$) binarnom pretragom pronađemo najveću vrednost $mid$ za koju važi $x_{mid} < \frac{A+B}{2}$; to znači da će svi stanovnici sa koordinatama $x_1, x_2, \ldots, x_{mid}$ ići u prodavnicu $A$ a stanovnici sa koordinatama $x_{mid+1}, x_{mid+2}, \ldots, x_n$ u prodavnicu $B$. Zatim dva puta primenimo prethodni algoritam, jednom za podniz $x[1, mid]$ i vrednost $A$, a drugi put za podniz $x[mid+1, n]$ i vrednost $B$.

Za dodatne podzadatke je takođe predviđen ovaj algoritam ali je za njih dovoljna potencijalno lakša imeplementacija i manja analiza specijalnih slučajeva o kojima treba voditi računa prilikom implementacije rešenja za $100$ poena -- npr. kada su vrednosti $A$ ili $B$ ili $\frac{A+B}{2}$ levo ili desno od niza $x$ (npr. kada svi idu u samo jednu prodavnicu). Ovo se u potpunosti može zaobići pametno dizajniranom funkcijom za pomenutu binarnu pretragu.

``` cpp title="03_prodavnice.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 100000;
const int MAX_M = 100000;

int n, m;
int a[MAX_N + 10];
long long pref[MAX_N + 10];

// max ind tako da a[ind] < val
int lastLessThan(int l, int r, int a[], double val)
{
	if (l > r || !(val > a[l]))
		return l - 1;
	while (l < r)
	{
		int m = (l + r + 1) / 2;
		if (a[m] < val)
			l = m;
		else
			r = m - 1;
	}
	return l;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a + 1, a + n + 1);
	pref[0] = 0LL;
	for (int i = 1; i <= n; i++)
		pref[i] = pref[i - 1] + a[i];

	for (int i = 1; i <= m; i++)
	{
		int A, B;
		scanf("%d%d", &A, &B);
		if (A > B)
			swap(A, B);
		int Y = lastLessThan(1, n, a, (A + B) / 2.0);
		// [1, Y] u A, [Y + 1, n] u B
		
		int X = lastLessThan(1, Y, a, A);
		int Z = lastLessThan(Y + 1, n, a, B);
		// a[1] <= a[2] <= ... <= a[X] < A <= a[X+1] <= ... <= a[Y] < (A + B)/2 < a[Y+1] <= ... <= a[Z] < B <= a[Z+1] <= ... <= a[n]
		long long sol 
			= ((long long)A * X - pref[X]) 
			+ (pref[Y] - pref[X] - (long long)A * (Y - X))
			+ ((long long)B * (Z - Y) - (pref[Z] - pref[Y])) 
			+ (pref[n] - pref[Z] - (long long)B * (n - Z));
		printf("%lld\n", sol);
	}

	return 0;
}
```
