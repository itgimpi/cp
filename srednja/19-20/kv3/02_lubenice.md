---
hide:
  - toc
---

# 2 - Lubenice

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |


Ante, rođeni brat Miloša (iz prvog zadatka), doselio se zajedno sa svojim bratom u novi komšiluk. Za razliku od Miloša koji je odlučio da poseti komšije, Ante misli da je dobar odnos sa komšinicama mnogo značajniji za njegovo buduće postojanje. On je odredio tri omiljene komšinice (Lanu i još dve), i rešio da njima pokloni sveže lubenice. Ante ukupno ima $N$ lubenica, Lani će pokloniti $\lceil \frac{N}{p} \rceil$ lubenica, drugoj komšinici $\lceil \frac{N}{q} \rceil$ i trećoj $\lceil \frac{N}{r} \rceil$. Izraz $\lceil x \rceil$ predstavlja broj $x$ zaokružen na gore (npr. $\lceil 4.1 \rceil  = 5$, $\lceil 7 \rceil  = 7$).

Primetimo da podela koju je Ante naveo nije moguća za sve kombinacije brojeva $N, p, q, r$ (može se desiti da on treba da pokloni više lubenica komšinicama nego što ih stvarno ima). Njega zanima da za fiksne brojeve $p, q, r$ odredi koliko ima prirodnih brojeva $N$ iz nekog intervala $[L, R]$ za koje je moguća podela $N$ lubenica (tj. za koliko prirodnih brojeva $N$ iz intervala $[L, R]$ važi nejedankost $\lceil \frac{N}{p} \rceil + \lceil \frac{N}{q} \rceil + \lceil \frac{N}{r} \rceil \leq N$).  

## Opis ulaza

Prva i jedina linija ulaza sadrži redom pet brojeva $p, q, r, L, R$. 

## Opis izlaza

U jedinoj liniji izlaza ispisati za koliko različitih brojeva lubenica iz intervala $[L, R]$ je podela lubenica moguća.

## Primer 1

### Ulaz

```
2 3 7 9 14
```

### Izlaz

```
2
```

## Primer 2

### Ulaz

```
3 4 5 1 1000000000000000000
```

### Izlaz

```
999999999999999998
```

## Objašnjenje primera 1

U prvom primeru validna podela postoji ako imamo $12$ ili $14$ lubenica.

## Ograničenja

- $1 \leq p, q, r \leq 10$
- $1 \leq L\leq R \leq 10^{18}$


Test primeri su podeljeni u 3 disjunktne grupe.

- U primerima vrednim 20 poena $L, R \leq 10^5$
- U primerima vrednim 25 poena $p = 2, q = 3, r = 7$.
- U primerima vrednim 55 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Nikola Jovanović | Nikola Jovanović |




## Analiza
Primetimo da za svako $k$ i svako $N$ važi $\lceil\frac{N}{k}\rceil \geq \frac{N}{k}$, iz čega sledi nejednakost $\lceil\frac{N}{p}\rceil + \lceil\frac{N}{q}\rceil + \lceil\frac{N}{r}\rceil \geq \frac{N}{p} +\frac{N}{q}+\frac{N}{r}$. U skladu sa ovim, razdvajamo problem na tri slučaja u zavisnosti od vrednosti $p,q,r$:

**Prvi slučaj**: $\frac{N}{p} +\frac{N}{q}+\frac{N}{r}>N$ $\Leftrightarrow$ $pq+pr+qr > pqr$
- Iz gornje nejednakosti imamo $\lceil\frac{N}{p}\rceil + \lceil\frac{N}{q}\rceil + \lceil\frac{N}{r}\rceil > N$, pa uslov tražen u zadatku ne može biti ispunjen ni za jedno $N$, te je konačno rešenje $0$, nezavisno od vrednosti $L$ i $R$.

