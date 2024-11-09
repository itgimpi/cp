---
hide:
  - toc
---

# 2 - Polica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Mika je odlučio da malo preuredi knjige na svojoj (veoma velikoj) polici, ali da se ne bi previše umorio, planira da zameni mesta **tačno dve** knjige. Svaka knjiga je obeležena jednom cifrom, i Mika definiše **lepotu** rasporeda knjiga kao broj koji se dobija kada se ove cifre pročitaju redom. Pomozite Miki da odabere dve knjige koje će zameniti, tako da lepota rasporeda nakon toga bude što veća.

## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se jedan broj, $N$: broj knjiga na polici. U drugom redu nalazi se $N$ brojeva, $A_1, A_2, \dots, A_N$, gde $A_i$ predstavlja cifru napisanu na $i$-toj knjizi.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati $N$ razmakom razdvojenih brojeva: cifre napisane na knjigama na polici, nakon što su dve knjige zamenile mesta tako da se dobije raspored najveće moguće lepote.

## Primer 1

### Ulaz

```
3
8 2 5
```

### Izlaz

```
8 5 2
```

## Primer 2

### Ulaz

```
2
6 3
```

### Izlaz

```
3 6
```

## Ograničenja

- Za sve $i$, $0 \leq A_i \leq 9$.
- $A_1 \neq 0$.
- Barem dve knjige nisu obeležene cifrom 0.

Test primeri su podeljeni u pet disjunktnih grupa:

- U test primerima vrednim $10$ poena, $N = 2$.
- U test primerima vrednim $30$ poena, $N \leq 8$.
- U test primerima vrednim $20$ poena, lepota početnog rasporeda na
  polici je najviše $4 \cdot 10^{18}$.
- U test primerima vrednim $20$ poena, $N \leq 1000$.
- U test primerima vrednim $20$ poena, $N \leq 10^6$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Dimitrije Erdeljan | Dimitrije Erdeljan | Marko Savić |


Da bi raspored dobijen zamenom dve cifre imao najveću moguću lepotu, želimo da prva cifra bude najveća moguća, pa ako iza $A_1$ postoji neka veća vrednost, zamenićemo je sa onom koja je:

* najveća, i ako postoji nekoliko istih
* poslednjom takvom (da bi stavili manju cifru $A_1$ na mesto sa što manjom "težinom").

Ukoliko ovakva cifra ne postoji, odnosno $A_1$ je veća ili jednaka od svih vrednosti desno od nje, isti proces probamo za sledeću cifru $A_2$ (gde kao kandidate za zamenu gledamo samo one desno od $A_2$), i tako dalje dok ne nađemo par koji se može zameniti.

Ukoliko dođemo do kraja broja i nismo ništa zamenili, cifre u početnom rasporedu su opadajuće, tako da nije moguće povećati lepotu rasporeda. U ovom slučaju nam je cilj da je smanjimo što manje (jer moramo napraviti neku zamenu). Ukoliko postoje dve iste cifre, zamenićemo njih da bi lepota ostala ista. U suprotnom, optimalno rešenje je da zamenimo poslednje dve cifre.

"Naivno" rešenje zadatka koje za svako $A_i$ prolazi kroz sve cifre desno od nje ima vremensku složenost $O(N^2)$, tako da se neće izvršiti u datom ograničenju za poslednji podzadatak. Da bi izbegli ovaj korak, na početku programa možemo pronaći poslednje pojavljivanje svake cifre i sačuvati to u pomoćnom nizu, što se može iskoristiti da za svako $A_i$ nađemo optimalnu zamenu u konstantnom vremenu, i samim tim daje ukupnu vremensku složenost $O(N)$.

``` cpp title="02_polica.cpp" linenums="1"
#include <cstdio>
#include <iostream>

const int N = 1000005;
int a[N], n;
int last[10];

void print_sol(int x, int y)
{
    std::swap(a[x], a[y]);
    for(int i = 0; i < n; i++)
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for(int i = 0; i < 10; i++)
        last[i] = -1;
    for(int i = 0; i < n; i++)
        last[a[i]] = i;

    // Povecan broj
    for(int i = 0; i < n; i++)
        for(int d = 9; d > a[i]; d--)
            if(last[d] > i)
            {
                print_sol(i, last[d]);
                return 0;
            }

    // Ostaje isti
    for(int i = 0; i < n; i++)
        if(last[a[i]] > i)
        {
            print_sol(i, last[a[i]]);
            return 0;
        }

    // Moramo da smanjimo
    print_sol(n - 1, n - 2);
    return 0;
}

```
