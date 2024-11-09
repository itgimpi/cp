---
hide:
  - toc
---

# 2 - Nameštanje granice

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Glasa se za granicu za prolaz na državno takmičenje iz atletike. Svi članovi komisije će napisati na papirić neki broj, koji će potom ubaciti u kutiju za glasove. Granica će se odrediti tako što će se uzeti medijana svih glasova koji su ubačeni u kutiju.

Kada je najpopularniji član komisije Markos, poznatiji kao „bog i batina“ došao da glasa, primetio je da niko ne obraća pažnju na kutiju sa glasovima. Odlučio je da, nakon što ostatak komisije glasa, dođe i proviri u kutiju, otkrije šta su ostali članovi komisije glasali i zatim napiše onoliko glasova koliko je minimalno potrebno da granica bude baš broj $X$ koji je on zamislio.

Posmatramo $Q$ scenarija gde je u $i$-tom scenariju broj koji je Markos zamislio $B[i]$. Pomozite Markosu da za svaki scenario otkrije koliko minimalno glasova mora da ubaci u kutiju za glasove. Glasovi koji su već bili u kutiji su dati nizom $A$, dužine $N$.

## Opis ulaza
U prvom redu standardnog ulaza se nalaze dva pozitivna cela broja $N$ i $Q$. U drugom redu se nalazi niz celih brojeva $A$. U trećem redu se nalazi niz celih brojeva $B$.

## Opis izlaza
Za svaki scenario ispisati rešenje u novom redu.

## Primer 1
### Ulaz
```
5 3
1 3 5 7 9
5 7 10
```

### Izlaz
```
0
1
5
```

## Objašnjenja primera
U prvom scenariju medijana je već 5 te je odgovor 0. U drugom scenariju Markos može da ubaci glas sa brojem 8 da bi medijana postala 7 te je odgovor 1. Konačno, u trećem scenariju, neophodno je da Markos ubaci još najmanje pet glasova sa brojem 10 ili više, da bi medijana postala 10, te je odgovor 5.

## Ograničenja

* $1 \leq N, Q \leq 2*10^5$
* $0\leq A[i] \leq 10^9$ za svako $0 \leq i < N$
* $0\leq B[i] \leq 10^9$ za svako $0 \leq i < Q$ 

Test primeri su podeljeni u četiri disjunktne grupe:

* U testovima vrednim 25 poena: $Q = 1$.
* U testovima vrednim 25 poena: Svaki broj $X$ koji je Markos zamislio će biti već nečiji glas.
* U testovima vrednim 25 poena: $N,Q \leq 1000$.
* U testovima vrednim 25 poena: Bez dodatnih ograničenja.

## Napomena
Neka je dat niz $A$ sa $N$ članova. Kao medijana ovog niza se uzima član koji bi se našao u sredini kada bi se niz $A$ sortirao. Formalnije, neka je $A^\prime$ niz koji se dobija kada se niz $A$ sortira. Neka je $A^\prime$ indeksiran od $1$. Medijana niza $A$ se definiše kao element $A^\prime[\lfloor\dfrac{N}{2}\rfloor + 1]$. Na primer, ukoliko je $A = [5,7,3,6]$, niz $A^\prime$ bi bio $[3,5,6,7]$, a medijana bi imala vrednost $6$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Toni Škrijelj | Dragan Urošević | Vladimir Milovanović |

## Glavno rešenje
Pretpostavimo da je niz $A$ sortiran u neopadajućem poretku, da je ukupan broj elemenata niza $N$ i da su elementi niza indeksirani brojevima od $0$ do $N-1$. Tada je medijana niza element sa indeksom $N/2$ (pri čemu se računa celobrojni deo količnika). Neka je $B$ broj poena koji Markos želi kao granicu. Tada razlikujemo tri slučaja:

* Ako je $A[N/2] = B$, onda je medijana već jednaka broju $B$ i Markos glasa $0$ puta.

* Ako je $B$ $<$ $A[N/2]$ određujemo indeks $i$ poslednjeg elementa koji nije veći od $B$ (ako takav ne postoji, onda je $i=-1$). Tada postoji  $i+1$ elemenata koji su manji od ili jednaki $B$ i $N-i-1$ elemenata koji su veći od $B$, pri čemu je $i+1 \leq N-i-1$. Da bi obezbedili da $B$ bude medijana potrebno je da grupa manjih ili jednakih ima bar jedan element više od grupe većih, pa je potrebno ubaciti $N-i-1-(i+1)+1 = N-2i-1$ glasova.
* Ako je $B>A[N/2]$ određujemo indeks $i$ prvog elementa koji nije manji od $B$ ( ako takav ne postoji, onda je $i=N$). Tada postoji  $i$ elemenata koji su manji od $B$ i $N-i$ elemenata koji su veći od ili $B$, pri čemu je $i \geq N-i$. Da bi obezbedili da $B$ bude medijana potrebno je da grupa većih ili jednakih ima bar onoliko elementa koliko ima manjih, pa je potrebno ubaciti $i - (N - i) = 2i-N$ glasova.

Složenost algoritma je određena složenošću sortiranja (koja može biti $\Theta(N\log N)$) i složenošću pronalaženja poslednjeg elementa koji nije veći od $B$, odnosno prvog elementa koji nije manji od $B$. Ako ovo realizujemo kao sekvencijalno pretraživanje, složenost dela koji se odnosi na određivanje odgovora na pitanja će biti $\Theta(QN)$, pa će ukupna složenost biti $\Theta(N\log N + NQ)$. Ako pronalaženje opisanog elementa realizujemo korišćenjem binarne pretrage (koju svakako možemo koristiti, ako smo niz sortirali), onda je složenost određivanja odgovora na pitanja $\Theta(Q\log N)$, pa je složenost kompletnog algoritma $\Theta((N+Q)\log N)$.





``` cpp title="02_namestanje_granice.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
const int mxN=2e5;
int a[mxN];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q; cin >> n >> q;
    for(int i=0; i<n; i++) cin >> a[i];
    sort(a,a+n);
    for(int i=0; i<q; i++)
    {
        int x; cin >> x;
        int mn=lower_bound(a,a+n,x)-a;
        int mx=upper_bound(a,a+n,x)-a;
        int l=-1, r=1e6;
        while(r-l>1)
        {
            int m=(l+r)/2;
            if((n+m)/2>=mn&&(n+m)/2<=mx-1+m) r=m;
            else l=m;
        }
        cout << r << "\n";
    }
}

```
