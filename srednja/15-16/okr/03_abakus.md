---
hide:
  - toc
---

# B3 - Abakus

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |


Stari Vavilonci su koristili jednu varijantu naprave Abakus za komplikovana matematička izračunavanja. Abakus se sastoji od $n$ kuglica numerisanih brojevima od 1 do $n$. Svaka od kuglica se može nalaziti na jednoj od 10 pozicija (numerisanih brojevima od 0 do 9), a te pozicije govore o vrednosti koju ima odgovarajuća kuglica (to su vrednosti od 0 do 9). Kuglice su podeljene u $m$ disjunktnih grupa, numerisanih brojevima od 1 do $m$ (pojedine grupe mogu biti prazne). Korisnik ima na raspolaganju dve vrste operacija:
* Postavi $BrG$ $Poz$, ovom komandom postavljaju se sve kuglice iz grupe $BrG$ u poziciju $Poz$
(tj. postavlja vrednost svih kuglica iz te grupe na Poz). Ova operacija ima cenu $C1$.

* Promeni $BrK$ $Poz$, ovom komandom se premešta samo kuglicu sa rednim brojem $BrK$ na poziciju $Poz$ (tj. menja se njena vrednost na $Poz$). Za ovu operaciju korisnik plaća cenu jednaku "kružnom rastojanju" između dosadašnje pozicije te kuglice i nove pozicije. "Kružno rastojanje" je najkraće rastojanje između pozicija, ako bi one bile poređane na krugu u skladu sa numeracijom. Npr. kružno rastojanje između 0 i 7 je 3, između 1 i 9 je 2, a imeđu 7 i 3 je 4.

Dobili ste opis Abakusa (broj kuglica, cenu operacije Postavi (C1) i podelu kuglica po grupama), početno stanje kuglica (tj. poziciju u kojoj se nalazi svaka od kuglica na početku) i krajnje stanje kuglica (tj. pozicije na kojima treba na kraju da se nalaze). Potrebno je da odredite minimalnu cenu da se od zadatog početnog stanja kuglica (tj. početnih pozicija kuglica) dođe do krajnjeg stanja kuglica.


## Opis ulaza
U prvom redu standardnog ulaza se nalazi broj kuglica ($n$) i cena operacije Postavi ($C1$).
U drugom redu se nalazi $n$ prirodnih brojeva, a $i$-ti od njih predstavlja redni broj grupe u kojoj se nalazi $i$-ta kuglica. U trećem redu se nalazi $n$ brojeva, a $i$-ti od tih brojeva predstavlja početnu poziciju (tj. početnu vrednost) $i$-te kuglice. U četvrtom redu se nalazi $n$ brojeva, a $i$-ti od tih brojeva predstavlja krajnju poziciju $i$-te kuglice.

## Opis izlaza
Na standardni izlaz ispisati samo jedan broj - minimalnu zbirnu cenu operacija koje
treba izvesti da bi se kuglice dovele na krajnje pozicije.

## Primer 1
### Ulaz
```
8 3
6 5 6 5 5 6 1 2
5 1 5 2 3 5 8 0
0 1 0 2 3 8 4 8
```

### Izlaz
```
10
```
## Objašnjenja primera
Kuglice iz grupe 5 ne moramo uopšte premeštati. Kuglice iz grupe 6 prebacujemo
komandom Postavi 6 0 u poziciju 0, a zatim komandom Promeni 6 8 i plaćamo cenu 5 (3+2).
Kuglicu iz grupe 1 prebacujemo komandom Postavi 1 4 i plaćamo cenu 3 (ako bi koristili komandu Promeni 7 4 platili bi 4). Kuglicu iz grupe 2 prebacujemo komandom Promeni 8 8 i plaćamo cenu 2 (komandom Postavi 2 8 platili bi 3).

## Ograničenja
* $1 \leq n \leq 10^6$.
* $1 \leq m \leq 1000$.
* $1 \leq C1 \leq 10^6$.

## Napomena
Test primeri su podeljeni u tri disjunktne grupe

