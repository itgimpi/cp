---
hide:
  - toc
---

# 4 - Veća trka

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 3000ms | 64MB |

Možda ste čuli za tzv. "veliku trku" koja se dešava u jednoj zemlji iz komšiluka. Ako pitate njih šta je najveći godišnji spektakl kod njih, reći će vam  "U RePuBlIcI iZoMeTrIjI nAjVeĆi GoDiŠnjI sPeKtAkL jE vElIkA tRkA kOjA sE oDrŽaVa U sRcU dRžAvE - cEnTrAlGrAdU"  (fuj). Ako pitate nas, to su sve budalaštine, a prave trke se dešavaju samo kod nas u Republici Liniji. Međutim, služeći se veštim marketinškim trikom, oni su svoju "trku" promovisali na jednom od najvećih događaja na svetu - okružnom takmičenju iz informatike $2021$ - i sad imaju milione turista svake godine. E pa, sada je na naš red! A da ne pominjemo da su kvalifikacije još veće takmičenje...

Ilustrovaćemo superiornost naših trka primerom. Danas se održava jedna trka sa $N$ učesnika. Trkači su postavljeni na brojevnoj pravoj (mi se ne zamlaćujemo "slatkim" rutama, najbitnija je brzina). Svaki trkač ima različitu početnu poziciju $x_i$ i neku brzinu $v_i$. Kada trka krene, svako potrči svojom brzinom u pozitivnom smeru ("ka desno") i nastavi to da radi zauvek. Preciznije, nakon $t$ pozicija $i$-tog trkača je $x_i+t\cdot v_i$

Najbitnije je ko je brži od koga, tako da nas interesuju trenuci kada jedan trkač pretekne drugog. Da biste mogli istinski da se uživite u našu trku, zahtevamo od vas da nađete trenutak $K$-tog preticanja. 

## Opis ulaza
U prvoj liniji standardnog ulaza se nalaze dva broja $N$ i $K$ iz teksta zadatka. U narednih $N$ linija se nalaze po dva cela broja $x_i$ i $v_i$.

## Opis izlaza
Potrbeno je ispisati jedan broj - vreme $K$-tog preticanja. Vaše rešenje se smatrati tačnim ukoliko se razlikuje od komisijskog za manje od $10^{-4}$.

## Primer 1

### Ulaz

```
4 3
1 5
2 2
3 3
5 2
```

### Izlaz

```
1.333333333
```

### Objašnjenje
Prvo preticanje će se dogoditi kada prvi trkač da pretekne drugog nakon trećine sekunde (u tom trenutku se oba trkača nalaze na lokaciji $2\frac{2}{3}$). Drugo preticanje će se dogoditi kada prvi trkač pretekne trećeg nakon ukupno jedne sekunde. Konačno, treće preticanje će se dogoditi četiri trećine sekunde od početka trke, kada prvi trkač prestigne poslednjeg. U ovom primeru još i treći igrč pretekne četvrog ukupno dve sekunde nakon početka, i onda više nikad niko nikoga ne pretekne.

## Primer 2

### Ulaz

```
4 5
1 4
2 3
3 2
4 1
```

### Izlaz

```
1.000000000
```

### Objašnjenje
Nakon jedne sekunde će se sva $4$ trkača nalaziti u poziciji $5$. U tom trenutku se dešava 6 preticanja istovremeno, pa se peto preticanje desi posle jedne sekunde.


## Ograničenja
 * $1\leq N \leq 150.000$
 * $1\leq K \leq \frac{N(N-1)}{2}$
 * Za svaki test primer se garantuje da će se dogoditi barem $K$ preticanja
 * $1\leq x_1<x_2<\cdots<x_N \leq 10^9$
 * $1\leq v_i \leq 10^8$
 
Test primeri su podeljeni u $5$ disjunktnih grupa

 * U test primerima vrednim 10 poena: $N=2$.
 * U test primerima vrednim 20 poena: $N\leq2000$.
 * U test primerima vrednim 15 poena: $K=1$.
 * U test primerima vrednim 25 poena: $K\leq300.000$.
 * U test primerima vrednim 30 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Aleksa Milisavljević | Aleksa Milisavljević |

## Rešenje kada $N=2$

U ovom podzadatku, može se desiti najviše jedno preticanje. Kako je $1 \leq K$, garantuje se da će se desiti tačno jedno preticanje. To preticanje će se desiti upravo u momentu $\frac{x_2-x_1}{v_1-v_2}$.


## Rešenje kada $N \leq 2.000$

U ovom podzadatku, možemo da posmatramo skup svih preticanja koja će se desiti. Za svako $i<j$ za koje $v_i > v_j$, važi da će $i$ preteći $j$ u momentu $\frac{x_j-x_i}{v_i-v_j}$. Potom možemo da sortiramo sve ove vrednosti i uzmemo $K$-tu najmanju vrednost. Vremenska složenost ovog rešenja je $O(N^2 \log N)$.

## Rešenje kada $K = 1$

Primetimo da se prvo preticanje mora desiti između dva susedna trkača. Dakle, dovoljno je da za svako $1 \leq i < N$ za koje $v_i > v_{i+1}$ izračunamo kada će trkač $i$ preteći trkača $i+1$. To će se desiti u momentu $\frac{x_{i+1}-x_i}{v_i - v_{i+1}}$. Treba da ispišemo najraniji takav momenat. Vremenska složenost ovog rešenja je $O(N)$.

