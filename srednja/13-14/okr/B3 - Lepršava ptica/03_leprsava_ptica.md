---
hide:
  - toc
---

# B3 - Lepršava ptica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Mlada studentkinja Mihaela je do sada bila najbolji student u svojoj generaciji sa najboljim ocenama. Međutim u poslednje vreme je postala lenja i posebno su joj postala dosadna predavanja iz informatike, iako joj je to pre bio omiljeni predmet. Trenutno se nalazi na predavanju iz informatike i kako se ne bi dosađivala, ona će se takmičiti sa svojim drugarima u igrici „Lepršava ptica“, koja je veoma slična popularnoj igrici “Flappy bird”. Ona ima vremena samo za jednu partiju igrice, te hoće da postigne što bolji rezultat.

Poenta igrice je da navodite lepršavu pticu tako da ne udari u cevi koje se nalaze sa gornje i donje strane mape. Mapu igrice možemo da posmatramo kao matricu visine $H$, dok je dužina matrice neograničena. Poznato je da postoji tačno $N$ cevi na mapi i za svaku cev se zna na kojoj poziciji se nalazi, kolika je visina dela cevi koji se proteže od vrha mape na dole i kolika je visina dela cevi koji se proteže od donjeg kraja mape na gore. Širina cevi je jednaka širini jednog polja u matrici.

Ptica se na početku nalazi na početku mape, tj. poziciji $0$, i na visini $\frac{H+1}{2}$ ukoliko je $H$ neparan broj, inače na visini $\frac{H}{2}$ i zauzima tačno jedno polje u matrici. U svakom trenutku se lepršava ptica pomeri za jedno mesto u desno na mapi, dok od Mihaele zavisi da li će da se pomeri za jedno mesto na gore ili na dole u matrici. Ukoliko Mihaela pritisne dugme na mišu lepršava ptica će se pomeriti za jedno mesto na gore, dok će u suprotnom da se pomeri za jedno mesto na dole. Preciznije rečeno, ukoliko se lepršava ptica nalazi na polju $(X,Y)$ u sledećem trenutku će se nalaziti ili na poziciji $(X+1,Y+1)$ ili na pozicji $(X+1,Y-1)$.

Vaš zadatak je da odredite maksimalni broj poena koji Mihaela može da osvoji ukoliko vam je poznata cela mapa igrice i ukoliko znate da svaki put kad lepršava ptica prođe kroz prolaz koji je napravljen od cevi dobijate $1$ poen. U trenutku kada lepršava ptica udari u cev ili izađe iz granica mape umire.

## Ulaz
U prvom redu standardnog ulaza se nalaze prirodni brojevi brojevi $H$ i $N$ koji redom označavaju visinu mape i broj cevi na mapi. U svakom od sledećih $N$ redova se nalaze po tri prirodna broja $X$, $H_d$ i $H_g$ koji označavaju redom koliko je cev udaljena od početka mape, dužinu dela cevi koji počinje sa gornjeg dela i visinu dela cevi koji počinje sa donjeg dela mape. Cevi će biti zadate u rastućem poretku po poziciji gde se nalaze i neće postojati dve cevi sa istom pozicijom.

## Izlaz
U prvom i jedinom redu standardnog izlaza potrebno je ispisati maksimalan broj poena koji Mihaela može osvojiti.

## Primer 1
### Ulaz
```
5 4
4 2 1
6 1 2
9 2 2
11 1 1
```

### Izlaz
```
2
```

## Objašnjenje primera
```
5| .  .  .  .  #  .  #  .  .  #  .  #  .  .  .
4| .  .  .  .  .  .  #  .  .  #  .  .  .  .  .
3| P  .  .  .  .  .  .  .  .  .  .  .  .  .  .
2| .  .  .  .  #  .  .  .  .  #  .  .  .  .  .
1| .  .  .  .  #  .  #  .  .  #  .  #  .  .  .
----------------------------------------------
0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
```

