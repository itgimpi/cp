---
hide:
  - toc
---

# A2 - Slepi brojevi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 128MB |

Mali Đole je sinoć sanjao dva broja: $S$ i $K$. Iznenada se probudio, i odmah zapisao dve definicije koje su mu pale na pamet:

- Slepi brojevi su oni brojevi čija je suma cifara jednaka $S$.
- Klepi par čine dva Slepa broja čiji je proizvod deljiv sa $K$.

Da bi se Đole ponovo uspavao, on želi da prebroji koliko ima Klepih parova, koje čine neka dva Slepa broja iz intervala $[A,B]$. Brzo je shvatio da ovakvih parova može imati mnogo, pa vas je zamolio za pomoć da mu brzo kažete kako bi odmoran stigao na takmičenje iz enigmatike.

## Opis ulaza

Prva linija standardnog ulaza sadrži četiri prirodna broja broj $A, B, S$ i $K$ odvojena razmakom.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati ukupan broj Klepih parova koje čine neka dva Slepa broja iz intervala $[A,B]$.

## Primer 1

### Ulaz

~~~
1 100 3 9
~~~

### Izlaz

~~~
10
~~~

## Primer 2

### Ulaz

~~~
80 120 15 6
~~~

### Izlaz

~~~
2
~~~

### Objašnjenje primera

U prvom primeru Slepi brojevi iz datog intervala su: $3,12,21$ i $30$ (svi brojevi od $1$ do $100$ čija je suma cifara $3$). Parovi Slepih brojeva čiji je proizvod deljiv sa $9$ čine Klepe brojeve, i u ovom slučaju imamo $10$ takvih parova: $(3,3), (3,12), (3,21), (3,30), (12,12), (12,21), (12,30), (21,21), (21,30), (30,30).$

U drugom primeru imamo dva Slepa broja: $87$ i $96$, i dva Klepa para: $(87,96), (96,96)$.

## Ograničenja

U svim test primerima važi: $1 \leq S \leq 100$, i $B \geq A \geq 1$, i $K \geq 1$.

Test primeri su podeljeni u $4$ disjunktne grupe:

* U test primerima vrednim 25 poena: $A,B,K \leq 10000$.
* U test primerima vrednim 30 poena: $A,B \leq 10^6$, i $K \leq 10000$.
* U test primerima vrednim 35 poena: $A,B,K \leq 10^6$.
* U test primerima vrednim 10 poena: $A,B \leq 10^{12}$, i $B-A \leq 10^6$, i $K \leq 10^6$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Vladimir Milenković | Aleksa Plavšić |

## Analiza
Primetimo da, u svim potproblemima, možemo na početku izdvojiti sve slepe brojeve - proveru da li je neki broj slep možemo uraditi u složenosti $O(\log B)$, tako da možemo izdvojiti sve takve u $\mathcal{O}((B - A)\log B)$, što je dovoljno brzo.

## Potproblem 1
Primetimo da možemo da probamo sve parove slepih brojeva (ima ih najviše $(B - A) ^ 2$ (gruba granica)), i videti koji od tih parova je klep, proverom da li $K$ deli njihov proizvod, u složenosti $\mathcal{O}((B - A) ^ 2)$

## Potproblem 2
Zapravo, nas samo interesuju ostaci svih slepih brojeva pri deljenju sa  $K$ - samo od ostataka pri deljenju dva broja nekim brojem zavisi i ostatak proizvoda. Dakle, možemo imati brojač koliko postoji slepih brojeva sa svakim ostatkom, i u $\mathcal{O}(K^2)$ izračunati koliko ima klepih parova.

## Potproblemi 3 i 4

Neka je $z$ broj slepih brojeva deljivih sa  $K$. Posmatrajmo sve ostale slepe brojeve. Ukoliko posmatramo neki broj $x$, neka je $t = gcd(x, k)$. Par  $(x, y)$ će biti klep ukoliko važi $\frac{k}{t} \mid y$ - dakle, kada tražimo sve brojeve koji formiraju klep par sa brojem $x$, treba nam broj brojeva deljivih sa nekim brojem. To možemo lako uraditi prolaskom kroz niz slepih brojeva (tj. njihovih ostataka pri deljenju sa $K$) - kada naiđemo na broj $x$, dodamo $\mathrm{count}[K / gcd(x, K)]$ na rešenje, i uvećamo $\mathrm{count}$ svakog delioca broja $x$ za 1. Ovo rešenje radi u složenosti $\mathcal{O}(\mathrm{brSlepih} \cdot \sqrt{K})$, što je sigurno dovoljno brzo, jer ne postoji ulaz za koji je broj slepih brojeva veći od 50000. Na ovo dobijeno rešenje treba dodati $z \choose 2$, kao i $z \cdot (\mathrm{brSlepih} - z)$.

``` cpp title="05_slepi_brojevi.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;

#define MAXKLEPI 1000555
#define MAXK 1000555

long long zbir_cifara(long long x) {
    if (x == 0) return 0;
    return (x%10) + zbir_cifara(x/10);
}

long long nzd(long long a, long long b) {
    return b ? nzd(b, a%b) : a;
}

long long ostaci[MAXK];
long long solve(long long a, long long b, long long s, long long k) {

    for(long long i=0; i<=k; i++) ostaci[i] = 0;

    for(long long i=a; i<=b; i++) {
        if (zbir_cifara(i) == s) {
            ostaci[i%k]++;
        }
    }

    long long res = (ostaci[0]*(ostaci[0]+1))/2;
    for(long long i=1; i<k; i++) {

        res += ostaci[i]*ostaci[0];

        long long t = k / nzd(i,k);
        long long j;
        for(j=t; j<i; j+=t) {
            res += ostaci[i]*ostaci[j];
        }
        if (j==i) {
            res += (ostaci[i]*(ostaci[i]+1))/2;
        }
    }

    return res;
}
int main() {

    long long a,b,s,k;
    scanf("%lld%lld%lld%lld", &a, &b, &s, &k);
    printf("%lld\n", solve(a,b,s,k));

    return 0;
}

```
