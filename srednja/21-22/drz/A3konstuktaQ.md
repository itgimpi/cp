# A3 - Konstrukta ()

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1600ms | 256MB |

Stablo ima $n$ čvorova i $n-1$ grana. Udaljenost dva čvora je broj grana između njih. 

Može da se izabere čvor, tako da je zbir svih udaljenosti najmanji.

Ako se doda još jedna grana onda to više nije stablo ali se zbir udaljenosti smanjuje. 

Koja grana se dodaje i koji će čvor posle dodavanja da bude centralni (ne postoji manji zbir udaljenosti do njega)?





## Opis ulaza
U prvom redu je $n$, broj čvorova. U sledećih $n-1$ redova su $2$ broja, veze između čvorova.
## Opis izlaza
U prvi red ispiši brojeve čvorova koji se dodatno povezuju. U drugi odabrani čvor.
## Primer1

### Ulaz

```
5
1 2
1 3
1 4
1 5
```
Stablo:
```
    4-----------1----------5
                |\
                | \
                |  \
                |   \ 
                |    \
                |     \
                2      3
```
### Izlaz

```
2 3
1
```
## Objašnjenja primera
Pre dodavanja grane, centar je čvor 1. Rastojanja do njega su $4 \cdot 1 = 1$. Do bilo kog drugog čvora zbir rastojanja je: $1+2+2+2=7$.

U ovom slučaju se ništa ne postiže dodavanjem grane, jer zbir ne može da bude manji od 4. Tako da, grana može da se postavi npr. između čvora 2 i 3.

## Ograničenja
-   $3 \leq n \leq 2\cdot 10^5$
-   $1 \leq u \neq v \leq n$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $16$ poena: Svaki čvor je direktno povezan sa najviše 2 čvora.
-   U test primerima vrednim $13$ poena: $n \leq 100$
-   U test primerima vrednim $12$ poena: $n \leq 400$
-   U test primerima vrednim $26$ poena: $n \leq 2000$
-   U test primerima vrednim $33$ poena: Bez dodatnih ograničenja

