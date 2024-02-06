---
hide:
  - toc
---

# A2 - Večiti

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Ivica, večiti student matematičkog fakulteta, najviše od svega voli da gleda fudbalske utakmice, pije pivo i izlazi na ispite iz Topologije. Interesantno je da je on za taj ispit učio samo jednom u životu ali i da profesor na svakom ispitu daje iste zadatke što za posledicu ima da **svaki put kada Ivica izađe na ispit iz ovog predmeta, on osvoji $A$ poena.**

Jednog dana, izvesna vračara je Ivici gledala u dlan i rekla mu je da se (jasno kao dan) vidi da će on završiti fakultet **onog trenutka kada ukupna suma njegovih poena na ispitima iz Topologije bude počinjala istim nizom cifara kao mistični broj $B$**. Sada Ivica ne može da spava od nestrpljenja i zanima ga kolika će biti ukupna suma njegovih poena u trenutku kada završi fakultet. Pomozite mu!

## Ulaz
U prvom redu standardnog ulaza nalazi se prirodan broj $A$, broj poena koje Ivica osvaja na svakom ispitu iz Topologije. U drugom redu standardnog ulaza nalazi se prirodan broj $B$ – mistični broj.

## Izlaz
U prvom i jedinom redu standarnog izlaza ispisati jedan prirodan broj – broj poena koje će Ivica imati u zbiru na ispitima iz Topologije u trenutku kada završi fakultet. Ukoliko se to nikada neće desiti, ispisati $-1$ (bez navodnika).

## Primer 1
### Ulaz
```
15
43
```

### Izlaz
```
435
```

## Objašnjenje primera
Ivica osvaja $15$ poena po ispitu i završiće fakultet kada ukupna suma počinje nizom cifara `43`. To će se prvi put desiti posle $29$ ispita (ne može ranije) i tada će  imati $29\cdot 15 = 435$ poena.

## Ograničenja

* $1 \leq A \leq 10^9$.
* $B$ je prirodan broj i imaće najviše $10^5$ cifara.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim $15$ poena važi $1\leq B\leq 9$.
* U test primerima vrednim $20$ poena važi $1\leq A, B \leq 10^3$.
* U test primerima vrednim $35$ poena važi $1\leq A,B\leq 10^9$.
* U test primerima vrednim $30$ poena nema dodatnih ograničenja.





#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Vladimir Branković | Boris Grubić |

## Prvi podzadatak
Neka brojevi $A$ i $B$ imaju, redom, $n$ i $m$ cifara. Brojevi $B\cdot10^{n}$, $B\cdot10^{n}+1$,  . . .   $B\cdot10^{n}+A-1$ daju različite ostatke po modulu A, što znači da je jedan od njih deljiv sa A i ima $n+m$ cifara. Sada kada znamo da rešenje uvek postoji, prolaskom kroz niz $B$, $B+1$, . . .$B\cdot10^{n}+A-1$ (brojevi su manji od $10^{n}$ ) nađemo najmanji broj deljiv sa A. Ovih brojeva ima     $1$ + $10^{2}$ + . . . + $10^{n}$ = $\cfrac{10^{n+1}-1}{9}$, pa je složenost algoritma $O\Big(\cfrac{10^{n+1}-1}{9}\Big)$ , gde je $n$ broj cifara broja A.

## Drugi podzadatak
Koristimo sličnu ideju, proveravamo brojeve $B$, $B+1$, . . .$B\cdot10^{n}+A-1$ (brojevi su manji od $10^{n+m}$ ). Složenost algoritma je $O\Big(\cfrac{10^{n+1}-1}{9}\Big)$.

## Treći podzadatak
Ovog puta, umesto da posmatramo sve brojeve, za svako $i$ od $1$ do $n$ tražimo najmanji
$i$-tocifreni broj $C$ (može imati vodeće nule) takav da je broj $B\cdot10^{i}+C$ deljiv sa A. To možemo u $O(1)$, jer je $C$ kongruentno sa $-B\cdot10^{i}$ po modulu A. Složenost je $O(n)$.

## чetvrti podzadatak
Slična ideja kao u prošlom podzadatku, ali je sada $B$ preveliko da bi direktno računali ostatak po modulu A, tako da pravimo pomoćni niz $p$, gde je $p_i$ ostatak broja $10^{i}$ po modulu A i ostatak broja $B$ je
$B[0]\cdot p[m-1]+B[1]\cdot p[m-2]+. . .+B[m-1]\cdot p[0]$. Kako nam je potrebno samo prvih $m$ članova niza $p$ ,složenost ovog algoritma je $O(n+m)$.

``` cpp title="05_veciti.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>
#include <cstring>

const int MaxN = 100100;

int n, a, digCount;
int digits[20];
long long curr, deg;
char b[MaxN];

int main()
{
	scanf("%d", &a);
	scanf("%s", b);
	n = strlen(b);
	
	curr = 0LL;
	for (int i = 0; i < n; i++)
		curr = (curr * 10 + (b[i] - '0')) % a;

	deg = 1;
	digCount = 0;
	while ((a - curr) % a >= deg)
	{
		deg = deg * 10;
		digCount++;
		curr = (curr * 10) % a;
	}

	curr = (a - curr) % a;
	for (int i = 1; i <= digCount; i++)
	{
		digits[i] = curr % 10;
		curr = curr / 10;
	}

	for (int i = 0; i < n; i++)
		printf("%c", b[i]);
	for (int i = digCount; i > 0; i--)
		printf("%d", digits[i]);
	printf("\n");
	return 0;
}
```
