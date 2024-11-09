---
hide:
  - toc
---

# 5 - Opklada

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 4000ms | 256MB |

Svetsko prvenstvo u fudbalu je glavna tema svih dečačkih priča na velikom odmoru, pa je tako i za trojicu junaka ovog zadatka - Lazara, Momira i Uglješu. Oni svaki dan diskutuju o tome ko je najbolji igrač, najbolja reprezentacija i najbitnije, ko će da pobedi. Međutim, kada se postavi pitanje pobednika nastaju ogromne nesuglasice. Da bi odlučili ko zaista najbolje predviđa rezultate utakmica, dogovorili su se da naprave opkladu.

Svako od njih želi da predvidi gol-razliku u narednih $N\cdot M$ mečeva. Zarad preglednosti predviđanja, Uglješa je napravio svima tablice dimenzije $N\times M$ gde će oni upisivati svoja predviđanja. Naime, u polju $(i,j)$ ($1\le i\le N$, $1\le j\le M$) će napisati koju gol-razliku predviđaju u $(M*(i-1)+j)$-toj utakmici (unapred su fiksirali koji tim je "prvi", tako da gol-razlika može biti i negativna).

Međutim, tajna koju Lazar i Uglješa ne znaju je da Momira baš i ne interesuje fudbal! On nije odgledao nijednu utakmicu svetskog prvenstva, samo je jako dobar u izmišljanju i klimanju glavom.  Zato sad kad treba da zapravo predvidi sam nešto, upao je u ozbiljan problem. Srećom, uspeo je da virne svojim prijateljima u tabele i video Lazarova predviđanja u matrici $l_{i,j}$, a Uglješina u matrici $u_{i,j}$. Momir možda ne zna ništa o fudbalu, ali zna svoje prijatelje, tako da zna da će Lazar sigurno potceniti gol razliku (Lazar uvek ide na najsigurnije opcije), dok će ih Uglješa sigurno preceniti (Uglješu često ponese uzbuđenje).  Stoga, Momir je odlučio da kad napiše njegova predviđanja u matricu $m_{i,j}$ važi $l_{i,j}\le m_{i,j}\le u_{i,j}$. Međutim, kako bi mu ovo pisanje predikcija bilo interesantnije, on je odlučio da pretvori to u igru. Naime, na početku je upisao u svoju tabelu sve nule. On će u jednom potezu ili da poveća sve vrednosti u nekom redu za $1$, ili da smanji sve vrednosti  u nekoj koloni za $1$. Interesuje ga da li je moguće pomoću ovih operacija da napravi predviđanja za koja će važiti $l_{i,j}\le m_{i,j}\le u_{i,j}$, a vaš zadatak je da mu pomognete u tome.

## Opis ulaza
U prvoj liniji ulaza se nalazi broj $T$ koji predstavlja broj test primera. Dalje sledi opis svakog test primera:
U prvom redu se nalaze dva cela broja $N$ i $M$. U narednih $N$ redova se nalaze po $M$ celih brojeva koji predstavljaju Lazareva predviđanja - matricu $l_{i,j}$. U narednih $N$ redova se nalaze po $M$ celih brojeva koji predstavljaju Uglješina predviđanja - matricu $u_{i,j}$.

## Opis izlaza
Za svaki primer treba dati odgovor, i to odvojen novim redom. Ukoliko nije moguće da Momir napravi svoja predviđanja da ispunjavaju uslove zadatka, potrebno je samo ispisati "NE" (bez navodnika).  U suprotnom treba ispisati "DA" (bez navodnika) i u narednih $N$ redova ispisati po $M$ brojeva koji predstavljaju Momirova predviđanja. Ukoliko postoji više rešenja, ispisati bilo koje.

## Primer 1
### Ulaz
```
2
2 2
1 -2
0 -3
4 0
1 -2
2 2
0 0
0 1
0 0
0 1
```

### Izlaz
```
DA
1 -2
1 -2
NE
```

## Objašnjenje primera
U prvom slučaju ako primenimo operaciju na oba reda po jednom, kao i tri operacije na drugu kolonu, dobijamo ispisanu matricu, a ona ispunjava tražene nejednakosti, pa je validno rešenje ispisano. U drugom slučaju je moguće dokazati da ne postoji rešenje.

