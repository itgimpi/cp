# A1 - Poklon

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |
	
Kao nagradu za prolaz na okružno takmičenje, komisija Vam poklanja $Q$ nizova. Svaki od nizova je dobijen tako što je od glavnog niza $A$, dužine $N$, kopiran neki uzastopni podniz. Preciznije, $i$-ti niz je određen vrednostima $l_i$ i $r_i$, što znači da on sadrži elemente ${A_{l_i}, A_{l_i+1}, ... , A_{r_i}}$, u tom redosledu.
	
Vama se, međutim, ovaj poklon ne sviđa mnogo, jer Vi volite samo nizove koji su sortirani u neopadajućem poretku. Zato ćete malo izmeniti nizove koje ste dobili. Pošto ne želite da ispadnete nezahvalni, nećete ih mnogo menjati, pa ćete iz svakog niza izbrisati **najviše jedan** element. Takođe, pošto Vas ipak mrzi da sada menjate toliki broj nizova, dovoljno je da za svaki od njih samo odredite da li ga je uopšte moguće izmeniti da postane sortiran.
	
Podrazumeva se da brisanje elementa iz jednog niza **ne utiče** na druge nizove.
	
## Opis ulaza
Prvi red standardnog ulaza sadrži ceo broj $N$, broj elemenata glavnog niza.

Drugi red sadrži $N$ celih brojeva koji predstavljaju glavni niz $A_1, A_2, ..., A_N$.
	
Treći red sadrži ceo broj $Q$, broj poklonjenih nizova.
	
Narednih $Q$ redova sadrže po dva broja, $l_i, r_i$, koji označavaju da $i$-ti niz sadrži elemente ${A_{l_i}, A_{l_i+1}, ... , A_{r_i}}$, u tom redosledu.
	
## Opis izlaza
Na standardni izlaz je potrebno ispisati $Q$ linija - u $i$-toj liniji ispisati "DA" (bez navodnika) ako je $i$-ti niz moguće sortirati brisanjem najviše jednog elementa, u suprotnom ispisati "NE" (bez navodnika).
	
## Primer 1
### Ulaz

```
7
1 7 2 7 2 2 3
4
1 4
2 7
4 6
5 5
```
	
### Izlaz
```	
DA
NE
DA
DA
```
	
## Objašnjenje primera
Prvi niz je $[A_1, A_2, A_3, A_4]$, tj. $[1, 7, 2, 7]$. Iz njega možemo izbrisati drugi element da bismo dobili niz $[1, 2, 7]$.
	
Drugi niz je $[A_2, A_3, A_4, A_5, A_6, A_7]$, tj. $[7, 2, 7, 2, 2, 3]$. Može se videti da koji god element izbrišemo, niz neće biti sortiran.
	
Treći niz je $[A_4, A_5, A_6]$, tj. $[7, 2, 2]$. Iz njega možemo izbrisati prvi element da bismo dobili niz $[2, 2]$.
	
Četvrti niz je $[A_5]$, tj. $[2]$. On je već sortiran, pa ne moramo raditi ništa.
	
## Ograničenja
	
- $1 \leq N \leq 2 \cdot 10^5$.
- $1 \leq Q \leq 10^5$.
- $1 \leq L_i \leq R_i \leq N$ za $1 \leq i \leq Q$.
- $1 \leq A_i \leq N$.
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
- U testovima vrednim 15 poena: $N, Q \leq 200$.
- U testovima vrednim 25 poena: $N, Q \leq 3000$.
- U testovima vrednim 10 poena: $Q = 5$.
- U testovima vrednim 20 poena: Svi elementi niza su $1$ ili $2$.
- U testovima vrednim 30 poena: nema dodatnih ograničenja.                                                                                                                     
	
## Napomena
Niz $[B_1, B_2, B_3, ... , B_M]$ je sortiran u neopadajućem poretku ako i samo ako važi $B_1 \leq B_2 \leq ... \leq B_M$.
	