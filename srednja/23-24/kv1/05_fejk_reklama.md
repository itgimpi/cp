---
hide:
  - toc
---

# 5 - Fejk reklama

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Svetski poznata kompanija "Najbolji ltd." razvija novu igru za mobilne telefone. Ova igra se diči svim najnovijim grafičkim inovacijama, uključujući *ray tracing, DLSS*, itd. Pored nadmoćne grafike, igrica poseduje i revolucionaran gejmplej.

U igri ima $T$ nivoa. 

Igrač započinje nivo sa vojskom veličine $S$ i nailazi na $N$ prepreka, sa ciljem maksimizovanja veličine svoje vojske nakon svih prepreka. Neka je veličina vojske koju igrač poseduje pre $i$-te prepreke jednaka $x$. U $i$-toj od prepreci igrač može da bira između dve opcije, "*$m_i$" ili "+$a_i$". Ukoliko odabere prvu opciju, veličina njegove vojske nakon $i$-te prepreke postaje $x*m_i$, a ukoliko odabere drugu opciju veličina njegove vojske postaje $x+a_i$.

Dodatno, nakon $i$-te prepreke, veličina vojske koju igrač poseduje mora biti barem $l_i$ i ne sme biti veća od $r_i$ (u suprotnom most posle $i$-te prepreke pukne pod prevelikim opterećenjem).

Primetite da vojska može da ima negativno vojnika. Takođe, neki nivoi mogu da budu toliko teški da ih uopšte nije ni moguće preći. 

Na slici ispod je prikazan jedan nivo ove igrice:


Srećom po tebe, dragi takmičaru, odabran si da budeš tester ove igrice u poznoj fazi njene proizvodnje. 

Tebe naravno, najviše interesuje kolika je teoretski maksimalna moguća veličina vojske koju možeš postići u svakom niovu.

## Opis ulaza

U prvom redu standardnog ulaza, dat je ceo broj $T$ - koji predstavlja broj nivoa u igrici. U narednim redovima slede opisi $T$ nivoa, pet redova po nivou.

U prvom redu opisa svakog nivoa su celi brojevi $N$ i $S$ - broj prepreka i početna veličina vojske.
U drugom redu opisa svakog nivoa nalazi se $N$ celih brojeva, $i$-ti od njih je $m_i$. 
U trećem redu opisa svakog nivoa nalazi se $N$ celih brojeva, $i$-ti od njih je $a_i$.
U četvrtom redu opisa svakog nivoa nalazi se $N$ celih brojeva, $i$-ti od njih je $l_i$.
U petom redu opisa svakog nivoa nalazi se $N$ celih brojeva, $i$-ti od njih je $r_i$.

## Opis izlaza
Ispisati $T$ redova. U $i$-tom od njih ispisati maksimalnu moguću veličinu vojske nakon svih prepreka iz $i$-tog nivoa (primetite da ovaj broj može da bude i negativan), ili `nemoguce`, ukoliko nije moguće preći $i$-ti nivo. 

## Primer 1

### Ulaz

```
1
2 4
2 3
-1 4
-2 2
5 10
```

### Izlaz

```
9
```
### Objašnjenje

Nivo sa slike. Igrač počinje igricu sa vojskom veličine $4$. Ukoliko bi odabrao opciju $*2$ na prvoj prepreci, ne bi mogao da prođe preko nje jer bi imao $4*2=8>5$ vojnika. Zato bira opciju $-1$ i do druge prepreke dolazi sa $3$ vojnika. Na njoj ima dve opcije $*3$ i $+4$. Prvom opcijom završava nivo sa $9$ vojnika, dok izborom druge opcije završava igricu sa $7$ vojnika. Zato je maksimum koji igrač može da postigne upravo $9$.

## Primer 2

### Ulaz

```
1
1 5
2
-2
4
6
```

### Izlaz

```
nemoguce
```
### Objašnjenje

U ovom niovu igrač ima dve opcije $*2$ i $-2$. Prvom opcijom bi imao vojsku od $5*2=10$ vojnika, dok bi drugom opcijom imao vojsku od $5-2=3$ vojnika. Međutim ni jedan ni drugi broj nisu u intervalu $[4,6]$, te ovaj nivo nije moguće preći.

