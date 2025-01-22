---
hide:
  - toc
---

# 5 - Čarobnjak

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Čarobnjak Milivoje poseduje $N$ magičnih napitaka poređanih u niz. Za svaki od tih $N$ napitaka data je njegova moć $a_i$. Milivoje želi da iskombinuje ove napitke u jedan i tako prizove moćnu čin. On zna da mu je za to potrebno da prvo odabere **tačno** $K$ od postojećih $N$ napitaka i ostale ostavi po strani. Dakle, Milivoje izabere $K$ napitaka, ostale odbaci, a izabranim napicima **ne menja redosled**. Potom Milivoje kombinuje tih $K$ napitaka sve dok mu ne ostane samo jedan.

Da bi se sprečilo što više nesreća na poslu, čarobnjaci su na međunarodnom kongresu usvojili veoma stroga pravila o tome kako se napici smeju mešati. Ta pravila su sledeća:

 - Moguće je uzeti poslednji napitak iz niza i nasuti ceo napitak u bočicu koja sadrži prvi napitak. U tom slučaju moć prvog napitka postaje razlika moći prvog i poslednjeg napitka. Dakle, ukoliko je prvi napitak imao moć $x$, a poslednji moć $y$, pri ovoj operaciji poslednji napitak se uklanja iz niza, a moć prvog napitka postaje $x-y$.
 - Moguće je uzeti prvi napitak iz niza i nasuti ceo napitak u bočicu koja sadrži poslednji napitak. U tom slučaju moć poslednjeg napitka postaje razlika moći poslednjeg i prvog napitka. Dakle, ukoliko je prvi napitak imao moć $x$, a poslednji moć $y$, pri ovoj operaciji prvi napitak se uklanja iz niza, a moć poslednjeg napitka postaje $y-x$.

 **Primetiti da primenom ovih operacija moć nekog napitka može postati i negativna.** U oba slučaja jedan napitak se potroši, tj. broj napitaka u nizu se smanji za jedan. U svakom trenutku Milivoje može da bira koje će od pravila koristiti. On će ovaj proces ponoviti $K-1$ puta, tj. sve dok u nizu ne ostane samo jedan napitak. Kako Milivoje želi da prizove što moćniju čin, njega interesuje koja je najveća moguća moć napitka koji može ostati nakon primene svih operacija. Milivoje je jedan od najboljih čarobnjaka na svetu i ukoliko mu pomognete, on će baciti čin koja će Vam doneti $100$ poena na ovom zadatku.
 
## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva pozitivna cela broja $N$ i $K$ - broj napitaka na početku i broj napitaka koje Milivoje treba da izabere. 

U drugom redu standardnog ulaza, nalazi se $N$ celih brojeva, $i$-ti od njih je $a_i$ i on predstavlja moć $i$-tog napitka.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza potrebno je ispisati jedan ceo broj, koji predstavlja najveću moć napitka koji može ostati u nizu nakon primene svih operacija.

## Primer 1
### Ulaz
```
3 2
5 3 2
```

### Izlaz
```
3
```

### Objašnjenje
Milivoje treba da izabere dva napitka. Ukoliko izabere prvi i poslednji napitak i primeni drugu operaciju, on će dobiti napitak koji ima moć $a_1-a_3=5-2=3$.

## Ograničenja

- $2 \leq K \leq N \leq 200.000$
- $|a_i| \leq 100.000$, za svako $1 \leq i \leq N$

Test primeri su podeljeni u pet disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $N \leq 10$.
-   U test primerima vrednim $15$ poena: $N \leq 200$.
-   U test primerima vrednim $20$ poena: $K = N$.
-   U test primerima vrednim $20$ poena: $N \leq 1.000$.
-   U test primerima vrednim $35$ poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Aleksa Milisavljević | Aleksa Milisavljević | Pavle Martinović |

## Rešenje za $N \leq 10$

U ovom slučaju možemo za svaki odabir $K$ od $N$ elemenata isprobati sve moguće načine da izvršimo operacije. Vremenska složenost je $O({N \choose K} \cdot 2^K)$.

## Rešenje za $N \leq 200$