## Ograničenja

- $1 \leq T \leq10$
-  $1\leq N\leq 300$
-  $-2\times10^9\le l_{i,j}\le u_{i,j}\le2\times10^9$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 15 poena: $N,M\le10$ i $u_{i,j}-l_{i,j}\le1$ za svako $1\le i\le N$, $1\le j\le M$.
- U testovima vrednim 10 poena: važi $l_{i,j}=u_{i,j}$ za svako $1\le i\le N$, $1\le j\le M$.
- U testovima vrednim 15 poena: važi $l_{i,j}=u_{i,j}$ za sva polja kada je $i=1$ ili $j=1$.
- U testovima vrednim 15 poena:  važi $l_{i,j}=u_{i,j}$ za sva polja gde su $i$ i $j$ iste parnosti.
- U testovima vrednim 45 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Milisavljević |

## Rešenje kada je $l_{i,j}=u_{i,j}$
Neka je $c_i$ broj operacija koje smo primenili na $i$-tu kolonu, a $r_i$ broj operacija koje smo primenili na $i$-ti red. Preimtimo da je onda $m_{i,j}=r_{i}-c_{j}$. iz ovoga možemo da zaključimo da je $m_{i,j}=r_{i}-c_{j}=r_{i}+r_{1}-c_{j}-c_{1}-m_{1,1}=(r_i-c_1)+(r_1-c_j)+m_{1,1}=m_{i,1}+m_{1,j}-m_{1,1}$. Može se bez većih poteškoća dokazati da je ovaj uslov potreban i dovoljan uslov za Momirovu krajnju tabelu (suštinski rešavanjem sistema jednačina za $r_i$ i $c_i$). Tako da je potrebno samo proveriti uslov i nalazimo rešenje u $O(TNM)$.

## Rešenje kada je $l_{i,j}=u_{i,j}$ u prvom redu i koloni
Iz prethodnog podzadatka možemo da vidimo zapravo da pošto su nam fiksirani prvi red i kolona da nam je ostatak tabele fiksrian. Onda samo izračunamo koje vrednosti moraju da se nalaze na kraju u svakom polju i proverimo da li je u traženom intervalu. Složenost:  $O(TNM)$.

## Rešenje kada je $u_{i,j}-l_{i,j}\leq1$ i $N,M<=10$
U ovom podzadatku, koristimo rešenje prethodnog. Naime primetimo da za vrednosti u prvom redu i koloni imamo najviše $2^{M+N-1}$ opcija. Fiksiramo svaku od tih opcija i probamo algoritmom sličan onome u prethodnom podzadatku (sa potencijalno nekim odsecanjem zbog ubrzanja). Složenost:  $O(T2^{M+N}NM)$

## Rešenje kada je $l_{i,j}=u_{i,j}$ u svim belim poljima
Vratimo se na interpretaciju $m_{i,j}=r_{i}-c_{j}$. Vidimo da nam polje gde je $l_{i,j}=u_{i,j}$ daje jedinstvenu vezu između $r_{i}$ i $c_{j}$. Zbog uslova ovog zadatka, sve vrednosti $r_i$ i $c_i$ ćemo moći da izrazimo samo preko $r_1$ ili samo preko $r_2$. Kada se te veze ispune i ubace u nejednačine ostalih polja, onda će sva preostala polja da nam daju neke nejednačine oblika $a\le r_1-r_2\le b$. Kombinujući ove nejednakosti po svim poljima, nalazimo u kom intervalu  $r_1-r_2$ zaista treba da bude (kao presek svih gorenavedenih intervala), i odatle možemo da uzmemo proizvoljnu vrednosti. Na kraju pustimo algoritam iz trećeg podzadatka (drugom u ovom tekstualnom rešenju), da bismo videli da li je validno rešenje to koje smo našli.

## Rešenje bez dodatnih ograničenja
Primetimo da nam se uslovi u suštini svode na $l_{i,j}\leq r_i-c_j\leq u_{i,j}$. Prezapišimo ovo kao $r_i-c_j\leq u_{i,j}$ i $c_j-r_i\leq-l_{i,j}$. Sada smo sveli zadatak: na rešavanje sistema nejednačina po promenljivima $x_1,x_2\cdots,x_{M+N}$ gde je svaka nejednačina oblika $x_i-x_j\leq c$. Postoji generalni način na koji se ovo rešava koji ćemo prezentovati ovde.

