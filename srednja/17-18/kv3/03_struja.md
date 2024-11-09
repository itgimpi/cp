---
hide:
  - toc
---

# 3 - Struja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |

Nakon rasprave sa časa filozofije, malom Stojanu je pala na pamet nova poslovna ideja -- odlučio je da se bavi kupovinom i prodajom struje. Na osnovu izgubljenog Teslinog izuma je napravio bateriju beskonačnog kapaciteta, tako da sada može da kupuje struju danima kada je jeftina i prodaje je kada je skupa.

Pomoću vremenske mašine (takođe Teslinog izuma), Stojan je saznao kolika će biti cena struje svakog od narednih $N$ dana ($i$-tog dana će kilovat-čas koštati $C_i$ dinara). Na početku mu je na raspolaganju $M$ dinara i prazna baterija. Svakog dana on može da kupi koliko god želi struje (dok god ima novca da je plati) ili proda koliko god želi (dok god ima dovoljno struje u bateriji). Količine kupljene i prodate struje ne moraju biti celi brojevi.

Pomozite Stojanu da odluči kako će trgovati strujom, tako da mu na kraju poslednjeg dana ostane što više novca.

## Opis ulaza
U prvoj liniji standardnog ulaza nalaze se dva cela broja, $N$ i $M$ - broj dana za koje Stojan zna cenu struje i svota novca koja mu jemna raspolaganju na početku.

U drugoj (poslednjoj) liniji nalazi se $N$ brojeva $C_1, C_2, \ldots,C_N$, gde je $C_i$ cena jednog kilovat-časa $i$-tog dana.

## Opis izlaza
Na prvu liniju standardnog izlaza ispisati maksimalnu sumu novca koju Stojan može imati na kraju poslednjeg dana. Garantuje se da ova vrednost neće biti veća od $10^{10}$.

## Primer 1
### Ulaz
```
4 10
4 10 5 20
```

### Izlaz
```
100
```

## Primer 2
### Ulaz
```
3 21
10 8 3
```

### Izlaz
```
21
```

## Objašnjenje primera
U prvom primeru, Stojan može da kupi $2.5$ kilovat-časova prvog dana, i proda ih drugog dana za $25$ dinara. Trećeg dana može da kupi pet kilovat-časova i proda ih četvrtog za $100$ dinara, što je i optimalno rešenje.

U drugom primeru, najbolje je da uopšte ne kupuje struju i sačuva $21$ dinar sa kojim je počeo.

## Ograničenja

* $1 \leq M, C_i \leq 10^6$.

Test primeri su podeljeni u tri disjunktne grupe:

* U 20% primera važi $1 \leq N \leq 20$.
* U 30% primera važi $1 \leq N \leq 3000$.
* U 50% primera važi $1 \leq N \leq 10^6$.

## Napomena

Ako je vaš program ispisao broj $a$, a rešenje komisije je realan broj $b$, vaše rešenje se prihvata kao tačno pod uslovom da važi $\frac{|a-b|}{b} \leq 10^{-6}$ ili važi $|a-b| \leq 10^{-6}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Jovanović | Dimitrije Erdeljan | Dimitrije Erdeljan | Nikola Jovanović |

Ako optimalno trgujemo strujom, sigurno ćemo svakog dana ili "čekati" (bez kupovine i prodaje), ili potrošiti sav novac na struju, ili prodati svu struju koju imamo. Ovo tvrđenje neće biti formalno dokazano ovde, ali ideja iza njega je da ako "razdvojimo" novac (ili struju) i potrošimo samo deo, potrošen i sačuvan deo se mogu posmatrati nezavisno. Ako potrošen deo novca donosi bolju zaradu od nepotrošenog, bolje je da potrošimo sve (i obrnuto).

Sada je potrebno samo odabrati dane kada ćemo kupovati i prodavati struju. Optimalan izbor je da kupujemo u lokalnim minimumima cene, odnosno danima kada je struja jeftinija nego što je bila juče i nego što će biti sutra, i da prodajemo u lokalnim maksimumima (kad je skuplja od susednih dana). Da bismo dokazali da je ovo optimalno, posmatrajmo bilo koji drugi izbor dana. Tada sigurno možemo "pomeriti" onu kupovinu (ili prodaju) koja nije lokalni minimum (maksimum) na "susedni" dan kada je cena povoljnija i zaraditi više.

Lokalne minimume i maksimume možemo naći u $\mathcal{O}(N)$ (za svaki dan gledamo samo dva suseda), tako da se ceo zadatak može rešiti u $\mathcal{O}(N)$. Obratite pažnju na prvi i poslednji dan -- pošto imaju samo jednog suseda, možemo ih ili posmatrati kao specijalne slučajeve, ili dodati "veštačke" elemente za dane $0$ i $N+1$, sa cenama $\infty$ i $-\infty$.

Nešto jednostavnije rešenje za implementaciju je sledeće: za svaki dan možemo odlučiti da li ćemo tog dana kupiti struju i odmah je prodati sledećeg dana. U ovom slučaju dozvoljavamo da isti dan prodamo struju i opet je kupimo po istoj ceni (što je isto kao da ne uradimo ništa). Jasno je da ćemo u ovom slučaju kupovati onih dana kada je cena manja nego sledećeg, tako da možemo izbeći "pamćenje" minimuma i maksimuma.

``` cpp title="03_struja.cpp" linenums="1"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    int n;
    double money;
    scanf("%d %lf", &n, &money);

    double prev = 1e10;
    while(n--)
    {
	double curr;
	scanf("%lf", &curr);
	if(curr > prev)
	    money *= curr / prev;
	prev = curr;
    }

    printf("%.6f\n", money);
    return 0;
}

```