U ovom podzadatku do rešenja možemo doći primenom dinamičkog programiranja. Definišimo $dp[l][r][p][g][h]$ na sledeći način:

 - Za $g=0, h=0$ najveća vrednost tako da u nizu napitaka ostane napitak sa tom moći, pa onda napici iz intervala $[l,r]$ i da smo izvan intervala odabrali da zadržimo $p$ elemenata.
 - Za $g=0, h=1$ najmanja vrednost tako da u nizu napitaka ostane napitak sa tom moći, pa onda napici iz intervala $[l,r]$ i da smo izvan intervala odabrali da zadržimo $p$ elemenata.
 -  Za $g=1, h=0$ najveća vrednost tako da u nizu napitaka ostane napitak sa tom moći, pre njega napici iz intervala $[l,r]$ i da smo izvan intervala odabrali da zadržimo $p$ elemenata.
  - Za $g=1, h=1$ najmanja vrednost tako da u nizu napitaka ostane napitak sa tom moći, pre njega napici iz intervala $[l,r]$ i da smo izvan intervala odabrali da zadržimo $p$ elemenata.

Kako se operacijama isključivo oduzima vrednost jednog kraja od vrednosti drugog, to se pronalaženje maksimalne ili minimalne vrednosti na jednom kraju upravo svodi na pronalaženje minimalne odnosno maksimalne vrednosti na suprotnom i primenu jedne operacije. Ovo dinamičko programiranje je vremenske složenosti $O(N^3)$.

## Rešenje za $K = N$

Za rešavanje ovog podzadatka, neophodno je primetiti da su sve vrednosti moći napitka koji ostaje poslednji u nizu ili razlika nepraznog prefiksa i odgovarajućeg nepraznog sufiksa ili razlika nepraznog sufiksa i odgovarajućeg nepraznog prefiksa. Za početak, primetimo da moć napitka koji ostaje poslednji u nizu uvek možemo preslikati na niz $b$ koji sadrži $N$ vrednosti koje su isključivo $+$ ili $-$. Konkretno, ako moć nekog napitka iz početnog niza učestvuje sa znakom $+$ u moći napitka koji ostaje poslednji, na tu poziciju u nizu $b$ stavljamo $+$, a u suprotnom $-$. Posmatrajmo sada niz $b$. Želimo da ga svedemo na niz koji ima samo jedan element i taj element ima vrednost $+$, primenom operacija definisanih u tekstu. Primetimo da ukoliko prva i poslednja vrednost u nizu $b$ imaju isti znak, tada sigurno nije moguće izvršiti ni jednu operaciju, jer tada želimo da i prvi i poslednji element učestvuju sa istim znakom, a znamo da primenom bilo koje od dve operacije dovodimo do toga da u konačnoj sumi učestvuju sa različitim znakom. U suprotnom, možemo da izvršimo bilo koju od ove dve operacije. Na nizu $b$ ovo se održava brisanjem jednog od dva kraja. Dakle, ukoliko posle primene nekih operacija dođemo do niza koji ima više od jednog elementa i njegovi krajevi su različitog znaka, onda nas taj niz nikako ne može dovesti do niza koji sadrži samo jedan element $+$. Zbog toga nije moguće da u nizu $b$ postoji više od jednog para susednih pozicija koje imaju suprotan znak. Dakle, dovoljno je da uzmemo maksimum razlika svih nepraznih prefiksa i odgovarajućih nepraznih sufiksa, odnosno nepraznih sufiksa i odgovarajućih nepraznih prefiksa. Ovo je moguće uraditi u  vremenskoj složenosti $O(N)$.

## Rešenje kad $N \leq 1000$

Rešavanje ovog podzadatka se nadovezuje na rešavanje prethodnog. Fiksiraćemo svaku poziciju koja će predstavljati razliku između prefiksa i sufiksa (odnosno sufiksa i prefiksa) i potom izbaciti $N-K$ elemenata tako da se ta razlika maksimizuje i da ni prefiks ni sufiks ne ostanu prazni. Ovo je moguće postići sortiranjem celog niza sa promenjenim znakom elemenata u sufiksu, te izbacivanjem najmanjih $N-K$ elemenata. Neophodno je samo voditi računa da izbacivanje tih elemenata ne dovede do praznog prefiksa ili sufiksa. Ovakvo rešenje je vremenske složenosti $O(N^2 \log N)$.