Napravimo graf čiji čvorovi odgovaraju promenljivima našeg sistema nejednačina. Napravimo za svaku nejednačinu oblika $x_i-x_j\leq c$ granu od čvora $j$ do čvora $i$ sa težinom $c$. Pustićemo algoritam Belman-Ford, da bismo našli distancu od $1$ do svakog drugog čvora u ovom grafu. Tvrdimo da ukoliko u našem grafu postoji negativan ciklus, odgovor je da rešenje ne postoji, dok ako ne postoji negativan ciklus, rešenje uvek postoji i nalatimo ga kao $x_i=dist(1,i)$. Ukoliko postoji negativan ciklus, onda neka je to ciklus $a_1,a_2,\cdots,a_k$. Tada za njih imamo neke nejednakosti oblika $x_{a_i}-x_{a_{i+1}}\leq c_{i}$ (indeksi uzeti po modulu $k$). Sada kad saberemo ove jednačine, svaki od promenljivih nam se skrati i dobijamo $0\leq c_1+c_2+\cdots+c_k<0$ (jer je u pitanju negativan ciklus). Iz ovoga zaključujemo da kad ima negativan ciklus, rešenje zaista ne postoji. Sada pretpostavimo da negativan ciklus ne postoji. Dokažimo da je $x_i=dist(1,i)$ zaista rešenje. Treba da se uverimo da je $dist(1,i)-dist(1,j)\leq c$, odnosno $dist(1,j)+c\geq dist(1,i)$, što je svakako tačno jer je desna strana najkraći put od $1$ do $i$, dok leva strana predstavlja neki put od $1$ do $i$, gde prvo idemo do $j$ a onda od $j$ do $i$ direktnom granom težine $c$. Ovime smo se uverili da je ovo zaista rešenje.

Najzad da bismo finiširali zadatak, potrebno je dati dve fusnote na prethodni algoritam. Prva je da su neke vrednosti promenljivih možda negativne, a nama trebaju samo pozitivne vrednosti. Ovo, međutim, nije problem jer možemo svim promenljivama da dodamo neko $k$ da bi smo dobili opet validno rešenje sistema, gde su sve promeljive veće za $k$, pa za dovoljno veliko $k$ i pozitivne. Druga bitna stvar je da rešenje ovakvog sistema jednačina, u generalnom slučaju, ne mora biti samo od celih brojeva. Međutim, zbog načina koji smo našli rešenja, to jest kao najkraći put u nekom grafu gde su težine svih grana cele, onda će ovo rešenje koje smo detektovali u gornjem algoritmu ipak biti validno.

Ovime smo rešili zadatak u $O(TNM(N+M))$.

``` cpp title="05_opklada.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 307
using namespace std;
long long ev[2*MAXN*MAXN],d[2*MAXN],dist[2*MAXN],l[MAXN][MAXN],u[MAXN][MAXN];
int ep[2*MAXN*MAXN],ek[2*MAXN*MAXN],br,a;
void bellman_ford_iter() {for(int i=0;i<br;i++) d[ek[i]]=min(d[ek[i]],d[ep[i]]+ev[i]);}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m; br=0;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++)
        {
            scanf("%d",&a);
            l[i][j]=a;
            ep[br]=i;
            ek[br]=n+j;
            ev[br++]=-a;
        }
        for(int i=0;i<n;i++) for(int j=0;j<m;j++)
        {
            scanf("%d",&a);
            ep[br]=n+j;
            ek[br]=i;
            ev[br++]=a;
        }
        d[0]=0;
        for(int i=1;i<n+m;i++) d[i]=1000000000000000000LL;
        for(int i=0;i<n+m;i++) bellman_ford_iter();
        for(int i=0;i<n+m;i++) dist[i]=d[i];
        bellman_ford_iter();
        bool fail=false;
        for(int i=0;i<n+m;i++) if(d[i]!=dist[i]) fail=true;
        if(fail) {printf("NE\n"); continue;}
        printf("DA\n");
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++) printf("%lld ",d[i]-d[n+j]);
            printf("\n");
        }
    }
}

```
