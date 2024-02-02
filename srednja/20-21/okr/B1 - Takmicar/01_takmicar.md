---
hide:
  - toc
---

# B1 - Takmičar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 256MB |

Mladi Ivan je odlučio da postane ozbiljan takmičar iz programiranja i njegov plan da to ostvari se sastoji iz toga da imitira likove iz tekstova zadataka sa takmičenja. Baš zbog toga je za rođendan od roditelja tražio niz prirodnih brojeva dužine $N$, a pošto je dobar dečak i vredan učenik, dobio je baš takav niz, niz $A_1, A_2, ..., A_N$.  

Uz niz je dobio i špil od $Q$ kartica. Postoje dva tipa kartica: 

- Na prvom tipu kartice nalaze se četiri broja: $1$ $l$ $r$ $x$. Kada se kartica ovog tipa iskoristi elementi niza sa indeksima od $l$ do $r$ se promene za $x$ (ako je $x$ pozitivno onda se povećaju, ako je negativno onda se smanje), tj. element $A_l$ postaje $A_l + x$, element $A_{l+1}$ postaje $A_{l+1} + x$ i tako do $A_r$ koji postaje $A_r + x$.
- Na drugom tipu kartice nalazi se samo broj $2$. Kada se kartica ovog tipa iskoristi, Ivan zapisuje trenutni zbir svih elemenata niza na papir

Za svaku karticu, vi znate brojeve koji su zapisani na njoj.  Ivan se igra tako da iskoristi svaku karticu **tačno jednom, ali može ih iskoristiti u bilo kom redosledu**. Njegova želja je da ukupan zbir svih brojeva koji su zapisani na papir (usled korišćenja kartice drugog tipa) bude što je veći moguć. Pošto je još uvek takmičar u treningu, zamolio je vas, iskusne takmičare, da mu pomognete da to uradi.

## Opis ulaza
U prvom redu ulaza se nalazi prirodan broj $N$ -- dužina niza. 
U drugom redu se nalazi niz $N$ prirodnih brojeva $A_1, A_2, ...  ,A_N$ -- početne vrednosti niza $A$. 
U trećem redu se nalazi prirodan broj $Q$ -- broj kartica. 
U narednih $Q$ linija nalaze se opisi kartica: ukoliko red počinje sa $1$, u pitanju je kartica prvog tipa i u istom redu slede prirodni brojevi $l$, $r$ i $x$ tim redom; ukoliko red počinje sa $2$, u pitanju je kartica drugog tipa.

## Opis izlaza
Na izlaz ispisati najveći mogući zbir zapisanih brojeva. 

## Ograničenja
-   $1 \leq N,Q \leq 2\cdot10^5$
-   $1 \leq A_i \leq 1000$
- Za kartice prvog tipa važiće $1 \leq l \leq r \leq N$ i $-1000 \leq x \leq 1000$.
-  Postojaće bar jedna kartica drugog tipa.
- Moguće je da nakon korišćenja nekih kartica prvog tipa elementi niza budu negativni ili veći od $1000$.

Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $10$ poena: Za kartice prvog tipa važiće $x \geq 1$.
-   U test primerima vrednim $10$ poena: $N, Q\leq 9$.
-   U test primerima vrednim $30$ poena: $N, Q \leq 5000$.
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
5
3 2 1 3 1
3
1 2 4 2
2
1 1 3 1
```

#### Izlaz
```
19
```

#### Objašnjenje
Iskoristimo prvo karticu $1$ $2$ $4$ $2$, tada niz postaje $3$ $4$ $3$ $5$ $1$. Nakon toga iskoristimo karticu $1$ $1$ $3$ $1$, tada niz postaje $4$ $5$ $4$ $5$ $1$. Na kraju iskoristimo karticu $2$, i na papir zapisujemo zbir $4+5+4+5+1=19$.

### Primer 2
#### Ulaz
```
7
33 11 73 78 12 62 84
5
1 2 5 3
2
1 2 6 -5
2
1 1 7 1
```

#### Izlaz
```
744
```

## Napomena
* Zbog veličine brojeva, koristite 64-bitne tipove celih brojeva (npr. u C++ tip `long long`).

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Dragan Urošević | Aleksa Milojević |

## Analiza
Da bi zbir odgovora na upite bio što veći, potrebno je da suma elemenata niza bude što veća. Suma elemenata je najveća onda kada elementi niza imaju najveću moguću vrednost. Najveća moguća vrednost se dobija nakon što se primene svi upiti tipa $1$ u kojima se elementi niza uvećavaju za neku pozitivnu vrednost.
Zbog toga je potrebni prvo izvršiti upite tipa $1$ kod kojih se vrednost elemenata uvećavaju za pozitivvnu vrednost, a zatim sve upite tipa $2$ i na kraju upite tipa $1$ kod kojih se vrednosti elemenata uvećavaju za negativnu vrednost.

Ako je suma elemenata niza iznosila $S$, onda nakon primene upita $1\  l\  r\  x$ suma elemenata niza iznosi 

$$
S_n = S + (r - l + 1) \cdot x.
$$

Prema tome, potrebno je odrediti sumu svih elemenata nakon primene svih upita tipa $1$ kod kojih se neki elementi uvećavaju za neku pozitivnu vrednost (neka ta suma iznosi $S_m$) i broj upita tipa $2$ (neka je to $n_2$).
Tada će suma odgovora na upite iznoositi 

$$
n_2 \cdot S_m.
$$

Lako se pokazuje da je složenost algoritma $\Theta(n+m)$, gde je $n$ broj elemenata u nizu, $m$ ukupan broj upita. 

``` cpp title="01_takmicar.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 200010
using namespace std;
long long A[MAXN], zbir;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        zbir += A[i];
    }
    int Q; cin >> Q;
    long long cnt = 0, sum = 0;
    while(Q--) {
        int tip; cin >> tip;
        if(tip == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            if(x > 0) sum += (r-l+1)*x;
        } else {
            cnt++;
        }
    }
    cout << (zbir+sum)*cnt;
    return 0;
}

```