## Glavno rešenje

Za rešenje celog zadatka, neophodno je optimizovati rešenje prethodnog podzadatka tako da ne moramo da za svaku poziciju sortiramo niz i ponovo biramo najmanje elemente. Glavna ideja u toj optimizaciji se zasniva na tome da se promenom pozicije koja razdvaja prefiks i sufiks za jedan menjaju tačno dve vrednosti iz niza koji sortiramo i iz kojeg biramo najmanjih $N-K$. Možemo koristiti strukturu `set` ili segmentno stablo da bi održavali taj niz. Rešenje kompletnog zadatka je vremenske složenosti $O(N \log N)$.

``` cpp title="05_carobnjak.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 200005
#define maxv 100000
using namespace std;
long long a[maxn];
int n,k;
long long pref[maxn];
long long suf[maxn];
int cnt[4*maxn];
int pref_cnt[4*maxn];
long long sum[4*maxn];
inline void clear_seg(int id,int l,int r) {
    sum[id]=0;
    cnt[id]=0;
    pref_cnt[id]=0;
    if(l==r) return;
    int m=(l+r)/2;
    clear_seg(id*2+1,l,m);
    clear_seg(id*2+2,m+1,r);
}
inline void update(int id,int l,int r,int pos,int c,int p,int s) {
    cnt[id]+=c;
    pref_cnt[id]+=p;
    sum[id]+=s;
    if(l==r) return;
    int m=(l+r)/2;
    if(pos<=m) update(id*2+1,l,m,pos,c,p,s);
    else update(id*2+2,m+1,r,pos,c,p,s);
}
inline pair<long long,pair<int,int>> pick(int id,int l,int r,int k,int ps,int ss) {
    if(k==0) return {0,{0,0}};
    if(k>=cnt[id] && ps>pref_cnt[id] && ss>cnt[id]-pref_cnt[id]) return {sum[id],{pref_cnt[id],cnt[id]}};
    if(l==r) {
        if(k>=cnt[id]) {
            if(ps==pref_cnt[id]) return {1ll*(l-maxv)*(cnt[id]-1),{pref_cnt[id]-1,cnt[id]-1}};
            else return {1ll*(l-maxv)*(cnt[id]-1),{pref_cnt[id],cnt[id]-1}};
        }
        else {
            return  {1ll*(l-maxv)*k,{k,k}};
        }
    }
    int m=(l+r)/2;
    pair<long long,pair<int,int> > p2=pick(id*2+2,m+1,r,k,ps,ss);
    pair<long long,pair<int,int> > p1=pick(id*2+1,l,m,k-p2.second.second,ps-p2.second.first,ss-p2.second.second+p2.second.first);
    return {p1.first+p2.first,{p1.second.first+p2.second.first,p1.second.second+p2.second.second}};
}
long long solve() {
    for(int i=1;i<=n;i++) {
        pref[i]=pref[i-1]+a[i];
    }
    for(int i=n;i>=1;i--) {
        suf[i]=suf[i+1]+a[i];
    }
    long long ans=-1e18;
    clear_seg(0,0,maxn);
    update(0,0,maxn,-a[1]+maxv,1,1,-a[1]);
    for(int i=2;i<=n;i++) {
        update(0,0,maxn,a[i]+maxv,1,0,a[i]);
    }
    for(int i=1;i<=n-1;i++) {
        pair<long long,pair<int,int > > p=pick(0,0,maxn,n-k,i,n-i);
        ans=max(ans,pref[i]-suf[i+1]+p.first);
        update(0,0,maxn,a[i+1]+maxv,-1,0,-a[i+1]);
        update(0,0,maxn,-a[i+1]+maxv,1,1,-a[i+1]);
    }
    return ans;
}
int main() {
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
    }
    long long ans=solve();
    for(int i=1;i<=n;i++) {
        a[i]=-a[i];
    }
    ans=max(ans,solve());
    printf("%lld",ans);
    return 0;
}

```
