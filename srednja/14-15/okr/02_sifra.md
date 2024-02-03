---
hide:
  - toc
---

# B2 - Šifra

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Poznati programer koji stalno putuje po svim takmičenjima, koga su zgodno nazvali Turista, je jedini za sada uradio zadatak iz informatike za koji se dobija milion dinara. On je poznat po tome što je skroman, te neće da objavi svoje rešenje u narednih godinu dana kako bi drugi imali šansu da dobiju milion dinara. On je zaključao svoje rešenje na internetu nizom brojeva, i veruje da niko ne može da provali tu šifru.

Mladi programer Kopi je umesto da pokuša da reši problem, rešio da pokuša lakšim putem da dođe do milion dinara. On će pokušati da provali šifru kojom je zaključano rešenje i tako uzme zasluge za to rešenje i nezasluženo osvoji milion dinara. Pošto je u prošlosti već krao rešenja od Turista, može da pretpostavi kako je Turist došao do svoje šifre.

Naime, on zna da su Turistu dva omiljena broja baš $M$ i $K$. Kako je pročitao tekst problema uvideo je da se u njemu pojavljuje tačno $N$ celih nenegativnih različitih brojeva. Veoma dobro poznaje kako Turista razmišlja, te je shvatio kako je Turist došao do svoje šifre.

Turista je napravio sve moguće $M$-torke sačinjene od $N$ brojeva koji se nalaze u tekstu problema (brojevi mogu da se ponavljaju u jednoj $M$-torki) i tako je dobio niz mogućih šifri ($M$-torki). Kako je već spomenuto, Turista voli broj $K$, te Kopi pretpostavlja da je Turist sortirao sve moguće šifre ($M$-torke) u rastućem poretku i  odabrao $K$-tu po redu da bude šifra zaključanog rešenja.

Znamo da je svaka moguća šifra sačinjena od $M$ brojeva te znamo i kako da ih upoređujemo. Za moguću šifru $a=(a_1,a_2,\ldots,a_M)$ kažemo da je manja od moguće šifre $b=(b_1,b_2,\ldots,b_M)$ ako i samo ako postoji prirodan broj $i$, $1\leq i \leq M$, takav da važi $a_j=b_j$ za svako $j<i$ i $a_i<b_i$ (klasično leksikografsko sortiranje).

Kako Kopi ne zna dobro da programira, zamolio vas je da mu pomognete oko pronalaženja šifre.

## Ulaz
U prvom redu standardnog ulaza nalaze se tri prirodna broja $N$, $M$ i $K$, koji redom označavaju koliko ima prirodnih brojeva u tekstu misterioznog problema, i dva omiljena broja Turista. U narednom redu se nalazi N celih nenegativnih različitih brojeva $A_1,A_2,A_3,\ldots,A_N$ koji predstavljaju brojeve koji se nalaze u misterioznom problemu, date u rastućem poretku.

## Izlaz
U prvom i jedinom redu standardnog izlaza potrebno je ispisati $M$ brojeva koji predstavljaju šifru za otključavanje rešenja.

## Ograničenja:
- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- $1 \leq K \leq 10^{18}$
- $0 \leq A_i \leq 10^9$, $A_1 < A_2 < \ldots A_N$
- Postoji $K$-ta $M$-torka.

Test primeri su podeljeni u šest disjunktnih grupa:

- U test primerima vrednim 10 poena važi $M=1$.
- U test primerima vrednim 20 poena važi $M=10$, $A_1=0, A_2=1, A_3=2, \ldots , A_{10}=9$.
- U test primerima vrednim 15 poena važi $N\leq 3, M\leq 9$.
- U test primerima vrednim 15 poena važi $N,M \leq 15$.
- U test primerima vrednim 20 poena važi $N \leq 10\,000$, $M \leq 1\,000$.
- U test primerima vrednim 20 poena nema dodatnih ograničenja.


## Primer:
### Ulaz
```
3 4 37
6 11 533
```

### Izlaz
```
11 11 6 6
```

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Duško Obradović | Demjan Grubić | Nemanja Majski | Marko Savić |

## Rešenje za $M=1$:
U ovom podzadatku nam se traži K-ti najmanji element niza. To možemo da nađemo tako što  samo ispišemo element na K-toj poziciji u nizu, pošto je niz već sortiran. Vremenska složenost je $O(N+M)$.