## Primer 3

### Ulaz

```
2
3 5
2 2 2
10 9 8
-100 -100 0
100 100 39
3 -5
100 100 100
1 1 1
-1000000000 -1000000000 -1000000000
1000000000 1000000000 1000000000
```

### Izlaz

```
38
-2
```




## Ograničenja
* $T <= 10$
* $N <= 40$
* $|S| <= 10^9$
* $|m_i|, |a_i| <= 10^9$
* $|l_i|,|r_i| <= 10^9$ i $l_i <= r_i$

Test primeri su podeljeni u četiri disjunktne grupe:

* U testovima vrednim 10 poena: $N <= 20$.
* U testovima vrednim 30 poena: $N <= 30$, $m_i = 1$, za svako $1 \leq i \leq N$.
* U testovima vrednim 40 poena: $N <= 30$.
* U testovima vrednim 20 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksandar Višnjić | Aleksa Milisavljević | Aleksandar Višnjić | Dimitrije Erdeljan i Aleksandar Višnjić |

## Rešenje za $N\leq 20$
Kod svake prepreke imamo $2$ izbora, te rekurzivno rešenje daje složenost $2^N$,

## Rešenje kada $m_i=1$ za svako $1\leq i\leq N$ i $N \leq 30$
Koristimo *meet in the middle* tehniku. Za prvih $\lfloor \frac{N}{2} \rfloor$ prepreka izračunamo sve moguće veličine vojske (rekurzivno kao u prethodnom podzadatku). Zatim, za narednih $\lceil \frac{N}{2} \rceil$ počnemo od neke neodređene veličine vojske $x$ i simuliramo prepreke za nju. Podatke čuvamo u sledećem formatu:

* Ako je početno $x$ u intervalu $[y,z]$, onda je $x+s$ moguća trenutna veličina vojske.

Naravno, ovih stavki može imati proizvoljno mnogo, te ih čuvamo u nekoj kolekciji. Ta kolekcija može biti prazna. Na početku ta kolekcija sadrži samo jednu stavku - onu za početno $x$ i ograničenje $[-10^9,10^9]$

 Kada prolazimo kroz prepreke, zbog uslova $m_i=1$, imamo dva izbora:

* Ne radimo ništa, i dodajemo novo ograničenje za interval za početno $x$ na svaku stavku;
* Za svaku početnu stavku, napravimo kopiju i simuliramo dodavanje $a_i$ na $x$.  Pamtimo inkrement, a potom dodajemo novo ograničenje za početno $x$ u obliku intervala. 

Pri svakom koraku veličina kolekcije ne poraste za više od duplo. Krajnja veličina nije veća od $2^N$. 

Kada nakon izvšavanja prve polovine saznamo svako moguće $x$, a nakon izvršavanja druge polovine dobijemo sve moguće stavke, možemo ih spojiti i izračunati najveću moguću veličinu vojske nakon svih prođenih prepreka.

Memorijska složenost je $O(2^{N/2})$, dok je vremenska $O(2^{N/2} \cdot N)$ zbog sortiranja i binarne pretrage.

## Rešenje kada $N \leq 30$
Slično kao u prethodnom podzadatku, koristimo tehniku *meet in the middle*. Problem nastaje pri ažuriranju "*$m_i$". U prvom delu možemo rekurzivno pronaći svako moguće $x$. Ali, u drugom delu više nemamo jednostavne stavke. One sada postaju komplikovanije funkcije od $x$. Ipak, ispostavlja se da su te funkcije linearne. Na početku imamo funkciju $f(x)=x$. Ona je očito linearna. Pretpostavimo da pre neke prepreke imamo kolekciju linearnih funkcija. Posmatrajmo jednu od njih, neka je to $f(x)=p x + q$. Za modifikovanje nje imamo dve opcije:

* $f(x)=p m_i x + q m_i$
* $f(x) = px + q + a_i$

