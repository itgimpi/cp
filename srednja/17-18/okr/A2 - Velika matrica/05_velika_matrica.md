---
hide:
  - toc
---

# A2 - Velika matrica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |

Prošlo je vreme igre, uživanja i razonode. Prošlo je vreme malih matrica. Danas su računari neverovatno brzi i mogu izvršiti i do $10^{100}$ komandi u sekundi. Iz tog razloga komisija vam je spremila jednostavan zadatak sa jednom matricom i mnogo interesantnih upita. 

U ovom zadatku vam je data matrica dimenzije $n \cdot m$ - matrica ima tačno $n$ vrsta i tačno $m$ kolona. Za svako $i$ ($1 \leq i \leq n$) i $j$ ($1 \leq j \leq m$) vrednost na poziciji ($i,j$) u matrici $A$ je definisano na sledeći način:

$A_{i,j}$ = ($i$ + $j$) mod $M$

Operacija $X$ $mod$ $M$ predstavlja ostatak koji daje broj $X$ pri deljenju sa $M$.

Potrebno je odgovoriti na $q$ upita oblika : Naći sumu svih brojeva u podmatrici matrice A sa gornjim levim temenom ($x_l,y_l$) i donjim desnim temenom($x_r,y_r$) po modulu $10^9+7$. Podmatrica matrice A sa navedenim ograničenjima obuhvata sve elemente $A_{i,j}$ takve da važi  $x_l \leq i \leq x_r$ , $y_l \leq j \leq y_r$.

## Opis ulaza
U prvoj liniji standardnog ulaza nalaze se brojevi $n$, $m$, $M$ -- broj vrsta matrice $A$, broj kolona matrice $A$ i modul $M$ opisan u tekstu zadatka, redom. Druga linija standardnog ulaza sadrži broj $q$, broj upita na koje je potrebno odgovoriti. Narednih $q$ linija sadrže po četiri broja, koji predstaljaju, redom, vrstu gornjeg levog temena podmatrice, kolonu gornjeg levog temena podmatrice, vrstu donjeg desnog temena podmatrice i kolonu donjeg desnog temena podmatrice.

## Opis izlaza
Na standardnom izlazu u $q$ redova odgovoriti na upite opisane u tekstu zadatka, tačnije u $i$-toj liniji standardnog izlaza ispisati sumu tražene podmatrice po modulu $10^9+7$ iz $i$-tog upita.

## Primer
### Ulaz
```
5 4 3
3
1 2 4 3
2 3 4 4
3 3 3 3
```

### Izlaz
```
7
6
0
```

## Objašnjenje primera
Matrica je dimenzija $5 \cdot 4$, $M=3$. Matrica izgleda:

```
2 0 1 2
0 1 2 0
1 2 0 1
2 0 1 2
0 1 2 0
```
                    
U prvom upitu, gornje levo teme podmatrice ima koordinate ($1,2$), dok donje desno teme ima koordinate ($4,3$). Rešenje ovog upita je:
$$
(0 + 1 + 1 +2 +2 + 0 + 0 +1 ) \ \text{ mod } \ (10^9+7) = 7 \ \text{ mod } \ (10^9+7) = 7.
$$

U trećem upitu jedini broj se nalazi na polju ($3,3$) i on ima vrednost $0$. Rešenje ovog upita je $0 \ \text{ mod } \ 10^9+7 = 0$.

## Ograničenja

* $1 \leq n,m,M \leq 10^9$.
* $1 \leq q \leq 2\cdot 10^5$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U primerima vrednim 10 poena važiće ograničenje $1\leq n,m,q \leq 100$.
* U primerima vrednim 10 poena važiće ograničenje $M=2$.
* U primerima vrednim 10 poena važiće ograničenje $1\leq n,m \leq 1000$.
* U primerima vrednim 30 poena važiće ograničenje $1\leq n,m,M \leq 10^6$.
* U primerima vrednim 40 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Ivan Stošić | Ivan Stošić |

Za prvi podzadatak rešenje koje računa sumu podmatrice element po element tj. rešenje složenosti $O(nmq)$ je dovoljno brzo.