**Drugi slučaj**: $\frac{N}{p} +\frac{N}{q}+\frac{N}{r}=N$ $\Leftrightarrow$ $pq+pr+qr = pqr$
- U ovom slučaju imamo da je uslov tražen u zadatku ispunjen samo ako je $\lceil\frac{N}{p}\rceil + \lceil\frac{N}{q}\rceil + \lceil\frac{N}{r}\rceil = \frac{N}{p} +\frac{N}{q}+\frac{N}{r}$, što je moguće samo ako $p|N$ i $q|N$ i $r|N$, što je ekvivalentno tome da $d | N$, gde je $d=NZS(p,q,r)$. Dakle, treba naći broj prirodnih brojeva deljivih sa $d$ u intervalu $[L,R]$. Ovo dobijamo računanjem broja takvih brojeva u $[1,R]$ i oduzimanjem broja takvih brojeva u $[1,L-1]$:  $\frac{R}{d} - \frac{L-1}{d}$.

**Treći slučaj**: $\frac{N}{p} +\frac{N}{q}+\frac{N}{r}<N$ $\Leftrightarrow$ $pq+pr+qr < pqr$
- Poslednji slučaj je najsloženiji jer nas prvobitna nejednakost ne dovodi direktno do zaključka, tj. da li je podela moguća za neko $N$ zavisi na netrivijalan način od deljivosti sa $p,q,r$. 
- Iako nas ograničenja za $L$ i $R$ odvraćaju od brute-force rešenja (prolazak kroz sve brojeve od $L$ i $R$ i provera da li je traženi izraz tačan), često je u ovakvim situacijama, kada je potrebno pronaći šablon, dobra ideja generisanje i posmatranje vrednosti koje brute-force proizvede. Ukoliko to ovde uradimo za npr. $(p,q,r)=(2,3,7)$ (drugi podzadatak) i $(L,R)=(1,300)$ možemo primetiti da je podela moguća za svako $N \in [50, 300]$, iz čega prirodno pretpostavljamo da je moguća za svako $N \geq 50$. U ovu pretpostavku se možemo dodatno ubediti povećavanjem $R$.
- Ukoliko je ovo tačno za $(p,q,r)=(2,3,7)$, tačno je i za svako drugo $(p' \leq q' \leq r')$ koje spada u treći slučaj, jer mora da važi $p'>p, q'>q, r'>r$ (proveriti!) pa je stoga (ako je naša pretpostavka tačna) za svako  $N > 50$: $\lceil\frac{N}{p'}\rceil + \lceil\frac{N}{q'}\rceil + \lceil\frac{N}{r'}\rceil \leq \lceil\frac{N}{p}\rceil + \lceil\frac{N}{q}\rceil + \lceil\frac{N}{r}\rceil  \leq N$.
- Ovo nas dovodi do efikasnog rešenja za treći slučaj: za svako $N < 50$ u $[L,R]$ proverimo uslov "ručno", dok za $N \geq 50$ pretpostavimo da sigurno važi. Ovo se ispostavlja kao tačno, a ukoliko želimo da budemo u potpunosti sigurni moguće je tvrdnju sličnu našoj pretpostavci i malo formanije dokazati (hint: posmatrati ponašanje izraza $\lceil\frac{N}{p}\rceil + \lceil\frac{N}{q}\rceil + \lceil\frac{N}{r}\rceil$ za $nzs(p,q,r)|N$).

``` cpp title="02_lubenice.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

int k1, k2, k3;
long long l, r;

int lcm(int x, int y)
{
    return x * y / __gcd(x, y) ;
}

int main()
{
    cin>> k1 >> k2 >> k3 >> l >> r ;

    int sum = k1 * ( k2 + k3 ) + k2 * k3 ;

    if (sum > k1 * k2 * k3) return !printf("0\n") ;

    if ( sum == k1 * k2 * k3 )
    {
        long long nzs = lcm( lcm ( k1, k2 ), k3) ;
        return !printf( "%lld\n", r / nzs - ( l - 1) / nzs ) ;
    }

    long long ans = 0;
    for (long long i = l ; i<= min(l + 3000, r) ; i++)
    {
         long long val =  (i + k1 - 1)/k1 + (i + k2 - 1)/k2 + (i + k3 - 1) / k3 ;
         if (val <= i) ans++;
    }

    ans += r - min( l + 3000, r ) ;

    return !printf( "%lld\n", ans ) ;
}

```