Primećujemo da pri oba izbora, naša funkcija zaista ostaje linearna. Međutim, dodavanje novih ograničenja za segment na originalno $x$ je nešto komplikovanije, ali izvodivo. Možemo celu stavku zamisliti kao funkciju sa ograničenim domenom (koji će biti neki segment).

Na kraju, iz prve polovine imamo svako moguće $x$, a iz druge polovine imamo svaku moguću linearnu funkciju sa odgovarajućim domenom. Spajanje možemo izvršiti tako što fiksiramo funkciju sa njenim domenom $[l,r]$. Primetimo da linearna funkcija dostiže maksimum u krajevima, tj. da tražimo $x$ da bude što bliže "većem kraju". Ovim skraćujemo mogućnost na najviše jedno moguće $x$. Sada jednostavno prođemo po svakoj funkciji i evaluiramo je u njenom optimalnom $x$.

Bitno je napomenuti da se može desiti da koeficijenti neke funkcije izađu iz opsega tipa long long. Takva je, na primer, funkcija $f(x)=10^{100}x -10^{100}$. Ona staje u ograničenje $[-10^9,10^9]$ za tačku $x=1$. Međutim, primetimo da takve funkcije čiji su koeficijenti veći od $10^{18}$ (po apsolutnoj vrednosti) staju u ograničenje $[l_i,r_i]$ samo u jednoj tački. Pošto je domen te funkcije u stvari jedna tačka, dovoljno je "kompresovati" je. Neka je $(x_e,y_e=f(x_e))$ ta tačka (u opštem slučaju "prevelike" funkcije). Nju možemo opisati i na sledeći način: $f(x) = 0x + y_e$. Ona očito ima koeficijente u opsegu $[-10^9,10^9]$, te staje u long long.

Memorijska složenost je $O(2^{N/2})$, dok je vremenska $O(2^{N/2} \cdot N)$ zbog sortiranja i binarne pretrage.

## Rešenje kada $N \leq 40$

Koristimo ideje iz prethodnog podzadatka. Potrebno je smanjiti vremensku složenost na $O(2^{N/2})$. Primetimo dve činjenice:

* Algoritam binarne pretrage može se zameniti sa tehnikom dva pokazivača
* Sortiranje parametara je moguće vršiti u $O(2^{N/2})$ vremenskoj složenosti.

Jasno je da ako dokažemo i izvedemo drugu činjenicu, ukupna složenost biće $O(2^{N/2})$.

Zamislimo da imamo trenutni niz $x_1,x_2,\ldots ,x_k$ (u prvom delu meet in the middle algoritma ) i da njega ažuriramo novim operacijama "*$m$" i "+$a$".  Poznato je da ako je početni niz sortiran, tada su i nizovi 

$$
m\cdot x_1,m\cdot x_2, \ldots, m\cdot x_k;
$$ 

$$
a+x_1, a+x_2, \ldots ,a+x_k.
$$ 

(potencijalno u obrnutom redosledu). Sada možemo primeniti algoritam nalik *merge sort* . Vremenska složenost ovog algoritma sortiranja zaista jeste $O(2^{N/2})$.

Funkcije slično sortiramo kada ih pripremamo za tehniku dva pokazivača. Međutim, potrebno ih je filtrirati u dve grupe. Jednu grupu sortiramo po levom kraju domena (one funkcije sa negativnim koeficijentom uz $x$), a drugu grupu po desnom kraju domena (one funkcije sa nenegativnim koeficijentom uz $x$).




