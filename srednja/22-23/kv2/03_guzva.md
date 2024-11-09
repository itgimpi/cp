---
hide:
  - toc
---

# 3 - Gužva

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 3000ms | 256MB |

Janko se sprema za odlazak na finale svetskog prvenstva u fudbalu 2022. godine. Međutim, kako su svi navijači pohrlili na utakmicu, u Dohi su velike gužve. Da stvari budu gore, Jankov hotel je na suprotnom kraju grada u odnosu na stadion. 

Poznato je da Doha izgleda kao matrica dimenzija $N \times M$. Polje $(i,j)$ označava polje u $i$-tom redu i $j$-toj koloni. Jankov hotel se nalazi na polju $(1,1)$, dok se stadion nalazi na polju $(N, M)$. Na svakom polju matrice (uključujući i polja na kojem su hotel i stadion) se nalazi neka grupa navijača - na polju $(i,j)$ ima tačno $a_{i,j}$ navijača. 

Janko sa polja $(i,j)$ isključivo može da ode na polje $(i+1,j)$ ili na polje $(i,j+1)$ (ukoliko je odgovarajuće polje na koje bi došao unutar matrice). Pošto Janko ne voli gužve, odlučio je da svoj put isplanira tako da na njemu susretne najmanji broj navijača (gde je broj navijača koje je sreo suma svih $a_{i,j}$ po poljima kroz koja je prošao na putu do stadiona, uključujući i polja hotela i stadiona).  

Čim je Janko napravio plan, čuo je na vestima da će **tačno jedno polje** biti blokirano za javnost, te on neće moći da prođe kroz njega na putu do stadiona. Janko nažalost nije siguran o kojem polju je reč, te vas moli da odgovorite na $Q$ različitih scenarija. U $i$-tom scenariju, Janko želi da zna koliko će navijača morati da sretne, ako polje $(x_i,y_i)$ bude blokirano.

## Opis ulaza
U prvom redu standardnog ulaza, nalaze se dva cela broja, $N$ i $M$, koji predstavljaju dimenzije Dohe.

Linija $i$ od narednih $N$ linija sadrži $M$ celih brojeva, od kojih $j$-ti predstavlja $a_{i,j}$ - broj navijača na polju $(i,j)$.

Naredna linija sadrži jedan ceo broj, $Q$, koji predstavlja broj različitih scenarija koje Janko razmatra. 

Narednih $Q$ linija sadrže po dva broja, $x_i$ i $y_i$, koji opisuju polje koje je blokirano u $i$-tom scenariju.

## Opis izlaza
Na standardni izlaz ispisati $Q$ redova, u $i$-tom od njih potrebno je ispisati jedan ceo broj, koji predstavlja minimalan broj navijača koje će Janko sresti na putu do stadiona, ukoliko bude blokirano polje $(x_i,y_i)$.

## Primer 1
### Ulaz
```
3 4
1 2 3 4
5 6 7 8
9 10 11 12
2
1 2
2 4
```

### Izlaz
```
39
36
```

## Objašnjenje primera

- prvi scenario: Ukoliko je blokirano polje $(1,2)$, optimalan put za Janka je $(1,1) \rightarrow (2,1) \rightarrow (2,2) \rightarrow (2,3) \rightarrow (2,4) \rightarrow (3,4)$. Na tom putu, on će ukupno sresti $39$ navijača.
- drugi scenario: Ukoliko je blokirano polje $(2,4)$, optimalan put za Janka je $(1,1) \rightarrow (1,2) \rightarrow (1,3) \rightarrow (2,3) \rightarrow (3,3) \rightarrow (3,4)$. Na tom putu, on će ukupno sresti $36$ navijača.


## Ograničenja

- $2 \leq N, M$.
- $4 \leq N \cdot M \leq 10^6$.
- $1 \leq Q \leq 5 \cdot 10^5$.
- $1 \leq a_{i,j} \leq 10^9$.
- $1 \leq x_i \leq N$.
- $1 \leq y_i \leq M$.
- Garantuje se da hotel i stadion nikada neće biti blokirani za javnost i da će Janko uvek moći da stigne od hotela do stadiona.

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 15 poena: $N = 2$.
- U testovima vrednim 10 poena: $Q \leq 100$, $N, M \leq 7$.
- U testovima vrednim 15 poena: $Q \leq 2000$, $N \cdot M \leq 2000$.
- U testovima vrednim 20 poena: $Q \leq 10^4$.
- U testovima vrednim 40 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević i Mladen Puzić | Aleksa Milisavljević | Mladen Puzić | Dragan Urošević |

Dalje u rešenjima ćemo reći da se krećemo *na dole* ukoliko se pomeramo sa polja $(i, j)$ na polje $(i+1, j)$, u suprotnom se krećemo *udesno*.

## Rešenje kada $N = 2$
Na tačno jednoj poziciji ćemo se pomeriti na dole, svi ostali potezi biće udesno. Označimo sa $d_i$ broj navijača koje sretnemo ukoliko se u koloni $i$ pomerimo na dole. Ovaj niz možemo izračunati koristeći prefiksni zbir nad gornjim redom i sufiksni zbir nad donjim redom.

Ukoliko je blokirano neko polje u prvom redu, npr. $(1, i)$, onda se moramo pomeriti na dole pre $i$-te kolone, pa je rešenje $\min(d_1, d_2, \ldots d_{i-1})$. Ukoliko je blokirano neko polje u drugom redu, npr. $(2, j)$, onda se moramo pomeriti na dole posle $i$-te kolone, pa je rešenje $\min(d_{i+1}, d_{i+2}, d_M)$.

