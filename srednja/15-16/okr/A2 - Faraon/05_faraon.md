---
hide:
  - toc
---

# A2 - Faraon

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |


Prema istoričarima, u staroj egipatskoj državi, faraoni su morali da dokažu predstavnicima plemena da su dovoljno snažni da vode državu tako što su pred njima morali da se bore sa bikom i da mu iščupaju rep. Međutim, manje poznato je da su faraoni morali da dokažu i da su dovoljno pametni rešavajući drevni matematički zadatak.

U drevnom matematičkom zadatku su postavljena dva broja $p$ i $q$. Faraon je morao da odgovori u koliko najmanje specijalnih matematičkih operacija može od broja p da se dobije broj q. Specijalne matematičke operacije su sledeće:

* Broj $t$ može da se pomnoži bilo kojim prostim brojem $r$, kako bi se dobio broj $t · r$
* Broj $t$ može da se podeli bilo kojim prostim brojem $r$ koji deli $t$, kako bi se dobio broj $t/r$.

Naravno, faraon je znao da su prosti brojevi oni prirodni brojevi veći od 1 koji su deljivi samo sa 1 i samim sobom. Kako bi mu otežali posao, predstavnik svakog plemena mu zadaje nove brojeve $p$ i $q$, i faraon mora tačno da odgovori na svaki zadati par brojeva. Istoričari su pronašli stari zapis na kojem su zapisani postavljeni brojevi faraonu i znajući da je faraon dokazao da je pametan (odgovorio je tačno na sva pitanja) vaš zadatak je da pronađete faraonove odgovore za svaki par postavljenih brojeva $p$ i $q$.


## Opis ulaza
U prvom redu standardnog ulaza će se nalaziti ceo broj $N$ koji označava broj plemena
(broj postavljenih pitanja). U narednih $N$ redova će se nalaziti po dva cela broja $p$ i $q$.

## Opis izlaza
Na standardni izlaz potrebno je ispisati $N$ redova gde se u $k$-tom redu nalazi odgo-
vor faraona na $k$-to pitanje iz ulaza.

## Primer 1
### Ulaz
```
5
1 1
16 2
2 3
3 9
6 10
```

### Izlaz
```
0
3
2
1
2
```

## Ograničenja

* $1 ≤ N ≤ 10^6$
* $1 ≤ p, q ≤ 10^6$

## Napomena
Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim 20 poena važi $N ≤ 10^4$.
* U test primerima vrednim 40 poena važi $p, q ≤ 10^5$.
* U test primerima vrednim 40 poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Demjan Grubić | Demjan Grubić | Mladen Puzić | Dimitrije Erdeljan |

Označimo sa $d$ najveći zajednički delilac brojeva $p$ i $q$. Prvo ćemo broj $p$ podeliti sa $p/d$, tako da dobijemo broj $d$, pa ga pomnožiti sa $q/d$, tako da dobijemo $q$. To, naravno, radimo jednim po jednim prostim brojem. Tako dobijamo $q$ od $p$, a optimalno je, jer nema potrebe da dalje delimo $p$ nakon što ga spustimo do $d$.

Ostaje nam samo da efikasno faktorišemo brojeve $p/d$ i $q/d$ i tako izbrojimo broj koraka koji su nam potrebni (što je zbir eksponenata u kanonskoj faktorizaciji tih brojeva).

## Rešenje za $N \leq 10^4$
Pošto je $N$ malo, možemo manje efikasno faktorisati brojeve. Konkretno, možemo to uraditi u složenosti $O(\sqrt x)$, za broj $x$ koji faktorišemo. To možemo uraditi tako što ćemo proći redom kroz sve brojeve od $2$ do $\lfloor \sqrt x \rfloor$ i deliti broj $x$ njima dokle god je moguće. Ovako ćemo ga uvek deliti prostim faktorima, jer kad dođemo do složenog broja, nijedan njihov prosti činilac više neće deliti $x$. Ukoliko nam ostane broj koji je veći od $1$ i taj broj je prost faktor broja $x$ (ovo je tačno jer broj $x$ može imati najviše jedan prost faktor koji je veći od $\lfloor \sqrt x \rfloor$). Ukupno će prostih faktora biti najviše $\lceil \log_2{x} \rceil$, pa deljenje njima ne utiče na složenost.

Vremenska složenost je $O(N\cdot (\sqrt p + \sqrt q)$), a memorijska $O(1)$.

## Rešenje za $p, q \leq 10^5$
Koristićemo istu faktorizaciju kao u prethodnom rešenju, samo što ćemo, pre nego što odgovorimo na bilo koje pitanje, izračunati broj prostih faktora svih brojeva od $1$ do $M$ (u ovom slučaju $M = 10^5$). Nakon toga koristimo te informacije kako bismo u $O(1)$ odgovorili na svako pitanje.

Vremenska složenost je $O(N\log M + M \sqrt {M})$, a memorijska $O(M)$.


## Glavno rešenje
Potrebno je da faktorizaciju uradimo efikasnije. Koristimo modifikovano Eratostenovo sito, pošto su nam brojevi do $10^6$, da pre svih pitanja izračunamo sledeće: 
- za svaki broj $x$ od $1$ do $M$, koji je najmanji prost broj koji deli $x$?

Kada naiđemo na prost broj, za sve njegove množioce proverićemo da li oni već imaju manjeg prostog delioca. Ukoliko ne, onda je u pitanju naš trenutni prost broj. Kada imamo ovu informaciju, zbir eksponenata u kanonskoj faktorizaciji $x$ je samo broj koraka koji nam je potreban da dovedemo $x$ do $1$, uvek ga deleći sa njegovim najmanjim prostim deliocem. Tih koraka će biti najviše $\lceil \log_2{x} \rceil$.

Vremenska složenost je $O(maxPQ \log maxPQ + N log)$



``` cpp title="05_faraon.cpp" linenums="1"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
using namespace std;

const int MaxNumber = 1000000;

int T, p, q;

int sqrtMaxNumber;
int smallestDivisor[MaxNumber+5];
int dp[MaxNumber+5];

int gcd(int a, int b)
{
	while (b) {
		int c = a % b;
		a = b;
		b = c;
	}

	return a;
}

int main()
{
	memset(smallestDivisor, -1, sizeof(smallestDivisor));
	sqrtMaxNumber = int(sqrt(MaxNumber)) + 1;

	smallestDivisor[1] = -1;
	for (int number = 2; number <= sqrtMaxNumber; ++number) {
		if (smallestDivisor[number] != -1) continue;

		smallestDivisor[number] = number;
		for (int curr = number * number; curr <= MaxNumber; curr += number) {
			if (smallestDivisor[curr] == -1) smallestDivisor[curr] = number;
		}
	}
	for (int i = sqrtMaxNumber; i <= MaxNumber; ++i) {
		if (smallestDivisor[i] == -1) smallestDivisor[i] = i;
	}

	dp[1] = 0;
	for (int number = 2; number <= MaxNumber; ++number) {
		int previousNumber = number / smallestDivisor[number];
		dp[number] = dp[previousNumber] + 1;
	}

	scanf("%d",&T);
	for (;T--;) {
		scanf("%d%d",&p,&q);
		int result = dp[p] + dp[q] - 2 * dp[gcd(p,q)];
		printf("%d\n",result);
	}

	return 0;
}
```