(`P` – ptica na početku, `#` - cevi)
Lepršava ptica ne može da prođe kroz prolaz koji je napravljen od treće cevi.

## Ograničenja

* $1\leq N\leq 10^5$.
* Svi ostali brojevi iz ulaza su prirodni brojevi ne veći od $10^9$.
* Za svaku cev iz ulaza će važiti $H_g + H_d \leq H$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $30$ poena važi $H, X\leq 1000$.
* U test primerima vrednim $30$ poena važi $H\cdot X\leq 10^6$.
* U test primerima vrednim $40$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Demjan Grubić | Aleksandar Višnjić | Dimitrije Dimić |

## Prvi podzadatak
Neka je $W$ maksimalno moguće $X$. Pamtimo za svih $W\cdot H$ polja da li je moguće doći do njih u matrici tipa $boolean$. Do polja $(x,y)$ je moguće doći ukoliko ono nije zid i moguće je pre njega doći do $(x-1,y-1)$ ili $(x-1,y+1)$. "Najdesnije" polje određuje maksimalan mogući broj poena. Složenost je $O(W\cdot H)$.

## Drugi podzadatak
Pošto nije moguće napraviti $10^5\cdot 10^5$ statičku matricu, polja moramo skladištiti u drugačijoj strukturi; Dinamička matrica (tip vector<vector< bool> >) ili niz sa indeksiranjem polja $(i,j)$ kao $i\cdot H + j$ zadovoljavaju uslov zadatka.

## Glavno rešenje
Za svaku cev ćemo pamtiti maksimalno gornje polje do kog je moguće stići, kao i minimalno donje polje. Ukoliko odredimo da do neke nije moguće stići, potrebno je samo ispisati indeks te cevi kao rešenje zadatka (brojimo sve cevi pre nje kroz koje smo uspešno prošli). Ako smo trenutno kod cevi $i$ sa i znamo maksimalnu i minimalnu i minimalnu visinu na kojoj se možemo naći - $G_i$ i $D_i$, a treba doći do cevi $i+1$, Nova visinska ograničenja postaju $$G_{i+1}=min(G_i+X_{i+1}-X_i,H-H_g-1)$$ $$D_{i+1}=max(D_i-X_{i+1}+X_i,H_d+1)$$
Potrebno je ispitati da li je $G_{i+1}<D_{i+1}$; u tom slučaju je nemoguće preći taj zid. Složenost je $O(N)$.



``` cpp title="03_leprsava_ptica.cpp" linenums="1"
#include <iostream>
#include <ctime>
#include <stdio.h>
using namespace std;

#define MaxN 1000010

int n,h;
int x[MaxN];
int hg[MaxN];
int hd[MaxN];

int currUp, currDown;

int main()
{
	scanf("%d%d",&h,&n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d",&x[i],&hd[i],&hg[i]);
	}

	if ( h % 2 == 1 ) currUp = currDown = (h+1) / 2;
	else currUp = currDown = h / 2;

	int ret = 0;
	int currPosition = 0;
	while ( ret < n && currDown <= currUp ) {
		int distance = x[ret] - currPosition;
		int maxH = currUp + distance;
		int minH = currDown - distance;

		int newCurrUp = min( h - hg[ret], maxH );
		int newCurrDown = max( hd[ret] + 1, minH );

		if ( distance % 2 == 1 ) {
			if ( currUp % 2 == newCurrUp % 2 ) --newCurrUp;
			if ( currDown % 2 == newCurrDown % 2 ) ++newCurrDown;
		}
		else {
			if ( currUp % 2 != newCurrUp % 2 ) --newCurrUp;
			if ( currDown % 2 != newCurrDown % 2 ) ++newCurrDown;
		}

		currPosition = x[ret];
		currUp = newCurrUp;
		currDown = newCurrDown;
		if ( currDown <= currUp ) ++ret;
	}

	printf("%d\n",ret);

	return 0;
}

```