## Rešenje kada $K \leq 300.000$

Ovaj podzadatak zahteva generalizaciju prethodnog podzadatka. Znamo da se prvo preticanje mora desiti između dva susedna trkača. Da bi rešili ovaj podzadatak, potrebno je da simuliramo prvih $K$ preticanja. Ovo možemo postići tako što u nekoj strukturi (recimo `set` ili `priority_queue`) čuvamo momente kada će neki trkač prestići onog koji je trenutno neposredno ispred njega (pored momenta u kojem će se ovo desiti, potrebno je da čuvamo i poziciju trkača na kojeg se to preticanje odnosi). Pronaćemo najraniji takav momenat u strukturi i zamenimo redosled ta dva trkača. Zatim ubacimo preticanja koja će se desiti između trkača koji su postali susedni nakon ove razmene. Vremenska složenost ovog rešenja je $O(K \log N)$.

## Glavno rešenje

Primenićemo binarnu pretragu po rešenju. Sada se zadatak svodi na sledeće pitanje: "Za dato $t$, koliko preticanja se desilo do trenutka $t$?". Prvo ćemo pronaći poziciju svakog trkača posle $t$ sekundi. Pretpostavimo, za početak, da su te pozicije jedinstvene, tj. da se dva različita trkača neće naći na istoj poziciji posle $t$ sekundi. Označimo poziciju trkača $i$ sa $y_i$. Primetimo da je trkač $i$ pretekao sve one trkače $j>i$ za koje važi $y_j < y_i$. Sortirajmo sada trkače prema njihovim novim pozicijama. Označimo sa $a_i$ trkača čiji indeks odgovara $i$-toj najmanjoj poziciji u nizu $y$. Dakle, trkač $a_i$ je pretekao sve trkače $a_j$ za koje važi $j<i$ i $a_j>a_i$. Tj. broj preticanja je jednak broju parova $j<i$ takvih da $a_j > a_i$. Ovo je poznato kao problem prebrojavanja inverzija u nizu. Ovaj problem najlakše možemo rešiti koristeći se Fenvikovim stablom (tj `bit`-om) ili segmentnim stablom. Prolazimo kroz niz s desna na levo i za dato $i$ na rešenje dodamo broj elemenata u Fenvikovom stablu koji je manji od $a_i$ i potom dodamo $a_i$ u Fenvikovo stablo. Alternativno, ovaj problem se može rešiti i simulacijom `merge sort` procedure. 

Trebalo bi analizirati i šta se dešava u slučaju da su neke pozicije nakon $t$ sekundi jednake. To bi značilo da se neka preticanja dešavaju tačno nakon $t$ sekundi. U ovom slučaju ćemo, pri poređenju, redosled trkača sa istim pozicijama odrediti na osnovu njihovih originalnih indeksa. U opštem slučaju, time ćemo dobiti broj preticanja koji se desio pre strogo momenta $t$.  Pretpostavimo da se u momentu $p$ desilo $K$-to preticanje. Dakle, algoritam će za momenat $p$ vratiti vrednost koja je manja od $K$. To znači da ćemo u binarnoj pretrazi u narednom koraku posmatrati vrednosti koje su veće od $p$. Međutim, za svako $t>p$, algoritam će vratiti vrednost koja je veća ili jednaka od $K$. Nakon nekoliko iteracija binarne pretrage, algoritam će stati i ispisati vrednost $p + \varepsilon$, što je dovoljno dobro, jer rešenje treba odrediti sa greškom do $10^{-4}$. 

Konačno, prokomentarišimo i samu implementaciju binarne pretrage nad brojevima koji nisu celi. U ovom slučaju, binarnu pretragu možemo implementirati tako što poredimo razliku desne i leve granice, $r-l$, sa nekom malom vrednošću, npr. $10^{-5}$, što je u ovom slučaju dovoljno dobro. U opštem slučaju, ovo može da izazove probleme sa preciznošću i bolje je unapred fiksirati broj iteracija binarne pretrage. Na primer $50$ iteracija garantuje da će nakon završetka binarne pretrage važiti $r-l \leq \frac{r_0-l_0}{2^{50}}$, gde su $l_0$ i $r_0$ početne vrednosti leve i desne granice. 

``` cpp title="04_veca_trka.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 150007
using namespace std;
int bit[MAXN],N;
double a[MAXN];
long long x[MAXN],v[MAXN],K;
void upd(int x)
{
    while(x<=N)
    {
        bit[x]++;
        x+=(x&-x);
    }
}
long long sum(int x)
{
    long long sum=0;
    while(x)
    {
        sum+=bit[x];
        x-=(x&-x);
    }
    return sum;
}
bool provera(double s)
{
    vector<pair<double,int>> vec;
    for(int i=1;i<=N;i++) vec.push_back({x[i]+s*v[i],i});
    sort(vec.begin(),vec.end());
    fill(bit,bit+N+1,0);
    long long invcnt=0;
    for(int i=0;i<N;i++)
    {
        invcnt+=i-sum(vec[i].second);
        upd(vec[i].second);
    }
    return invcnt>=K;
}
int main()
{
    scanf("%d%lld",&N,&K);
    for(int i=1;i<=N;i++) scanf("%lld%lld",&x[i],&v[i]);
    double l=0,r=1000000000;
    while(r-l>5e-10)
    {
        double s=0.5*(l+r);
        if(provera(s)) r=s;
        else l=s;
    }
    printf("%.9f",0.5*(l+r));
}

```