## Rešenje za $N=10$ i $A_1=0, A_2=1, ...A_{10}=9$: 
[Ima greška u tekstu zadatka, piše $M=10$, ali u primerima je $N=10$]

U ovom podzataku je $K$-ta $M$-torka sam broj $K-1$, samo je važno dodati vodeće nule tako da $K-1$ bude $M$-tocifren broj. Na primer, za $M=5$ i $K=100$, $K-ta$ $M-torka$ je $0 0 0 9 9$. Vremenska složenost je $O(N+M)$.

## Rešenje za $N\le3, M\le9$:
U ovom podzadatku najviše ima $3^9=19683$ $M$-torki. Tako da možemo da idemo redom kroz svaku dok ne dođemo do $K$-te. To možemo uraditi pomoću rekurzije. Vremenska složenost je $O(N^M)$.

## Rešenje za $N\le15, M\le15$:
Zamislimo da je $A_i=i-1$ za svako $1\le i \le N$. Onda je traženo rešenje broj $K-1$ zapisan kao $M$-tocifren broj u brojevnom sistemu sa osnovom $N$. 

Dugim rečima, recimo da je niz $B_1, B_2 ... B_M$ šifra za otključavanje, onda važi:

$$
K-1= B_1 \cdot N^{M-1} + B_2 \cdot N^{M-2} + ... + B_{M-1} \cdot N^{1} + B_M \cdot N^0
$$

Na primer, za $N=3$ i $M=5$:
$$K-1 = B_1\cdot 3^4 + B_2\cdot 3^3 + B_3 \cdot 3^2 + B_4 \cdot 3^1 + B_5 \cdot 3^0$$

Kako važi $0 \le B_i < N$ za svako $1\le i \le M$, jednačina iznad ima jedinstveno rešenje. Ono može da se nađe sledećim postupkom:

Idemo od $B_1$, koji će na početku da bude 0. Nakon toga mi njega povećavamo tako da bude najveća moguća vrednost, ali takva da je desna strana jednačine manja ili jednaka levoj. Kada smo ga povećali do takve vrednosti, prelazimo na $B_2$ i ponavljamo postupak.

Ali, šta da radimo ukoliko $A_i \ne i-1$? Opet ćemo broj K-1 predstaviti u brojevnom sistemu $N$, neka su cifre tako predstavljenog broja $B_1, B_2 ... B_M$. Sada kada želimo da ispišemo rešenje, umesto da ispisujemo redom $B_i$ za svako $1\le i \le M$, ispisaćemo $A_{B_i+1}.$  Vremenska složenost je $O(N\cdot M)$.

## Glavno rešenje:
Isto kao rešenje za prethodni podzatadak, samo moramo paziti na to da nam vrednosti ne pređu maksimalnu granicu. To možemo da uradimo tako što ćemo svuda gde je $N^{M-i} >K$ staviti $B_i=0$. Proveru možemo raditi koristeći funckiju logaritma. Složenost ovog pristupa je $O(Nlog_N K + M)$. Rešenja koja su rešila problem prelaska preko granice, ali rade u $O(N\cdot M)$ prolaze za podzadatak gde je $N\le 10000$ i $M\le 1000$.

Napomena: Korišćenjem operacije deljenja za nalaženje vrednosti $B_i$ može da se zadatak reši u složenosti $O(N+M)$.

``` cpp title="02_sifra.cpp" linenums="1"
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
using namespace std;

#define MaxN 100005
#define MaxM 100005

int n, m;
long long k;
int a[MaxN];

vector<int> KbaseM;

int main()
{
	scanf("%d%d%lld", &n, &m, &k);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	--k;

	if (n == 1) {
		printf("%d", a[0]);
		for (int i = 1; i < m; ++i)
			printf(" %d", a[0]);
		printf("\n");
	}
	else {

		while (k > 0) {
			KbaseM.push_back(k % n);
			k /= n;
		}

		bool first = true;
		for (int i = 0; i < m - KbaseM.size(); ++i) {
			if (first) first = false; else printf(" ");
			printf("%d", a[0]);
		}

		for (int i = KbaseM.size() - 1; i >= 0; --i) {
			if (first) first = false; else printf(" ");
			printf("%d", a[ KbaseM[i] ]);
		}
		printf("\n");

	}
}
```
