---
hide:
  - toc
---

# A3 - Sdneirf

# Zadatak
	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |
	
Prethodnih godina, filmovi duologije o velikom šefu mafije ekskluzivne disjunkcije *Okram Ćivas* postali su neki od najpopularnijih i najvoljenijih na tržištu. Duologija se sastojojala od, kao što ime kaže, dva filma, koji se zovu *Okram* i *Ćivas*. Međutim, usled lude popularnosti prethodna dva filma, pokrenula se proizvodnja za treći i poslednji deo ovog serijala - "Sdneirf". U ovom filmu Okram Ćivas je odavno napustio mafiju i sad živi srećno sa svojom porodicom. Međutim, onda stiže poziv za jedan poslednji zadatak...
	 
U poslednjoj avanturi našeg heroja, slično kao u prvoj (mora da se gađa na nostalgiju u ovakvim filmovima), on se zatekao u misterioznoj matrici, dimenzija $N\times M$. U svakom polju matrice je napisan po jedan ceo nenegativan broj, konkretno u polju u preseku reda $i$ i kolone $j$ se inicijalno nalazi vrednost $a_{i,j}$. Posle zabune oko toga šta se dešava, Okram Ćivas je shvatio da ima samo jedan način na koji može da menja vrednosti u ovoj matrici. U svakom potezu, on može da izabere nenegativan ceo broj $X$ i neki niz od $N+M-1$ polja koji počinje od gornjeg levog polja i završava se na donjem desnom, tako da svaka dva susedna polja u tom nizu dele stranicu, i onda za svako polje na tom putu promeni vrednost u njemu na sledeći način: ako se pre ovog poteza u ovom polju nalazio broj $Y$, nova vrednost u ovom polju će biti $Y\text{ xor }X$.
	
Kako je Okram Ćivas poznat po svojoj majstoriji sa ekskluzivnom disjunkcijom, on je sebi zadao sledeći zadatak: posle proizvoljnog broja poteza, koja je najmanja moguća suma svih vrednosti u matrici? Ako uspe da minimizuje sumu, deluje da će uspeti da pobegne iz ove matrice i zauvek napusti svet kriminala.
	
## Opis ulaza
Prva linija standardnog ulaza sadrži dva cela broja, broj redova $N$ i broj kolona $M$, redom. Narednih $N$ linija sadrže po $M$ celih brojeva: $j$-ti broj u $(i+1)$-voj liniji predstavlja broj $a_{ij}$, koji označava početnu vrednost polja u $i$-tom redu i $j$-toj koloni.
	
## Opis izlaza
U jedinoj liniji standardnog izlaza potrebno je ispisati jedan ceo broj: najmanju moguću sumu brojeva u matrici posle nekog broja poteza.
	
## Primer 1
### Ulaz
```
1 2
1 0
```
	
### Izlaz
```
1
```
	
## Primer 2
### Ulaz
```
2 3
2 7 5
5 7 2
```
	
### Izlaz
```
0
```
	
## Objašnjenje primera
U prvom primeru, početna suma je jedan. Ovo je minimalna vrednost jer je suma pozitivna posle proizvoljno mnogo poteza.
	
U drugom primeru, u prvom potezu Okram Ćivas može uzezi $X=7$ i niz polja $(1,1),$ $(1,2),$ $(2,2),$ $(2,3)$, a onda napravi $3$ poteza sa $X=5$ i prvo nizom polja $(1,1),$ $(2,1),$ $(2,2),$ $(2,3)$, zatim nizom polja $(1,1),$ $(1,2),$ $(1,3),$ $(2,3)$ i na kraju nizom $(1,1),$ $(1,2),$ $(2,2),$ $(2,3)$.
	
## Ograničenja
	
-   $1 \leq N,M \leq 1.500$.
-   $0\leq A_{ij}\leq 1.000.000.000$.
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
-   U test primerima vrednim $10$ poena: $N,M\leq2$.
-   U test primerima vrednim $10$ poena: $N=1$.
-   U test primerima vrednim $20$ poena: $N=2$.
-   U test primerima vrednim $30$ poena: $0\leq A_{ij}\leq 1$.
-   U test primerima vrednim $30$ poena: Bez dodatnih ograničenja.
	
## Napomena
Operator ekskluzivne disjunkcije u Pascal-u je označen sa  `xor`, dok u C++ ga zapisujemo pomoću simbola  `^`. Ova operacija $x\ \text{xor} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način. Prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in {1, \ldots, k }$ računa $c_i$ pomoću sledećih pravila:
	
-   Za $a_{i} = 0, b_{i} = 0$ važi $c_{i} = 0$
-   Za $a_{i} = 0, b_{i} = 1$ važi $c_{i} = 1$
-   Za $a_{i} = 1, b_{i} = 0$ važi $c_{i} = 1$
-   Za $a_{i} = 1, b_{i} = 1$ važi $c_{i} = 0$
	
Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{xor} \ y$.
	
Ako želite da upoznate sa prethodnim avanturama Okrama Ćivasa, posle takmičenja možete da pogledate prošlogodišnji treći zadatak za B kategoriju na okružnom: *Okram*, kao i prošlogodišnji drugi zadatak za A kategoriju na okružnom: *Ćivas*
	