``` cpp title="05_fejk_reklama.cpp" linenums="1"
#include <bits/stdc++.h>
#define maxn 44
#define maxl 2100000
#define maxk 530000
using namespace std;
long long t;
long long n,s;
long long m;
long long mult[maxn];
long long add[maxn];
long long l[maxn];
long long r[maxn];
long long npot[2][maxl];
long long add_pot[maxl];
long long mult_pot[maxl];
long long add_potn;
long long mult_potn;
long long npotn[maxn];
inline void construct_pot(long long i,long long g) {
    if(i>m) return;
    add_potn=mult_potn=0;
    for(long long j=0;j<npotn[g];j++) {
        long long v=npot[g][j];
        long long add_v = 1ll * v + add[i];
        if(l[i]<=add_v && add_v<=r[i]) add_pot[add_potn++]=add_v;
        long long mult_v = 1ll * v * mult[i];
        if(l[i]<=mult_v && mult_v<=r[i]) mult_pot[mult_potn++]=mult_v;
    }
    if(mult[i]<0) {
        reverse(mult_pot,mult_pot+mult_potn);
    }
    long long p=0;
    long long q=0;
    npotn[g^1]=0;
    while(p<add_potn && q<mult_potn) {
        if(add_pot[p]<mult_pot[q]) {
            npot[g^1][npotn[g^1]++]=add_pot[p];
            p++;
        }
        else {
            if(add_pot[p]>mult_pot[q]) {
                npot[g^1][npotn[g^1]++]=mult_pot[q];
                q++;
            }
            else {
                npot[g^1][npotn[g^1]++]=add_pot[p];
                p++;
                q++;
            }
        }
    }
    while(p<add_potn) {
        npot[g^1][npotn[g^1]++]=add_pot[p];
        p++;
    }
    while(q<mult_potn) {
        npot[g^1][npotn[g^1]++]=mult_pot[q];
        q++;
    }
    construct_pot(i+1,g^1);
}
struct func {
    long long k,n;
    long long l,r;
};
inline bool l_cmp(func a,func b) {
    return a.l>b.l;
}
inline bool r_cmp(func a,func b) {
    return a.r<b.r;
}
inline bool (*(cmp[2]))(func x, func y) = {l_cmp,r_cmp};
func fnc[2][2][maxk];
long long fncn[2][2];
func add_fnc[maxk];
func mult_fnc[maxk];
long long add_fncn;
long long mult_fncn;
inline void construct_linear(long long i,long long g) {
    if(i<=m) {
        for(long long id=0;id<2;id++) {
            for(long long j=0;j<fncn[id][g];j++) {
                if(fnc[id][g][j].l==fnc[id][g][j].r) {
                    fnc[id][g][j].n=fnc[id][g][j].k*fnc[id][g][j].l+fnc[id][g][j].n;
                    fnc[id][g][j].k=0;
                }
            }
        }
        return;
    }
    for(long long id=0;id<2;id++) fncn[id][g^1]=0;
    for(long long id=0;id<2;id++) {
        add_fncn=mult_fncn=0;

        for(long long j=0;j<fncn[id][g];j++) {
            func f=fnc[id][g][j];
            if(f.l==f.r) {
                f.n=f.k*f.l+f.n;
                f.k=0;
            }
            long long nl = f.l-add[i];
            long long nr = f.r-add[i];
            long long ml = max(l[i-1],nl);
            long long mr = min(r[i-1],nr);
            if(ml<=mr) {
                func add_f = {f.k,f.k*add[i]+f.n,ml,mr};
                add_fnc[add_fncn++]=add_f;
            }
        }
        if(mult[i]>=0) {
            for(long long j=0;j<fncn[id][g];j++) {
                func f=fnc[id][g][j];
                if(f.l==f.r) {
                    f.n=f.k*f.l+f.n;
                    f.k=0;
                }
                long long nl,nr;
                if(mult[i]>0) {
                    nl = f.l/mult[i];
                    while(nl*mult[i]<f.l) nl++;
                    while((nl-1)*mult[i]>=f.l) nl--;
                    nr = f.r/mult[i];
                    while(nr*mult[i]>f.r) nr--;
                    while((nr+1)*mult[i]<=f.r) nr++;
                }
                else {
                    if(f.l<=0 && 0<=f.r) {
                        nl = -1e9;
                        nr = 1e9;
                    }
                    else {
                        nl = 1e9;
                        nr = -1e9;
                    }
                }
                long long ml = max(l[i-1],nl);
                long long mr = min(r[i-1],nr);
                if(ml<=mr) {
                    func mult_f = {f.k*mult[i],f.n,ml,mr};
                    mult_fnc[mult_fncn++]=mult_f;
                }
            }
        }
        else {
            mult[i]*=-1;
            for(long long j=0;j<fncn[1-id][g];j++) {
                func f=fnc[1-id][g][j];
                if(f.l==f.r) {
                    f.n=f.k*f.l+f.n;
                    f.k=0;
                }
                long long nl = f.l/mult[i];
                while(nl*mult[i]<f.l) nl++;
                while((nl-1)*mult[i]>=f.l) nl--;
                long long nr = f.r/mult[i];
                while(nr*mult[i]>f.r) nr--;
                while((nr+1)*mult[i]<=f.r) nr++;
                nl*=-1;
                nr*=-1;
                swap(nl,nr);
                long long ml = max(l[i-1],nl);
                long long mr = min(r[i-1],nr);
                if(ml<=mr) {
                    func mult_f = {-f.k*mult[i],f.n,ml,mr};
                    mult_fnc[mult_fncn++]=mult_f;
                }
            }
            mult[i]*=-1;
        }
        long long p=0;
        long long q=0;
        while(p<add_fncn && q<mult_fncn) {
            if(cmp[id](add_fnc[p],mult_fnc[q])) {
                fnc[id][g^1][fncn[id][g^1]++]=add_fnc[p];
                p++;
            }
            else {
                fnc[id][g^1][fncn[id][g^1]++]=mult_fnc[q];
                q++;
            }
        }
        while(p<add_fncn) {
            fnc[id][g^1][fncn[id][g^1]++]=add_fnc[p];
            p++;
        }
        while(q<mult_fncn) {
            fnc[id][g^1][fncn[id][g^1]++]=mult_fnc[q];
            q++;
        }
    }
    construct_linear(i-1,g^1);
}
int main() {
    scanf("%lld",&t);
    assert(1<=t && t<=10);
    while(t--) {
        scanf("%lld %lld",&n,&s);
        assert(1<=n && n<=40);
        assert(abs(s)<=1000000000);
        for(long long i=0;i<2;i++) {
            npotn[i]=0;
            fncn[0][i]=fncn[1][i]=0;
        }
        for(long long i=0;i<n;i++) {
            scanf("%lld",&mult[i]);
            assert(abs(mult[i])<=1000000000);
        }
        for(long long i=0;i<n;i++) {
            scanf("%lld",&add[i]);
            assert(abs(add[i])<=1000000000);
        }
        for(long long i=0;i<n;i++) {
            scanf("%lld",&l[i]);
            assert(abs(l[i])<=1000000000);
        }
        for(long long i=0;i<n;i++) {
            scanf("%lld",&r[i]);
            assert(abs(r[i])<=1000000000);
        }
        m=n/2;
        npot[0][0]=s;
        npotn[0]=1;
        construct_pot(0,0);
        fnc[0][(n-1)&1][fncn[0][(n-1)&1]++]={1,0,l[n-1],r[n-1]};
        fnc[1][(n-1)&1][fncn[1][(n-1)&1]++]={1,0,l[n-1],r[n-1]};
        construct_linear(n-1,(n-1)&1);
        bool hans=false;
        long long mans=0;
        long long p=0;
        if(npotn[(m+1)&1]>0) {
            p=0;
            for(long long i=0;i<fncn[1][m&1];i++) {
                func f=fnc[1][m&1][i];
                while(p+1<npotn[(m+1)&1] && npot[(m+1)&1][p+1]<=f.r) p++;
                long long x = npot[(m+1)&1][p];
                if(f.l<=x && x<=f.r) {
                    if(!hans || f.k*x+f.n>mans) {
                        hans=true;
                        mans=f.k*x+f.n;
                    }
                }
            }
            reverse(npot[(m+1)&1],npot[(m+1)&1]+npotn[(m+1)&1]);
            p=0;
            for(long long i=0;i<fncn[0][m&1];i++) {
                func f=fnc[0][m&1][i];
                while(p+1<npotn[(m+1)&1] && npot[(m+1)&1][p+1]>=f.l) p++;
                long long x = npot[(m+1)&1][p];
                if(f.l<=x && x<=f.r) {
                    if(!hans || f.k*x+f.n>mans) {
                        hans=true;
                        mans=f.k*x+f.n;
                    }
                }
            }
        }
        if(!hans) printf("nemoguce\n");
        else printf("%lld\n",mans);
    }
    return 0;
}

```
