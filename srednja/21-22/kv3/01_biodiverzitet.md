---
hide:
  - toc
---

# 1 - Biodiverzitet

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |


Kao što već znate, zaštita životne sredine i biodiverziteta jako su važni. Zato ste unajmljeni da pomognete sa projektom procene biodiverziteta u Srbiji.

Životinjske vrste koje žive ili su živele u Srbiji indeksirane su brojevima $0, 1, 2, ...$. Indeksi su dodeljeni tako da biološki predak vrste sa indeksom $i$ ima indeks $\lfloor i/K\rfloor$, gde je $K$ unapred fiksiran prirodan broj. Ovde $\lfloor i/K\rfloor$ označava rezultat celobrojnog deljenja broja $i$ sa $K$.

Vi treba da analizirate biodiverzitet jednog područja. Zato vam je dat skup vrsta koje trenutno obitavaju na tom prostoru. Vaš zadatak je da odredite broj različitih bioloških predaka vrsta koje trenutno žive na ovom području.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva cela broja $N$ i $K$ - broj vrsta koje trenutno žive na datom području i broj koji određuje kako izračunati indeks biološkog pretka.

U drugom redu standardnog ulaza nalazi se niz celih brojeva $i_1,  i_2, \ldots, i_N$ dužine $N$, gde $i_k$ koji predstavljaju indekse vrsta koje trenutno žive na datom području. 

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati ceo broj koji predstavlja broj različitih bioloških predaka vrsta koje trenutno žive na datom području. 

## Primer 
### Ulaz
```
5 4
10 20 15 11 30
```

### Izlaz
```
4
```

### Objašnjenje
Preci datih vrsti su redom vrste sa indeksom 2, 5, 3, 2, 7. Dakle, imamo četiri različita pretka.


## Ograničenja

- $1 \leq N \leq 10^4$
- $0 \leq i_k \leq 10^9$, za $1 \leq k \leq N$
- $1 \leq K \leq 10^9$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 20 poena važi $N \leq 10, i_k\leq 100$.
- U testovima vrednim 10 poena važi $K=1, i_k\leq 100$.
- U testovima vrednim 20 poena važi $i_k\leq 10^6$
- U testovima vrednim 50 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Aleksa Milojević | Vladimir Milovanović | Vladimir Milovanović |

## Glavno rešenje
Kako je cilj odrediti broj različitih bioloških predaka vrsta koje trenutno žive, a budući da su u zadatku dati indeksi vrsta koje trenutno žive, najpre je potrebno pristupiti izračunavanju indeksa bioloških predaka. To se čini tako što se indeks vrste $i$ celobrojno podeli sa $K$ i to za sve indekse $i_1, i_2, \ldots, i_N$ u zadatom nizu. Time se dobija novi niz koji zapravo predstavlja niz bioloških predaka. Treba primetiti da se u opštem slučaju vrednosti unutar niza biloških predaka mogu ponavljati. Najzad da bi se odredio broj različitih predaka potrebno je prebrojati jedinstvene članove niza koji sadrži i duplikate. Postoji više načina na koji je moguće izračunati broj jedinstvenih članova niza, a jedan od njih je da se članovi niza bioloških predaka sortiraju i onda u jednom prolazu kroz niz izbroje različite vrednosti.

U rešenju, pored operacija prolaza kroz niz u kojima se izvršava celobrojno deljenje ili prebrajanje jedinstvenih članova, a koje su linearne složenosti $\mathcal{O}(N)$, takođe imamo i operaciju sortiranja koja je dominantne složenosti. Koristeći se efikasnim algoritmima niz je moguće sortirati u loglinearnoj vremenskoj složenosti $\mathcal{O}(N\log N)$, iako je za maksimalan broj poena to bilo dovoljno učiniti i u kvadratnoj, odnosno $\mathcal{O}(N^2)$ složenosti.

``` cpp title="01_biodiverzitet.cpp" linenums="1"
n, k = map(int, input().split())
niz = list(map(int, input().split()))
print(len(set(map(lambda x: x//k, niz))))

```