Za podzadatak gde je $M=2$, ukoliko je visina $H$ ili širina $W$ podmatrice paran broj, odgovor je $\frac{WH}{2}$. U suprotnom (ako su oba neparna), rešenje je $\frac{WH + x}{2}$, gde je $x$ vrednost u gornjem levom uglu matrice. Ovo proističe iz činjenice da matrica izgleda kao šahovska tabla.

Za podzadatak gde je $n,m \leq 1000$, možemo izračunati $2D$ prefiksne sume, odnosno za svako $u,v$ vrednost $P_{u,v} = \sum_{i\leq u, j \leq v} A_{i, j}$. Za ove vrednosti važi sledeća veza: $P_{u,v} = P_{u-1,v} + P_{u,v-1} - P_{u-1,v-1} + A_{u,v}$. Nakon toga, vrednost u podmatrici $(x_l, y_l) - (x_r, y_r)$ nalazimo kao $P_{x_r,y_r}+P_{x_l-1,y_l-1}-P_{x_r, y_l-1}-P_{x_l-1,y_r}$. Vremenska složenost je $O(nm+q)$.

Četvrti podzadatak se rešava isto kao poslednji, s tim što za pojedine matematičke sume nije neophodno tražiti formulu složenosti $O(1)$ već se mogu izračunati unapred sve vrednosti u linearnoj složenosti po $n,m$.

Rešenje za maksimalni broj poena se sastoji od toga da se matrica podeli na tri dela, zatim se svaki od tih delova deli na tri poddela, a za svaki od njih se suma može izračunati u $O(1)$, pa je ukupna vremenska složenost $O(1)$ po upitu odnosno $O(q)$. Ukoliko je matrica pravougaona, prvi deo biće jednakokrako-pravougli trougao kome je kateta kraća ivica (gornja ili leva) a prav ugao mu je u gornjem-levom temenu podmatrice. Slično, drugi deo biće jednakokrako-pravougli trougao kome je prav ugao u donjem-desnom temenu podmatrice a kateta mu je kraća ivica (desna ili donja). Treći deo je ostatak ove podmatrice koji će imati oblik paralelograma (ovaj deo može biti prazan). U slučaju da je data podmatrica kvadratna možemo uzeti da donji desni trougao ima za $1$ kraću katetu od gornjeg levog, a treći deo (paralelogram u sredini) će opet biti prazan.

Zatim, svaki od ovih delova delimo na poddelove. Svaki od delova će se sastojati od skupa sporednih dijagonala takvih da su unutar dijagonale svi brojevi jednaki. Kod prvog dela (gornji/levi trougao), ove dijagonale imaju rastuće dužine, kod drugog dela (donji/desni trougao) one imaju opadajuće dužine, a kod trećeg (srednjeg) dela one imaju jednake dužine. Svaki od delova delimo na tri poddela: Srednji od ovih poddelova se sastoji maksimalnog broja poddijagonala koje redom uzimaju vrednosti $0, 1, 2, \ldots, M-1$, dok su ostala dva dela levi i desni ostaci. Za računanje sume unutar svakog od ovih poddelova možemo koristiti sledeće identitete:

* $\sum_{i=1}^n i = \frac{n(n+1)}{2}$
* $\sum_{i=1}^n i^2 = \frac{n(n+1)(2n+1)}{6}$

Neke od posledica koje su korisne pri računanju suma su:

* $\sum_{i=1}^n (a+i)(b+i) = abn + \frac{n(n+1)(2n+1)}{6} + \frac{(a+b)n(n+1)}{2}$
* $\sum_{i=1}^n (a+i)(b-i) = abn - \frac{n(n+1)(2n+1)}{6} + \frac{(b-a)n(n+1)}{2}$