Vremenska složenost je $O(M+Q)$, a memorijska $O(M)$.

## Rešenje kada $Q \leq 100$, $N, M \leq 7$
Rešenje možemo dobiti *brute force* metodom, odnosno isprobavanjem svih mogućih puteva od prvog do poslednjeg polja, za svako blokirano polje. Takvih puteva postoji ${N+M-2 \choose N-1}$ (imamo ukupno $N+M-2$ koraka, od kojih biramo $N-1$ da budu usmereni na dole). Sve puteve možemo proveriti rekurzijom. 

Vremenska složenost je $O(Q\cdot{N+M-2 \choose N-1})$, a memorijska $O(NM)$.

## Rešenje kada $Q \leq 2000$, $N \cdot M \leq 2000$
Za svako blokirano polje, koristićemo dinamičko programiranje - izračunaćemo $dp_{i, j}$, najmanji broj navijača koje moramo da sretnemo na putu od $(1, 1)$ do $(i, j)$, ako ne posetimo trenutno blokirano polje. Jasno je da važi $dp_{1, 1} = a_{1, 1}$ i $dp_{i, j} = dp_{i-1, j} + dp_{i, j-1}$, s tim što prilikom računanja uvek preskačemo polja koja su van matrice i trenutno blokirano polje. Rešenje se onda nalazi u $dp_{N, M}$. 

Vremenska složenost je $O(QNM)$, a memorijska $O(NM)$.

## Rešenje kada $Q \leq 10^4$
Kao u prethodnom rešenju, izračunajmo niz $A_{i, j}$ - najmanji broj navijača koje moramo da sretnemo na putu od $(1, 1)$ do $(i, j)$, i slično $B_{i, j}$ - najmanji broj navijača koje moramo da sretnemo na putu od $(i, j)$ do $(N, M)$. 

Recimo da blokiramo polje $(x, y)$. Posmatrajmo sva polja $(x', y')$ za koja važi $x+y = x' + y'$. Možemo videti da se zapravo sva ova polja nalaze na istoj dijagonali, kao i da na svakom putu od $(1, 1)$ do $(N, M)$ prolazimo kroz tačno jedno od ovih polja. 

Ovo nam govori da, kako bismo garantovali da ne prolazimo kroz polje $(x, y)$, dovoljno je da garantujemo da prolazimo kroz neko drugo polje na ovoj dijagonali. Možemo naći put sa najmanje navijača koji prolazi kroz polje $(i, j)$ sa $A_{i, j} + B_{i, j} - a_{i, j}$. 

Možemo, dakle, proći kroz sva polja na dijagonali blokiranog polja i videti za koje dobijamo najmanji put. Bitno je primetiti da je broj polja na toj dijagonali najviše $\min(N, M)$, što je manje od $\sqrt{NM}$.

Vremenska složenost je $O(Q\cdot \sqrt{N M} + NM)$, a memorijska $O(NM)$.

## Glavno rešenje
Uradimo sve isto kao u prethodnom rešenju, sem što ćemo efikasnije naći minimum na dijagonali bez jednog polja. To ćemo uraditi tako što ćemo čuvati prefiksni i sufiksni minimum za svaku dijagonalu. Za blokirano $(x, y)$ uzećemo minimum od prefiksa do $(x-1, y+1)$ i sufiksa od $(x+1, y-1)$.

Vremenska složenost je $O(Q + NM)$, a memorijska $O(NM)$.

``` cpp title="03_guzva.cpp" linenums="1"
#include<bits/stdc++.h>
#define ll long long
#define inf 1e18
using namespace std;
int n,m,q;
vector<vector<ll> > a,dp_top,dp_bot,pref,suf;
int main() {
    scanf("%d %d",&n,&m);
    a.resize(n+2);dp_top.resize(n+2);dp_bot.resize(n+2);pref.resize(n+2);suf.resize(n+2);
    for(int i=0;i<=n+1;i++) {
        a[i].resize(m+2);dp_top[i].resize(m+2);dp_bot[i].resize(m+2);pref[i].resize(m+2);suf[i].resize(m+2);
        for(int j=0;j<=m+1;j++) a[i][j]=dp_top[i][j]=dp_bot[i][j]=pref[i][j]=suf[i][j]=inf;
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%lld",&a[i][j]);
    dp_top[1][1]=a[1][1]; dp_bot[n][m]=a[n][m];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp_top[i][j]=min(dp_top[i][j],min(dp_top[i-1][j],dp_top[i][j-1])+a[i][j]);
    for(int i=n;i>=1;i--) for(int j=m;j>=1;j--) dp_bot[i][j]=min(dp_bot[i][j],min(dp_bot[i+1][j],dp_bot[i][j+1])+a[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) pref[i][j]=min(pref[i-1][j+1],dp_top[i][j]+dp_bot[i][j]-a[i][j]);
    for(int i=n;i>=1;i--) for(int j=1;j<=m;j++) suf[i][j]=min(suf[i+1][j-1],dp_top[i][j]+dp_bot[i][j]-a[i][j]);
    scanf("%d",&q);
    while(q--) {
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%lld\n",min(pref[x-1][y+1],suf[x+1][y-1]));
    }
    return 0;
}

```
