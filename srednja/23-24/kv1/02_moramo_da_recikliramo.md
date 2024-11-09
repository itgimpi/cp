---
hide:
  - toc
---

# 2 - Moramo da recikliramo

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |

Moramo da recikliramo!

Poznato je da su članovi komisije ekološki osvešćeni. Stoga, svaki od $N$ članova komisije ima svoj kontejner za reciklažu papira, koji je krajnje odredište za sve takmičarske žalbe. Ti kontejneri su poređani u niz. $i$-ti od njih ima kapacitet $C_i$, a u njemu se već nalazi $A_i$ žalbi. 

Rok za žalbe traje $Q$ dana. $j$-tog od tih $Q$ dana pristigne $x_j$ žalbi, <s>(i te žalbe odbija)</s> na te žalbe odgovara član $k_j$. Kada $k_j$ <s>(odbije sve žalbe)</s> odgovori na sve žalbe, on ih odnosi do svog kontejnera i ubacuje u njega (tj. povećava $A_{k_j}$ za $x_j$). Međutim, ukoliko se dodavanjem $x_j$ žalbi kontejner $k_j$ napuni, višak žalbi se prebacuje u naredni kontejner (događaj komisiji poznat kao prelivanje) i tako sve do kraja niza. Formalno, ukoliko je $A_{k_j} + x_j > C_{k_j}$, $A_{k_j}$ postaje $C_{k_j}$ a $A_{k_j} + x_j - C_{k_j}$ žalbi koje su višak se dodaje u kontajner $k_j + 1$. Ukoliko se i poslednji kontejner napuni, žalbe koje su višak jednostavno padnu na trotoar pored njega (ekološka osvešćenost komisije ima svoje granice).


Nakon kraja roka za žalbe, komisija dodeljuje nagrade svojim članovima na osnovu toga koliko je pun njihov kontejner. Kako je komisija prezauzeta <s>(odbijanjem žalbi)</s> odgovaranjem na žalbe, pomozite joj i ispišite koliko žalbi ima u svakom kontejneru nakon svih $Q$ promena.

## Opis ulaza
U prvom redu standardnog ulaza, dat je ceo broj $N$. U drugom redu, dato je $N$ celih brojeva, $i$-ti od njih predstalja $A_i$. U trećem redu, dato je $N$ celih brojeva, a $i$-ti od njih predstavlja $C_i$. 

U narednom redu, dat je jedan ceo broj $Q$. U $j$-tom od narednih $Q$ redova, data su po dva cela broja $k_j$ i $x_j$, koji označavaju promenu $A_{k_j} = A_{k_j} + x_j$.

## Opis izlaza
U jedinom redu standardnog izlaza ispisati vrednosti niza nakon svih operacija.

## Primer 1

### Ulaz

```
4
1 3 2 3
5 4 5 4
2
3 2
2 4
```

### Izlaz

```
1 4 5 4
```
### Objašnjenje
Komisija ima $4$ člana. 

Kontejner prvog člana ima $1$ žalbu i kapacitet $5$.
Kontejner drugog člana ima $3$ žalbe i kapacitet $4$.
Kontejner trećeg člana ima $2$ žalbe i kapacitet $5$.
Kontejner četvrtog člana ima $3$ žalbe i kapacitet $4$.

Rok za žalbe traje $2$ dana.

Prvog dana stižu $2$ žalbe i za njih je zadužen treći član komisije. Kako njegov kontejner ima $2$ žalbe, a kapacitet $5$, nakon obe žalbe staju u kontejner i nakon ovog dana u njemu se nalazi $4$ žalbe.



Drugog dana stižu $4$ žalbe i za njih je zadužen drugi član komisije. Kako njegov kontejner ima $3$ žalbe a kapacitet $4$, u njega stane jedna žalba a preostale $3$ se prebacuju u treći kontejner. Međutim, nakon prvog dana, ovaj kontejner ima $4$ žalbe, a kapacitet $5$, pa i u njega staje samo jedna žalba. Preostale $2$ se prebacuju u četvrti kontejner. U njemu se nalaze $3$ žalbe i ima kapacitet $4$, pa i u njega staje samo jedna žalba. Kako je ovo poslednji kontejner u nizu, poslednja žalba neće biti ubačena ni u jedan kontejner.



## Ograničenja
* $1 \leq N, Q \leq 200.000$
* $0 \leq A_i \leq C_i \leq 10^9$ za $1 \leq i \leq N$
* U svih $Q$ upita važi $1 \leq k_j \leq N$ i $0 \leq x_j \leq 10^9$ (takmičari su nemilosrdni u svom slanju žalbi).

Test primeri su podeljeni u četiri disjunktne grupe:

* U testovima vrednim 30 poena: $Q = 1$.
* U testovima vrednim 30 poena: $N, Q \leq 5.000$.
* U testovima vrednim 15 poena: Za sve $1 \leq i \leq N$ važi $C_i \leq 10$.
* U testovima vrednim 25 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Igor Pavlović | Aleksandar Višnjić | Aleksandar Višnjić |

## Prva dva podzadatka
Izvršavamo direktnu simulaciju svih upita. Neka su $k$ i $x$ trenutni parametri upita. Ukoliko je $A_k + x \leq C_k$, tada jednostavno dodajemo $x$ na $A_k$ i završavamo upit. U suprotnom, $x$ smanjujemo za $C_k-A_k$, a na vrednost $A_k$ upisujemo $C_k$. Potom povećavamo $k$ za $1$ i nastavljamo izvršavanje upita sa novim vrednostima. Ukoliko izađemo iz niza, svakako prekidamo izvršavanje upita.

Vremenska složenost je $O(QN)$, jer se može desiti da prilikom izvršavanja upita prođemo kroz celu dužinu niza.


## Glavno rešenje
Primetimo da redosled izvršavanja upita nije bitan. To znači da možemo prvo učitati sve upite, a potom ih odjednom sve izvršiti. Tačnije, za svaki upit sa parametrima $k$ i $x$ najpre dodamo $x$ na $A_k$ bez vođenja računa o $C_k$. 

Kada to uradimo za svaki upit, dovoljno je proći jednom po celom nizu sleva nadesno i ažurirati vrednosti $A_k$. Za trenutni indeks $k$, ako je $A_k> C_k$,Wdodajemo $A_k-C_k$ na $A_{k+1}$, a zatim na vrednost $A_k$ upisujemo $C_k$. U suprotnom, ne radimo ništa. Napomenimo da ako je $k= $ (krajwniza), nije potrebno ažurirati[$A_{+1}$.

Složenost prolaska po svim upitima je $O(Q)$, dok je složenost jednog prolaska po celom nizu $O(hN)$ Ukupna složenost je $O(N+Qi.$

``` cpp title="02_moramo_da_recikliramo.cpp" linenums="1"
#include <bits/stdc++.h>
#define maxn 2000050
using namespace std;
int n;
int q;
long long a[maxn];
long long c[maxn];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++) {
        scanf("%lld",&c[i]);
    }
    scanf("%d",&q);
    while(q--) {
        int i;
        long long x;
        scanf("%d %lld",&i,&x);
        a[i]+=x;
    }
    for(int i=1;i<=n;i++) {
        if(a[i]>c[i]) {
            a[i+1]+=(a[i]-c[i]);
            a[i]=c[i];
        }
        printf("%lld ",a[i]);
    }
    return 0;
}

```
