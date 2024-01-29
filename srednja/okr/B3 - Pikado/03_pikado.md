---
hide:
  - toc
---

# B3 - Jednostavni pikado
	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 512MB |
	
Bane igra jednostavni pikado koji je organizovan tako da je tabla standardna $xy$ ravan sa nekoliko (konačno mnogo) takozvanih "kontrolnih tačaka" $(x_1, y_1)$, $(x_2, y_2)$, $\ldots$ sa celobrojnim koordinatama.
	
Za ovaj pikado važe posebna pravila! Neka je broj kontrolnih tačaka $N$. Bane će baciti strelicu i ukoliko ta strelica pogodi ravan u tački sa koordinatama $(x_A, y_A)$, tada Bane osvaja poene na sledeći način:
- Ako za svaku kontrolnu tačku $(x_i, y_i)$ važi da je $x_i \neq x_A$, Bane osvaja 0 poena;
- Ako za svaku kontrolnu tačku $(x_i, y_i)$ važi da je $y_i \neq y_A$, Bane osvaja 0 poena; 
- Inače (tj. ako među kontrolnim tačkama postoji bar jedna sa $x$ koordinatom jednakom $x_A$ i bar jedna sa $y$ koordinatom jednakom $y_A$) broj poena koje Bane osvaja je jednak 
	
$$\sum_{i=1}^{N}|x_i-x_A|\cdot|y_i-y_A|$$
	
Dat je niz od $M$ tačaka sa celobrojnim koordinatama $(x_1, y_1)$, $(x_2, y_2)$, $\ldots$ $(x_M, y_M)$. Za svako $i = 1,2, \ldots, M$ ispisati koji je najveći broj poena koji Bane može da dobije **u jednom bacanju** ukoliko skup kontrolnih tačaka sadrži samo prvih $i$ tačaka ovog niza. **Rezultate ispisivati po modulu $10^9 + 7$.**
	
## Opis ulaza
U prvoj liniji ulaza nalazi se ceo broj $M$ - ukupan broj tačaka u nizu
	
U narednih $M$ linija nalaze se parovi celih brojeva odvojenih razmakom koji predstavljaju koordinate tačaka $x_i, y_i$
	
## Opis izlaza
U $M$ linija ispisati brojeve $R_1, R_2, ..., R_M$, redom, gde je $R_i$ najveći mogući broj poena **po modulu $10^9 + 7$** koji Bane može osvojiti ako skup kontrolnih tačaka sadrži isključivo prvih $i$ tačaka iz niza. 
	
## Primer 1
### Ulaz
```
3
2 1
1 2
3 3
```
	
### Izlaz
```
0
1
4
```
	
## Primer 2
### Ulaz
```
4
1 2
2 1
5 4
3 5
```
	
### Izlaz
```
0
1
17
24
```
	
## Objašnjenje primera
U prvom primeru, ako je kontrolna samo prva tačka, gde god da strelica pogodi, dobija se $0$ poena. Ako su nam kontrolne prve dve tačke možemo "pogoditi" $(1, 2)$, i dobiti rezultat $1\cdot1+0\cdot0=1$, a ako su sve tri tačke, optimalna je tačka $(1, 1)$, gde je rezultat $1\cdot 0+0\cdot 1+2\cdot 2=4$.
	
## Ograničenja
	
- $1 \leq M \leq 10^6$.
- $|x_i|, |y_i| \leq 10^5$.
	  
Test primeri su podeljeni u šest disjunktnih grupa:
	
- U test primerima vrednim $10$ poena, $1 \leq M \leq 100$.
- U test primerima vrednim $10$ poena, $1 \leq M \leq 500$.
- U test primerima vrednim $15$ poena, $1 \leq M \leq 2000$.
- U test primerima vrednim $15$ poena, $1 \leq M \leq 2\cdot 10^5$.
- U test primerima vrednim $10$ poena, $1 \leq M \leq 10^5$ i $0 \leq x_i, y_i \leq 10$.
- U test primerima vrednim $40$ poena nema dodatnih ograničenja.
	
	
