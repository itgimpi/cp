---
hide:
  - toc
---

# B2 - Lepa matrica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Vera je instalirala novu igricu na svom novom modernom mobilnom telefonu. U toj igrici je data matrica $A$ sa $N$ vrsta i $M$ kolona. Cilj igrice je maksimizovati lepotu matrice. Lepota matrice se definiše kao kao suma apsolutnih vrednosti razlika susednih polja matrice, pri čemu su susedna polja ona koja dele zajedničku stranicu. Preciznije, lepota matrice $A$ je

$\sum_{i=0}^{i<N-1} \sum_{j=0}^{j<M} |A[i+1][j]-A[i][j]| + \sum_{j=0}^{j<M-1} \sum_{i=0}^{i<N} |A[i][j+1]-A[i][j]|$, gde je $A[i][j]$ element u $i$-toj  vrsti i $j$-toj koloni matrice $A$.

Vera može da promeni matricu na sledeći način:

* Tako što nagne telefon na levo i time izvrši ciklično pomeranje elemenata svih vrsta matrice na levo za jedan, tj: $A[i][j]$ postaje ono što je pre pomeranja bilo $A[i][(j+1) \mod M]$ (gde je $0 \leq i < N$ i $0 \leq j < M$).
* Tako što nagne telefon na gore i time izvrši ciklično pomeranje elemenata svih kolona matrice na gore za jedan, tj: $A[i][j]$ postaje ono što je pre pomeranja bilo $A[(i+1) \mod N][j]$ (gde je $0 \leq i < N$ i $0 \leq j < M$).

Vera može primenjivati ove operacije više puta i u proizvoljnom redosledu. Pomozite joj i ispišite maksimalnu lepotu matrice koju može dobiti primenom ovih operacija.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se celi brojevi $N$ i $M$, gde je $N$ broj vrsta, a $M$ broj kolona matrice $A$. U narednih $N$ redova, nalazi se po $M$ celih brojeva, gde je $j$-ti broj u $i$-tom redu baš $A[i][j]$.

## Opis izlaza
U jedinom redu standardnog izlaza ispisati jedan broj - maksimalnu lepotu matrice koja se može dobiti.

## Ograničenja
-   $1 \leq N,M \leq 1.000$
-   $1 \leq A[i][j] \leq 10^9$, za svako $0 \leq i < N$ i $0 \leq j < M$

Test primeri su podeljeni u 5 disjunktnih grupa:

*   U test primerima vrednim $10$ poena: $N = 1$.
*   U test primerima vrednim $10$ poena: $N, M \leq 100$.
*   U test primerima vrednim $20$ poena: $N, M \leq 500$.
*   U test primerima vrednim $20$ poena: $A[i][j] \leq 2$, za svako $0 \leq i < N$ i $0 \leq j < M.$
*   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
3 3
2 1 1
1 1 1
1 1 1
```

#### Izlaz
```
4
```

#### Objašnjenje
Prvo nagnemo telefon jednom na levo i dobijemo matricu:
```
1 1 2
1 1 1
1 1 1
```
Potom nagnemo telefon dva puta na gore i dobijemo matricu:
```
1 1 1
1 1 2
1 1 1
```
Na kraju nagnemo telefon još jednom na levo i dobijemo matricu lepote 4:
```
1 1 1
1 2 1
1 1 1
```

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Aleksa Milisavljević | Dragan Urošević | Vladimir Milenković |

## Analiza
Vrste sa rednim brojevima $i$ i $i+1$ ćemo nazvati **susednim vrstama**. Osim toga ćemo i vrste sa rednim brojevima $N$ i $1$ (pretpostavimo da su vrste numerisane brojevima od 1 do $N$) smatrati susednim. Slično ćemo kolone sa rednim brojevima $j$ i $j+1$ smatrati **susednim kolonama**, a isto tako kolone sa rednim brojevima $M$ i $1$ ćemo smatrati susednim. Takođe ćemo reći da su elementi $A[i][j]$ $A[i+1][j]$  **odgovarajući elementi** u susednim vrstama. Slično ćemo elemente $A[i][j]$ $A[i][j+1]$  smatrati **odgovarajućim elementima** u susednim kolonama.

Pod ovim pretpostavkama, **lepota matrice** se može odrediti tako što se od zbirova apsolutnih vrednosti razlika odgovarajućih elmenata u susenim vrstama i odgovarajućih elemenata  u susednim kolonama oduzmu apsolutne razlike odgovarajućih elemenata u poslednjoj i prvoj vrsti i apsolutne razlike  odgovarajućih elemenata u poslednjoj i prvoj koloni. Kada se matrica rotira za $j$ kolona ulevo, onda kolone $j$ i $j+1$ postaju poslednja i prva kolona (izuzetno, ako se rotira za nula kolona, onda su kolone $1$ i $M$, prva i poslednja kolona). Slično, kada se matrica rotira za $i$ vrsta na gore, vrste $i$ i $i+1$ postaju poslednja i prva vrsta (izuzetno, ako se rotira za nula vrsta, onda su vrste $1$ i $N$, prva i poslednja vrsta).

Neka je $S$ suma svih apsolutnih razlika odgovarajućih elemenata u susednim vrstama i svih apsolunih razlika odgovarajućih elemenata u susednim kolonama.  Označimo sa $SR[i]$ sumu apsolutnih razlika odgovarajućih elemenata u vrstama $i$ i $i+1$, a sa $SC[j]$ sumu apsolutnih razlika odgovarajućih elemenata u kolonama $j$ i $j+1$. 

Tada se lepota matrice koja se dobija nakon rotacije za $j$ kolona ulevo i rotacije ѕa $i$ vrsta na gore dobija tako što se od $S$ oduzme $SR[i]$ i $SC[j]$. Lepota matrice je najveća ako se oduzimaju  sume apsolutnih razlika odgovarajućih elemenata susednih vrsta i susednih kolona za koje su te sume najmanje. Zbog toga je potrebno odrediti indekse $i$ i $j$, ѕa koje su $SR[i]$ i $SC[j]$ najmanji i te dve sume oduzeti od $S$.

Lako se utvrđuje da je složenost opisanog algoritma $N\cdot M$.

``` cpp title="02_lepa_matrica.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 1005
using namespace std;
int n,m;
long long a[maxn][maxn];
long long r[maxn];
long long c[maxn];
int main() {
    long long ans=0;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%lld",&a[i][j]);
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            r[i]=r[i]+abs(a[(i+1)%n][j]-a[i][j]);
            c[j]=c[j]+abs(a[i][(j+1)%m]-a[i][j]);
            ans=ans+abs(a[i][(j+1)%m]-a[i][j]);
            ans=ans+abs(a[(i+1)%n][j]-a[i][j]);
        }
    }
    long long mv=r[0];
    for(int i=0;i<n;i++) mv=min(mv,r[i]);
    ans-=mv;
    mv=c[0];
    for(int i=0;i<m;i++) mv=min(mv,c[i]);
    ans-=mv;
    printf("%lld",ans);
    return 0;
}

```
