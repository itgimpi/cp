---
hide:
  - toc
---

# 1 - Isplata

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |

Spremajući se za put u Egipat, Miloš je čitao o novčanom sistemu u drevnom Egiptu. Otkrio je da su postojale samo novčanice u vrednosti $d \cdot 10^k$ za za svako $d$ iz skupa $\{ 1,2,5 \}$, i svaki nenegativan ceo broj $k$, tj. novčanice u vrednosti $\{1,2,5,10,20,50,100,200,500,\ldots\}$. Razmišljajući o ovome, Miloš se zapitao koliko je najmanje novčanica potrebno da se isplati neka suma $V$?

## Opis ulaza

U prvom redu nalazi se nenegativan ceo broj $V$, suma koju je potrebno isplatiti.

## Opis izlaza

Ispisati najmanji broj novčanica, potrebnih da se isplati data suma.

## Primer 1

### Ulaz

```
42
```

### Izlaz

```
3
```

## Primer 2

### Ulaz

```
121412181214
```

### Izlaz

```
16
```

## Objašnjenje primera 1
U datom primeru, sumu možemo isplatiti koristeći $2$ novčanice vrednosti $20$ i jedne novčanice vrednosti $2$.

## Ograničenja
* $1 \leq V < 10^{18}$

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena: $V < 10$.
* U test primerima vrednim 20 poena: Broj $V$ se sastoji samo od cifara $1$, $2$ i $5$.
* U test primerima vrednim 45 poena: $V < 10^9$.
* U test primerima vrednim 15 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Aleksa Milisavljević | Nikola Jovanović | Aleksandar Zlateski |

## Analiza
Uočimo da ćemo za fiksno $k$ i skup $\{1 \cdot 10^k, 2 \cdot 10^k,  5 \cdot 10^k\}$ u optimalnom rešenju iskoristiti:
* najviše jednu novčanicu tipa $1 \cdot 10^k$ (dve $1 \cdot 10^k$ se mogu zameniti jednom $2 \cdot 10^k$);
* najviše jednu novčanicu tipa $5 \cdot 10^k$ (dve $5 \cdot 10^k$ se mogu zameniti jednom $1 \cdot 10^{k+1}$);
* najviše dve novčanice tipa $2 \cdot 10^k$ (tri $2 \cdot 10^k$ se mogu zameniti jednom $1 \cdot 10^k$ i jednom $5 \cdot 10^k$), a ako iskoristimo barem dve tada ne koristimo $1 \cdot 10^k$ (dve $2 \cdot 10^k$ i jedna $1 \cdot 10^k$ se mogu zameniti jednom  $5 \cdot 10^k$).

Odavde sledi da u optimalnom rešenju nema *prenosa*, tj. ako predstavimo $V=c_n 10^n + c_{n-1} 10^{n-1} + \dots + c_0 10^0$, novčanice tipa $d \cdot 10^k$ koristimo samo kako bismo se rešili člana $c_k 10^k$. Dakle, optimalno rešenje dobijamo prolaskom kroz $V$ cifru-po-cifru i sabiranjem minimalnog broja novčanica tipa $d \cdot 10^k$ čiji je zbir $c_k \cdot 10^k$. Na primer, za $c_k=7$ biramo skup $\{$$5 \cdot 10^{k}$, $2 \cdot 10^{k}$$\}$ što dodaje $2$ na konačan rezultat. Sve vrednosti minimalnog broja novčanica za $c_k \in \{0,\dots9\}$ se lako mogu izračunati: $[0, 1, 1, 2, 2, 1, 2, 2, 3, 3]$.

Ovaj zadatak je specijalan slučaj [*change making*](https://en.wikipedia.org/wiki/Change-making_problem) problema. Za skup novčanica dat u ovom zadatku, *greedy* pristup (ponovljeno biranje najvrednije novčanice koja nema vrednost veću od preostale sume) dao bi optimalno rešenje, ekvivalentno gore opisanom. Ipak, ovaj pristup nije optimalan za sve skupove novčanica, pa se ovaj problem u opštem slučaju rešava metodom dinamičkog programiranja.

``` cpp title="01_isplata.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;
char s[20];
int novcanica_za_cifru(int a) {
    int rt=0;
    while(a>=5) {
        a-=5;
        rt++;
    }
    while(a>=2) {
        a-=2;
        rt++;
    }
    while(a>=1) {
        a-=1;
        rt++;
    }
    return rt;
}
int main()
{
	scanf("%s",s);
	int n=strlen(s);
	int ans=0;
	for(int i=0;i<n;i++) ans+=novcanica_za_cifru(s[i]-'0');
	printf("%d",ans);
	return 0;
}

```