``` cpp title="05_velika_matrica.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const long long mo=1e9+7;

int n,m;
long long mod;
int q;

long long gcd(long long x, long long y)
{
    if (x<0) x*=-1;
    if (y<0) y*=-1;
    if (x==0 || y==0) return max(x,y);
    if (x%y==0) return y;
    return gcd(y,x%y);
}

pair<long long,pair<int,int> > calc(int x, int y)
{
    long long tot=0;

    //kratim po y
    tot=x*(y/mod);
    tot%=mo;
    y%=mod;

    // kratim po x
    tot+=y*(x/mod);
    tot%=mo;
    x%=mod;// sada x<mod && y<mod
    return {tot,{x,y}};
}

long long mul(long long n, long long x, long long k)
{
    long long first=k*n;
    first%=mo;
    first*=x;
    first%=mo;

   return first;
}

long long sumDOWN(long long n, long long x, long long k)//sum (n+i) *(x-i) (i=0...k-1) po modulu 10^9+7
{
    long long ans=0;
    long long first=mul(n,x,k);

    long long p=6;

    long long second=(k-1)/gcd(k-1,p);
    p/=gcd(k-1,p);

    long long third=k/gcd(k,p);
    p/=gcd(k,p);

    long long fourth=(3*n-3*x+2*k-1);
    long long fifth=fourth;
    fourth=fifth/gcd(fifth,p);
    p/=gcd(fifth,p);//sada je p sigurno 1

    long long sixth=mul(second,third,fourth);

    ans=(first-sixth+mo)%mo;

    return ans;
}

long long sumUP(long long n, long long x, long long k) //sum (n+i)*(x+i) (i=0...k-1)  po modulu 10^9+7
{
    long long ans=0;

    long long first= mul(n,x,k);

    long long p=6;

    long long second=(k-1)/gcd(k-1,p);
    p/=gcd(k-1,p);

    long long third=k/gcd(k,p);
    p/=gcd(k,p);

    long long fourth=(3*n+3*x+2*k-1);
    long long fifth=fourth;
    fourth=fifth/gcd(fifth,p);
    p/=gcd(fifth,p);//sada je p sigurno 1

    long long sixth=mul(second,third,fourth);

    ans=(first+sixth)%mo;

  return ans;
}

long long sumLine(long long n, long long x, long long k) // sum (n+i)*x  i=0...k-1 po modulu 10^9+7
{
  long long ans=0;

  long long first=mul(n,x,k);

  long long second=k-1;
  long long third=k;

  if (second%2==0) second/=2; else third/=2;

  long long fourth=mul(second,third,x);

  ans=(fourth+first)%mo;

  return ans;
}
long long finish(int xl, int yl,int xr, int yr)
{
    if (xl>xr || yl>yr) return 0;
    long long ans=0;

    long long dx=(xr-xl)+1;
    long long dy=(yr-yl)+1;
    long long dz=min(dx,dy)-1;

    long long currentTop=(xl+yl)%mod;
    long long rest=mod-currentTop;

    if (rest>=dz)
         ans=sumUP(currentTop,1,dz);
     else
     {
        ans=sumUP(currentTop,1,rest);
        ans+=sumUP(0,rest+1, dz-rest);
     }

    currentTop+=dz;
    currentTop%=mod;
    ans%=mo;

    long long dp=max(dx,dy)-dz;
    rest=mod-currentTop;

    if (rest>=dp)
            ans+=sumLine(currentTop,min(dx,dy),dp);
    else
    {
       ans+=sumLine(currentTop,min(dx,dy),rest);
       ans+=sumLine(0,min(dx,dy),dp-rest);
    }

    currentTop+=dp;
    currentTop%=mod;
    ans%=mo;

    rest=mod-currentTop;

    if (rest>=dz)
         ans+=sumDOWN(currentTop,dz,dz);
     else
     {
        ans+=sumDOWN(currentTop,dz,rest);
        ans+=sumDOWN(0,dz-rest, dz-rest);
     }

    ans%=mo;

    return ans;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&mod);
    scanf("%d",&q);

    long long val=(1ll*(mod-1)*mod)/2;
    val%=mo;
  
    while(q--)
    {
        int xl,yl,xr,yr;
        scanf("%d%d%d%d",&xl,&yl,&xr,&yr);
        long long ans=0;
        pair<long long,pair<int,int> > rest = calc(xr-xl+1,yr-yl+1);
        ans=(val*rest.first)%mo;
        ans+=finish(xr-rest.second.first+1,yr-rest.second.second+1, xr, yr);
        ans%=mo;
        printf("%lld\n",ans);
    }

  return 0;
}

```
