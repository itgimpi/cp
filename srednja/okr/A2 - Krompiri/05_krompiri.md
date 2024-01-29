---
hide:
  - toc
---

# A2 - Krompiri

# Zadatak
	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 750ms | 64MB |
	
Čuveni astro-botaničar Mateja Dejmon se još od 2017. godine uspešno bavi uzgojem krompira na Marsu zahvaljujući pomoći takmičara iz informatike.
	
On je ove godine odlučio da napravi novu farmu krompira na Marsu i ponovo mu je potrebna vaša pomoć. Njemu je na raspolaganju plodno marsovsko zemljište dimenzija $N \times M$ koje je on izdelio na $N \cdot M$ jediničnih polja. Na svakom polju je moguće posaditi određen broj krompira, međutim, zbog posebnog sastava marsovskog zemljišta u redu $i$ ukupno ne sme biti manje od $a_i$ niti više od $b_i$ krompira (za svako $i = 1,2,\ldots,N$). Takođe, u koloni $j$ ukupno ne sme biti manje od $c_j$ niti više od $d_j$ krompira (za svako $j = 1,2,\ldots,M$).
	
Pomozite Mateji da odredi raspored krompira koji će maksimizovati njegov prinos tj. pomozite mu da posadi što više krompira.
	
## Ulaz
U prvom redu standardnog ulaza nalaze se, redom, dva cela broja $N$ i $M$ - dimenzije zemljišta.
	
U narednih $N$ redova nalaze se po dva cela broja $a_i$ i $b_i$ - ograničenja za $i$-ti red.
	
U narednih $M$ redova nalaze se po dva cela broja $c_j$ i $d_j$ - ograničenja za $j$-tu kolonu.
	
## Izlaz
U prvom redu standardnog izlaza ispisati maksimalan broj krompira koji Mateja može da posadi.
	
U drugom redu ispisati broj $K$ - broj polja na kojima treba posaditi krompire.
	
U narednih $K$ redova ispisati po tri cela broja $x$, $y$ i $n$ ($1 \leq x \leq N$, $1 \leq y \leq M$, $n \geq 0$), redom, koji označavaju da na polju u preseku $x$-tog reda i $y$-te kolone treba posaditi $n$ krompira.
	
Raspored krompira mora biti takav da poštuje sva ograničenja iz teksta zadatka. **Ukoliko ima više rešenja, ispisati bilo koje.**
	
## Primer 1
### Ulaz
```
2 2
1 2
1 1
1 3
0 0
```
	
### Izlaz
```
3
2
1 1 2
2 1 1
```
	
## Primer 2
### Ulaz
	
```
2 3
2 2
2 2
1 2
1 2
1 2
```
	
### Izlaz
	
```
4
4
1 1 1
1 3 1
2 2 1
2 3 1
```
	
## Objašnjenje primera
U tabeli ispod je prikazan jedan mogući raspored krompira koji zadovoljava ograničenja i maksimizuje prinos u **prvom primeru** (izrazi oblika $x-y$ u tabeli označavaju donju i gornju granicu za broj krompira u odgovarajućem redu/koloni).
	
| | 1-3 |0-0|
| ---        |    :----:   |          :---: |
|**1-2**| 2 | 0 |
|**1-1**| 1 | 0 |
	
U tabeli ispod je prikazan jedan mogući raspored krompira koji zadovoljava ograničenja i maksimizuje prinos u **drugom primeru**:
	
| | 1-2 |1-2| 1-2 |
| ---   |    :----:   | :---: | :---:|
|**2-2**| 1 | 0 | 1 |
|**2-2**| 0 | 1 | 1 |
	  
## Ograničenja
	
- $1 \leq N, M \leq 50000$.
- $0 \leq a_i \leq b_i \leq 10^9$.
- $0 \leq c_i \leq d_i \leq 10^9$.
- **Garantuje se da postoji raspored krompira koji zadovoljava sve uslove**.
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
- U testovima vrednim $10$ poena: $N=M, a_i \leq c_i \leq b_i \leq d_i$.
	- U testovima vrednim $10$ poena: $a_i = b_i, c_i = d_i$.
	- U testovima vrednim $15$ poena: $a_i = b_i$.
	- U testovima vrednim $15$ poena: $N = 1$.
	- U testovima vrednim $30$ poena: $a_i = c_i = 0$.
	- U testovima vrednim $20$ poena: Bez dodatnih ograničenja.
	
