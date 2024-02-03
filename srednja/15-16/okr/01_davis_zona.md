---
hide:
  - toc
---

# B1 - Davis zona

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

U starim vremenima, mongolski vladar Petar Kan je vladao Tajnom Komisijom sa čvrstom pesnicom. Predani uzurpator Davis je po svaku cenu rešen da ga zbaci sa trona. Opšte je poznato da Davis dobija nadljudske moći kada uđe u njegovu zonu—zato je Petar rešen da po svaku cenu spreči Davisa da uđe u zonu.

Davisova zona se nalazi unutar tajne prostorije (koja je potpuno okružena zidovima) oblika pravougaonika stranica $a$ i $b$. Prostorija je podeljena na $a · b$ kvadratnih polja dimenzija 1 × 1. Polja su numerisana od (1, 1) (gornje-levo) do (a, b) (donje-desno). Zona je pravougaonik dimenzija c i d, sa gornjim levim poljem $(x, y)$ (ovaj pravougaonik je potpuno sadržan u prostoriji). 

Davis kreće sa polja $(dx, dy)$, i u svakom koraku će se pomeriti za $∆x$ polja nadole, odnosno $∆y$ polja udesno. Ukoliko bi Davis tim pomeranjem udario u zid, odbiće se pod istim uglom pod kojim je udario u njega. Ako Davis udari u zid više od k puta bez da uđe u zonu, odustaće ovoga puta.

Petra sada zanima da li će Davis ikada biti u zoni, i ako hoće, zanima ga polje na kome će
biti kada prvi put bude u zoni, da bi znao da na njega postavi stražare.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva prirodna broja a i b, koji predstavljaju
broj redova i kolona prostorije, redom. U drugom redu nalaze se dva prirodna broja $c$ i $d$, koji predstavljaju broj redova i kolona Davisove zone, redom. U trećem redu nalaze se dva prirodna broja $x$ i $y$, koji predstavljaju red i kolonu gornjeg levog polja zone, redom. U četvrtom redu nalaze se dva prirodna broja $dx$ i $dy$, koji predstavljaju red i kolonu polja sa koga Davis kreće. U petom redu nalaze se tri cela broja $∆x$, $∆y$ i $k$, koji predstavljaju broj polja nadole i udesno za koliko će se Davis pomeriti u svakom koraku, kao i ograničenje za broj udara u zid.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza potrebno je ispisati dva prirodna broja hx
i hy, koji predstavljaju red i kolonu polja na kome će Davis biti prvi put kada se nađe u zoni, redom. Ukoliko Davis ne uspe da uđe u zonu, potrebno je ispisati “NE” (bez navodnika).

## Primer 1
### Ulaz
```
5 4
1 2
2 3
5 2
-1 -1 1
```

### Izlaz
```
2 3
```


## Objašnjenja primera
Na slikama ispod nalazi se opis test primera; na svakoj slici Davisova pozicija
označena je slovom D, polja zone su zatamnjena, a strelica označava polje na koje će Davis otići u sledećem koraku. Davis najpre udara u zid u polju (4, 1); dva koraka nakon toga uspešno ulazi u zonu, i to u polju (2, 3). Pritom nije udario u zid više od jednom, tako da je ovo konačno rešenje koje treba ispisati.

## Ograničenja

* $1 ≤ a, b, c, d ≤ 1000$;
* $1 ≤ c, x, dx ≤ a$;
* $1 ≤ d, y, dy ≤ b$;
* $0 ≤ k ≤ 1000$;
* $∆x, ∆y ∈ \{−1, 0, 1\}$;
* Davisova zona će uvek biti obuhvaćena prostorijom.

## Napomena
* U test primerima vrednim 20 poena važiće $∆x = 0$ ili $∆y = 0$.
* U test primerima vrednim 20 poena važiće $k = 0$.
* U test primerima vrednim 60 poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Dragan Urošević | Mladen Puzić | Ivan Stošić |

##  Rešenje za $\Delta x = 0$ ili  $\Delta y = 0$:
Uslov znači da se krećemo isključivo ili gore-dole ili levo-desno, i samim tim nije potrebno razmatrati komplikovanije sudare sa zidom. Između svaka dva sudara sa zidom proći će najviše $max(a, b)$ sekundi, pa će ukupan broj koraka biti najviše oko $max(a, b) \cdot k$, što je dovoljno malo da možemo simulirati kretanje. To radimo tako što proverimo da li smo trenutno u Davis zoni, pa se pomerimo (ovaj redosled je bitan za slučaj da smo već u početku u Davis zoni). Ukoliko udarimo u zid, samo promenimo smer kretanja u suprotni. Stajemo kada smo u Davis zoni, ili kada *potrošimo* sva odbijanja od zida. Vremenska složenost: $O((a+b)\cdot k)$, memorijska složenost: $O(1)$. 

## Rešenje za $k = 0$:
U ovom slučaju, nikad ne moramo simulirati odbijanje od zidove, već samo kretanje dok ne naiđemo na zid ili Davis zonu. Pošto je najveći broj koraka pre udarca u zid $max(a, b)$, vremenska složenost je $O(a+b)$, a memorijska složenost $O(1)$.

## Glavno rešenje:
Još uvek možemo da simuliramo proces (još uvek između svaka dva udarca u zid ima najviše $max(a, b)$ koraka), samo je potrebno i simulirati komplikovanija odbijanja od zid, konkretno, dijagonalna odbijanja. Na primer, ako udaramo u vertikalan zid, onda ćemo promeniti $\Delta y$, u suprotnom $\Delta x$. Ukoliko udaramo u ćošak, onda menjamo obe vrednosti. Simuliramo dok ne potrošimo sva odbijanja ili ne budemo u Davis zoni. Vremenska složenost: $O((a+b)\cdot k)$, memorijska složenost: $O(1)$. 


``` cpp title="01_davis_zona.cpp" linenums="1"
# include <stdio.h>

main() {
  int a, b, c, d;
  int cx, cy, dx, dy;
  int to, mo;
  int x1, y1, x2, y2;
  scanf("%d%d", &a, &b); 
  scanf("%d%d", &c, &d); 
  scanf("%d%d", &x1, &y1); 
  scanf("%d%d", &cx, &cy); 
  scanf("%d%d%d", &dx, &dy, &mo); 
  x2 = x1 + c - 1;
  y2 = y1 + d - 1;
  if ((dx == 0) && (dy == 0)) {
  	if ((cx >= x1) && (cx <= x2) && (cy >= y1) && (cy <= y2)) 
  	  printf("%d %d\n", cx, cy);
  	else
  	  printf("NE\n");
  	return 0;
  }
  to = 0;
  while (to <= mo) {
  	if ((cx >= x1) && (cx <= x2) && (cy >= y1) && (cy <= y2)) {
  	  printf("%d %d\n", cx, cy);
  	  return 0;
	}
	if ((cx+dx < 1) || (cx+dx > a)) {
	  dx = -dx;
	  if ((cy+dy < 1) || (cy+dy > b)) dy = -dy;
	  to++;
	} else {
	  if ((cy+dy < 1) || (cy+dy > b)) {
	    dy = -dy;	
	    to++;
	  }
	}
	if (to > mo) break;
	cx += dx; cy += dy;  
  }
  printf("NE\n");
  return 0;
}

```