* u test primerima koji vrede 30 poena važiće da se sve kuglice nalaze u jednoj grupi (tj. $m$ = 1).
* u test primerima koji vrede 30 poena svaku od grupa čini blok uzastopnih kuglica (tj. blok kuglica čije su oznake uzastopni prirodni brojevi).
* u test primerima koji vrede 40 poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Jovanović | Dragan Urošević | Marko Ilić | Demjan Grubić |

## Rešenje za $m = 1$:
Ono što treba primetiti jeste da operaciju kojom prebacujemo sve kuglice jedne grupe na određenu poziciju ima smisla raditi samo na početku i to maksimalno jednom, jer bilo koja operacija koja se odradi pre takve operacije ne bi imala uticaj na krajnji rezultat. Dakle, možemo da uopšte ne koristimo tu operaciju, ili da sve kuglice prebacimo u neku od deset grupa, pa onda one koje ne treba da budu tu, prebacimo u odgovarajuće grupe pomoću druge operacije. Kao rešenje treba izabrati najjeftiniju opciju. Vremenska složenost: $O(N \cdot maxC)$, gde je $maxC$ broj cifara, memorijska složenost: $O(N)$.

## Rešenje kada svaku od grupa čini blok uzastopnih kuglica:
S tim da kuglice iz različitih grupa ne možemo pomerati u istoj operaciji, treba svaku grupu posebno rešiti, pa će konačno rešenje biti suma rešenja za svaku od grupa. U ovom podzadatku možemo jednostavno izdvojiti grupe s tim da su to uzastopne kuglice i nakon toga za svaku grupu primeniti ideju iz prvog podzadatka. Vremenska  složenost: $O(N \cdot maxC)$, memorijska složenost: $O(N)$.  

## Glavno rešenje:
Razlika u odnosu na prethodni podzadatak je u tome što ovde prvo treba odvojiti kuglice po grupama. Možemo da za svaku grupu izgradimo niz kuglica koje se nalaze u njoj i nakon toga treba primeniti ideju iz prethodnog podzadatka. Vremenska složenost: $O(N \cdot maxC)$, memorijska složenost: $O(N)$

``` cpp title="03_abakus.cpp" linenums="1"
# include <stdio.h>
# include <stdlib.h>

# define MAXN 1000000
# define MAXM 1000

int c1;
int n, m;
int g[MAXN];
int a[MAXN], b[MAXN];
int brp[MAXM][10][10];
int brf[MAXM][10];
int ukc, minc, trenc;
int c2[10][10];

void citaj() {
	int i;
	scanf("%d%d", &n, &c1);
	for (i = 0; i < n; i++) 
	  scanf("%d", &g[i]);
	for (i = 0; i < n; i++) 
	  scanf("%d", &a[i]);
	for (i = 0; i < n; i++) 
	  scanf("%d", &b[i]);	
}

void odredic2() {
	int i, j;
	for (i = 0; i < 10; i++) 
	  for (j = 0; j < 10; j++) {
	  	c2[i][j] = abs(i - j);
	  	if (10 - c2[i][j] < c2[i][j])
	  	   c2[i][j] = 10 - c2[i][j];
	  }
}

void prebroj() {
	int i;
	int mt;
	for (i = 0; i < n; i++) {
		mt = g[i];
		if (mt > m) m = mt;
		brp[mt][a[i]][b[i]]++;
		brf[mt][b[i]]++;
	}
}

void resi() {
	int mt;
	int i, j;
	for (mt = 0; mt <= m; mt++) {
	    trenc = 0;
		for (i = 0; i < 10; i++)
		  for (j = 0; j < 10; j++)
		    trenc += brp[mt][i][j] * c2[i][j];
		minc = trenc;
		for (i = 0; i < 10; i++) {
			trenc = c1;
			for (j = 0; j < 10; j++)
			  trenc += brf[mt][j] * c2[i][j];
			if (trenc < minc)
			  minc = trenc;
		}
		ukc += minc;
	}
}

void pisi() {
	printf("%d\n", ukc);
}

main() {
	citaj();
	odredic2();
	prebroj();
	resi();
	pisi();
}

```
