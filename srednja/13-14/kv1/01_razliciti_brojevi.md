---
hide:
  - toc
---

# 1 - Različiti brojevi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Pred Zimske olimpijske igre, organizator svakodnevno meri visinu snega. Nekad i više puta dnevno. Rezultati merenja dostupni su svima. Američka reprezentacija veruje da može pomoći svojim skijašima ako detaljno analizira ove podatke. Primetili su da se visina snega s vremenom **nikako ne smanjuje**. Međutim, često im je bio potreban odgovor na pitanje: **Koliko se različitih visina pojavljuje između dva merenja** (računajući i ta merenja)? Njihovim programerima je trebalo previše vremena da odgovore na ova pitanja, pa su zamolili vas za pomoć.

## Ulaz
U prvom redu standardnog ulaza nalazi se broj $N$, broj rezultata merenja. U drugom redu nalazi se $N$ prirodnih brojeva, koji predstavljaju rezultate (visinu snega), u redosledu merenja. U trećem redu nalazi se broj $Q$, broj upita Američke reprezentacije. U sledećih $Q$ redova nalaze se dva cela broja $L$ i $R$ koji predstavljaju redne brojeve dva merenja (merenja su indeksirana brojevima od $0$ do $N-1$).

## Izlaz
Standardni izlaz sadrži $Q$ celih brojeva, svaki u novom redu, koji predstavljaju odgovore na pitanje Američke reprezentacije za data dva merenja. U $i$-tom redu nalazi se odgovor na $i$-ti upit.

## Primer 1
### Ulaz
```
10
1 2 2 2 4 4 5 6 7 7
5
0 9
1 3
1 5
7 9
4 4
```

### Izlaz
```
6
1
2
2
1
```

## Objašnjenja primera
U prvom upitu rezultati koji se pojavljuju su $1$, $2$, $4$, $5$, $6$ i $7$. U drugom to je samo $2$. Između merenja broj $1$ i broj $5$ pojavljuju se rezultati $2$ i $4$.

## Ograničenja

* $1 \leq N,Q \leq 100.000$.
* $0 \leq L \leq R \leq N-1$.
* Visina snega je veća od $0$ a manja od $10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U testovima vrednim 30 poena: $1 \leq N, Q \leq 1000$.
* U testovima vrednim 30 poena: $10 \leq N \leq 10.000$ i visina snega je manja od 500.
* U testovima vrednim 40 poena: Bez dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Baković | Marko Baković | Nepoznato | Aleksandar Ivanović |

Za svaki interval, prolaskom od levog do desnog kraja, možemo naći broj različitih brojeva koje sadrži tako što ćemo brojati samo prvo pojavljivanje svakog broja. Kako ćemo znati da je neko pojavljivanje prvo? Znamo da je niz sortiran, pa važi da je pojavljivanje broja prvo ako je taj broj ili prvi broj unutar intervala, ili je broj različit od svog prethodnika (broja levo od njega). Vremenska složenost po upitu je $O(N)$, pa je složenost ovog rešenja $O(N\cdot Q)$. Memorijska složenost je $O(N)$. Ovo rešenje donosi $30$ poena.

Neka je $cnt[k][i]$ broj pojavljivanja broja $k$ u nizu na pozicijama od $1$ do $i$. Važi sledeće:
$$
cnt[k][i] = cnt[k][i–1], \text{ako je } niz[i] \neq k
$$
$$
cnt[k][i] = cnt[k][i–1] + 1, \text{ako je } niz[i] = K
$$
Koristeći ovo, cnt možemo odrediti u složenosti $O(max\_num\cdot N)$ gde je $max\_num$ najveći broj u nizu. Za svaki interval možemo u složenosti $O(1)$ da odredimo da li se broj $K$ pojavljuje unutar intervala tako što je broj pojavljivanja broja $k$ unutar $[l, r]$ jednak $cnt[k][r] – cnt[k][l–1]$. Sada na svaki upit možemo odgovoriti prolaskom od $1$ do $max\_num$ i proverom za svaki broj da li se pojavljuje unutar intervala iz upita. Vremenska složenost ovog rešenja je $O(Q\cdot max\_num + N\cdot max\_num)$, a memorijska $O(N\cdot max\_num)$. Ovo rešenje takođe vredi $30$ poena, ali može se primeniti u kombinaciji sa prethodnim rešenjem tako što ukoliko je $max\_num \leq 500$ radimo u složenosti $O(Q\leq max\_num + N\leq max\_num)$, a inače u složenosti $O(N\cdot Q)$, i ovakva kombinacija vredi $60$ poena.

Analizirajmo sada rešenje za $100$ poena. Posmatrajmo samo prvo pojavljivanje svakog broja u nizu. Neka je $dp[i]$ broj ovih prvih pojavljivanja u nizu na pozicijama od $1$ do $i$. Broj različitih brojeva na intervalu jednak je broju prvih pojavljivanja na intervalu. Već smo rekli da je pojavljivanje broja prvo ako je taj broj ili prvi broj unutar intervala, ili je broj različit od svog prethodnika. Broj onih koji su različiti od svog prethodnika na intervalu $[l, r]$ jednak je $dp[r] – dp[l-1]$. Međutim, u slučaju da je $niz[l] = niz[l-1]$, tada rešenje treba uvećati za $1$ jer nismo računali broj sa indeksom $l$ jer je on jednak svom prethodniku, a treba ga računati zato što je prvi broj unutar intervala. Dakle, rešenje za interval $[l, r]$ je:
$$
dp[r] – dp[l-1], \text{ako je } niz[l] \neq niz[l-1]
$$
$$
dp[r] – dp[l-1] + 1, \text{ako je } niz[l] = niz[l-1]
$$
Niz $dp$ kreiramo u složenosti $O(N)$, i kada imamo taj niz, na upite odgovaramo u $O(1)$. Vremenska složenost ovog rešenja je $O(N + Q)$, a memorijska $O(N)$.

``` cpp title="01_razliciti_brojevi.cpp" linenums="1"
/*
    Marko Bakovic
    Razliciti brojevi O(Q + N)
*/

#include <cstdio>

const int maxn = 1e6 + 5;

int n, q, niz[ maxn ], broj_razlicitih[ maxn ], leva_granica, desna_granica;

int main()
{
    scanf( "%d", &n );
    for ( int i = 0; i < n; i++ ) scanf( "%d", &niz[ i ] );
    broj_razlicitih[ 0 ] = 1;
    for ( int i = 1; i < n; i++ )
    {
        if ( niz[ i ] != niz[ i - 1 ] ) broj_razlicitih[ i ] = broj_razlicitih[ i - 1 ] + 1;
        else broj_razlicitih[ i ] = broj_razlicitih[ i - 1 ];
    }
    scanf( "%d", &q );
    for ( int i = 0; i < q; i++ )
    {
        scanf( "%d %d", &leva_granica, &desna_granica );
        int resenje = broj_razlicitih[ desna_granica ];
        if ( leva_granica )
        {
            resenje -= broj_razlicitih[ leva_granica - 1 ];
            if ( niz[ leva_granica ] == niz[ leva_granica - 1 ] ) resenje++;
        }
        printf( "%d\n", resenje );
    }
    return 0;
}

```
