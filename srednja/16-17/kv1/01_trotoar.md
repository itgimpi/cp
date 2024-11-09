---
hide:
  - toc
---

# 1 - Trotoar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Milutin mnogo voli da ide u školu, tj. da pešači od kuće do škole. Njegov omiljeni predmet je matematika, omiljeni brojevi - celi brojevi, a omiljene operacije su mu **sabiranje i množenje** jer ostale ne zna. 

Jednog dana, na putu do škole, naišao je na tri cela broja $a$, $b$ i $c$, napisana jedan za drugim kredom na trotoaru. Tada mu je sinula strašna ideja: **dopisaće neku od njemu omiljenih operacija između prvog i drugog kao i između drugog i trećeg broja tako da rezultat bude najmanji mogući broj**; zatim će pobeći sa lica mesta. Odredite koji je to najmanji mogući broj uzimajući u obzir da Milutin nije mogao da menja redosled brojeva niti da dopisuje zagrade, ali da zna o prioritetu operacija.

## Opis ulaza
U prvom i jedinom redu standardnog ulaza nalaze se tri cela broja $a$, $b$ i $c$, razdvojena razmacima i u redosledu kojim su napisani na trotoaru.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan ceo broj - traženi najmanji mogući broj koji može dobiti Milutin.

## Primer 1
### Ulaz
```
1 2 1
```

### Izlaz
```
2
```

## Primer 2
### Ulaz
```
-2 5 -7
```

### Izlaz
```
-37
```

## Objašnjenje primera
U prvom primeru najmanji broj dobijamo dopisivanjem dve operacije množenja: $1 \cdot 2 \cdot 1 = 2$, dok je za drugi primer potrebno prvo dopisati sabiranje pa množenje : $(-2) + 5 \cdot (-7) = -37$.

## Ograničenja
Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima koji vrede $40$ poena važiće $1 < a, b, c < 100$.
* U test primerima koji vrede $60$ poena važiće $-1000 < a, b, c < 1000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Nikola Jovanović |

## Glavno rešenje

Ovo je najlakši zadatak sa Kvalifikacija čije je rešenje pravolinijsko i složenosti $O(1)$. Potrebno i dovoljno je uočiti da postoje samo $4$ načina na koja se mogu postaviti operacije pa je potrebno vratiti samo $\min\{ a + b + c, a + b \cdot c, a \cdot b + c, a \cdot b \cdot c \}$. Ograničenja su takva da rešenje staje u $32$-bitni ceo broj. Napomenimo da nije lako odraditi analizu slučajeva na osnovu broja pozitivnih/negativnih brojeva među $a$, $b$, $c$; između ostalog, problem prave specijalni slučajevi kada su neki od njih $0$ ili $\pm 1$ (npr. nije uvek optimalno koristiti samo sabiranje ako su svi brojevi pozitivni).

Dodatno, za prvi podzadatak je rešenje uvek $a + b + c$ jer za sve realne (a samim tim i cele) brojeve $x, y \geq 2$ važi $(x - 1)(y - 1) \geq (2 - 1)(2 - 1) = 1$ što je ekvivalento sa $x + y \leq xy$ što znači da se uvek isplati da vršimo sabiranje umesto množenja.

``` cpp title="01_trotoar.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

int a, b, c, sol;

int main()
{
	scanf("%d%d%d", &a, &b, &c);

	sol = 1000000000;
	if (a + b + c < sol)
		sol = a + b + c;
	if (a + b * c < sol)
		sol = a + b * c;
	if (a * b + c < sol)
		sol = a * b + c;
	if (a * b * c < sol)
		sol = a * b * c;

	printf("%d\n", sol);
	return 0;
}

```
