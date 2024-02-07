---
hide:
  - toc
---

# A1 - Dobitni listić

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 512MB |


Rzanj je gradić u Rusiji, koji je poznat po istoriji, kulturi, niskim temperaturama... i lutriji! Lutrija u Rzanju se održava izvlačenjem $N$ prirodnih brojeva, manjih od $10^{18}$. **U ovoj lutriji brojevi se mogu ponavljati, a važan je i njihov redosled.**


Aljoha, junak naše priče, korišćenjem raznih opskurnih sredstava uspeo je da dođe do nekih dodatnih informacija o narednoj dobitnoj kombinaciji. Neka su brojevi koji će biti izvučeni na lutriji $L_{i}, 1 \leq i \leq N$. **Aljoha je saznao niz koji se sastoji od $N-1$ broja, od kojih $i$-ti broj, $A_{i}$, predstavlja najveći broj koji deli i $L_{i}$ i $L_{i+1}$.**


Sada Aljoha želi da popuni listić i za to mu je potrebna pomoć. Ispišite jednu kombinaciju koja ispunjava uslove, ili $-1$, ukoliko takva kombinacija ne postoji. Primetite da kombinacija koje ispunjavaju uslove može biti više. U tom slučaju, ispišite bilo koju. Takođe primetite da su validne samo one kombinacije u kojima je svaki broj manji od $10^{18}$.


## Opis ulaza

U prvom redu nalazi se broj $N$, broj brojeva u lutriji.
U narednom redu nalazi se $N-1$ broj, koji predstavljaju dodatne informacije do kojih je došao Aljoha.

## Opis izlaza

U jedinom redu ispisati $N$ brojeva, **manjih od $10^{18}$**, koji predstavljaju neku kombinaciju, koja može biti dobitna, ili $-1$ ukoliko takva kombinacija ne postoji.

## Primer 1

### Ulaz

```
4
3 4 10
```

### Izlaz

```
3 12 20 10
```

## Primer 2

### Ulaz

```
4
3 4 6
```

### Izlaz

```
-1
```

## Objašnjenje primera
Primetimo da je najveći broj koji deli $3$ i $12$ baš $3$, najveći broj koji deli $12$ i  $20$ je baš $4$, a najveći broj koji deli $10$ i $20$ je baš $10$. U drugom primeru ne postoji kombinacija koja ispunjava uslove.

## Ograničenja
* $2 \leq N \leq 10^{5}$
* $1 \leq A_{i} < 10^9$

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 15 poena: $N = 3$.
* U test primerima vrednim 10 poena: Brojevi $A_{i}$ su prosti.
* U test primerima vrednim 10 poena: Brojevi $A_{i}$ su stepeni dvojke.
* U test primerima vrednim 25 poena: $N \leq 10^3$ i $A_{i} \leq 10^6$.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

## Napomena
Jovan Cvijić je rođen u Loznici, godinu dana pošto je izgrađena pruga između Rzanja i Moskve.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Aleksa Milisavljević | Aleksa Milisavljević | Pavle Martinović |


## Analiza

Označimo sa $nzd(a,b)$ najveći broj koji deli i $a$ i $b$, a sa $nzs(a,b)$ najmanji broj kojeg dele i $a$ i $b$. Primetimo da je jedino ograničenje na $L_{1}$ i $L_{N}$ da ih $A_{1}$ i $A_{N-1}$ dele redom. Dalje, primetimo da za svaki broj $L_{i}, 1 < i < N$ važi $A_{i-1} | L_{i}$ i $A_{i} | L_{i}$, tj. $nzs(A_{i-1},A_{i}) | L_{i}$ . Posmatrajmo niz: 

$$K_{1} = A_1, K_{2} = nzs(A_{1},A_{2}),...,K_{i}=nzs(A_{i-1},A_{i}),...,K_{N-1}=nzs(A_{N-2},A_{N-1}),K_{N}=A_{N-1}$$

Primetimo da za ovakav niz $K_{i}$ važi da $A_{i} | K_{i}$ i $A_{i} | K_{i+1}$, tj. $A_{i} | nzd(K_{i},K_{i+1})$.  Primetimo, takođe, da za svaki niz $M_{i}$ koji ispunjava ograničenja važi da: 

$$K_{i} | M_{i}, 1 \leq i \leq N$$

Zbog toga, važi da $nzd(K_{i},K_{i+1}) ∣ nzd(M_{i},M_{i+1})$, tj. $A_{i} \leq nzd(K_{i},K_{i+1}) \leq nzd(M_{i},M_{i+1})$. Dakle dovoljno je proveriti da li niz $K_{i}$ ispunjava ograničenja, tj. proveriti da li važi $A_{i} = nzd(K_{i},K_{i+1})$ za svako $i$.

``` cpp title="04_dobitni_listic.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 300000
using namespace std;
int n;
long long b[maxn];
long long a[maxn];
int main () {
    scanf("%d",&n);
    for(int i=1;i<n;i++) {
        scanf("%lld",&b[i]);
    }
    a[1]=b[1];
    a[n]=b[n-1];
    for(int i=2;i<n;i++) {
        a[i]=b[i-1]*b[i]/__gcd(b[i-1],b[i]);
    }
    for(int i=1;i<n;i++) {
        if(__gcd(a[i],a[i+1])!=b[i]) {
            printf("-1");
            return 0;
        }
    }
    for(int i=1;i<=n;i++) printf("%lld ",a[i]);
    return 0;
}

```
