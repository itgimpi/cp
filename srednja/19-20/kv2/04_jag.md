---
hide:
  - toc
---

# 4 - JAG

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |


_JAG™_ je nova revolucionarna strateška igra kompanije "Najbolji ltd.".


U igri postoji $N$ teritorija. Neke dve teritorije mogu deliti granicu. Poznato je da ukupno $N-1$ parova teritorija dele granicu, na takav način da su sve teritorije povezane, tj. od bilo koje teritorije je moguće doći do bilo koje druge, potencijalno prelazeći preko drugih teritorija.


Igru igraju dva igrača, i na početku partije oni biraju svoje teritorije. Teritorije biraju naizmenično prvi pa drugi igrač. Svako od njih izabere tačno jednu teritoriju koju do sada ni jedan igrač nije izabrao. Ovo se dešava sve dok postoji teritorija koju ni jedan igrač nije izabrao.

*Raštrkanost* teritorija prvog igrača jednaka je udaljenosti dve njegove najdalje teritorije (tačnije broju granica preko kojih je neophodno preći na najkraćem putu između te dve teritorije). Prvi igrač želi da minimizuje raštrkanost svojih teritorija, dok drugi igrač želi da maksimizuje taj broj (raštrkanost teritorija prvog igrača).


Ispisati ovu vrednost pri optimalnoj igri oba igrača.


## Opis ulaza

U prvom redu nalazi se broj $N$, broj teritorija u igri.
U narednih $N-1$ redova nalaze se po dva broja $u$ i $v$, koja označavaju da $u$ i $v$ dele granicu.

## Opis izlaza

U jedinom redu standardnog izlaza ispisati jednu vrednost, *raštrkanost* teritorija prvog igrača pri optimalnoj igri oba igrača.

## Primer 1

### Ulaz

```
5
1 2
1 3
1 4
1 5
```

### Izlaz

```
2
```

## Primer 2

### Ulaz

```
4
1 2
2 3
3 4
```

### Izlaz

```
1
```

## Objašnjenje primera 1
Kako god da prvi igrač igra, mora izabrati bar dve teritorije iz skupa $\{2,3,4,5\}$. Između bilo koje dve od njih je rastojanje dva.

## Ograničenja
* $3 \leq N \leq 10^{5}$
* $1 \leq u, v \leq n$

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena: $N \leq 10$.
* U test primerima vrednim 10 poena: Teritorije $i$ i $i+1$ dele granicu, za svako $i$ za koje važi $1 \leq i < N$.
* U test primerima vrednim 20 poena: $N \leq 10^3$.
* U test primerima vrednim 50 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Aleksa Milisavljević | Dragan Urošević | Nikola Milosavljević |

Skup teritorija možemo reprezentovati kao neorijentisan graf, u kome su čvorovi baš tih $N$ teritorija, a grane postoje između parova teritorija koje dele zajedničku granicu.  Taj graf je povezan (jer je od bilo koje teritorije moguće doći do bilo koje druge, potencijalno prelazeći preko drugih teritorija). Kako ima tačno $N-1$ grana (jer toliko ima parova teritorija koje dele granicu), to taj graf predstavlja stablo (povezan graf u kome nema petlji/ciklusa). 

Dijametar stabla je dužina puta između dva najudaljenija čvora (udaljenost se računa kao dužina najkraćeg puta, tj. broj grana na najkraćem putu). Označimo sa $D$ dijametar grafa. 
Primetimo da ako postoje bar $4$ teritorije takve da je rastojanje između svake dve jednako dijametru $D$, onda drugi igrač može igrati tako da prvi igrač mora obojiti bar dve od te četiri teritorije i zbog toga je tada raštrkanost teritorija prvog igrača jednaka $D$. Ali raštrkanost će biti jednaka $D$ i ako se mogu izdvojiti dve (disjunktne) grupe teritorija (neka su to $A$ i $B$) koje imaju po bar dva elementa tako da je rastojanje između svake teritorije iz prve grupe i svake teritorije iz druge grupe jednako dijametru $D$. Naime, i u tom slučaju, drugi igrač može igrati tako da prvi igrač mora obojiti po jednu teritoriju iz svake od dveju grupa (misli se na grupe $A$ i $B$) i tada je raštrkanosti jednaka $D$. 

Šta ako stablo (graf) ne zadovoljava gornje uslove? Neka su $u$ i $v$ čvorovi koji su na rastojanju $D$. Pretpostavimo da postoji bar još jedan čvor koji je na rastojanju $D$ od bar jednog od čvorova (neka je čvor $w$ na rastojanju $D$ od čvora $u$). Tada se mogu izdvojiti dve (disjunktne) grupe $A$ i $B$ (od kojih jedna ima samo jedan element, inače bi u suprotnom mogli primeniti razmatranje iz prethodnog odeljka) takve da je rastojanje između svaka dva čvora iz te dve grupe jednako dijametru $D$. U ovom slučaju rezultat zavisi od parnosti broja teritorija. Ako je broj teritorija neparan, prvi igrač "izvodi'' poslednji potez i zbog toga drugi igrač može igrati tako da prvi igrač mora obojiti po jednu teritoriju ia svake od dveju grupa, pa je raštrkanost jednaka $D$. Ako je broj teritorija paran, onda prvi igrač može igrati tako da ne uzme teritoriju koja se nalazi u grupi sa samo jednom teritorijom. Zbog toga je raštrkanost jednaka $D-1$.

Ako nije važio ni prethodni uslov, onda postoje tačno dve teritorije koje su na rastojanju $D$ (neka su to $u$ i $v$). U tom slučaju se određuje koliko ima teritorija koje su na rastojanju $D-1$ od jedne (ili obe) od ove dve teritorije i izvodi se slično razmatranje kao u prethodna dva odeljka sa jedinom razlikom što će sada raštrkanost biti $D-1$ ili $D-2$ zavisno od broja teritorija koje su na rastojanju $D-1$ od teritorija $u$ i $v$ (kao i od parnosti broja $N$, ako postoji po tačno jedna teritorija koja je na rastojanju $D-1$ od svake teritorija $u$ i $v$).

Za kraj kako odrediti dijametar grafa? Jedan od načina je primenom dva obilaska u dubinu uz određivanje rastojanja svakog od čvorova stabla od polaznog čvora). Prvi obilazak kreće od proizvoljnog čvora $w$, a drugi od čvora $u$ koji je na najvećem rastojanju od čvora $w$. Neka je čvor $v$ na najvećem rastojanju od čvora $u$. Može se pokazati da je rastojanje između čvorova $u$ i $ v$  jednako dijametru stabla.   

Složenost opisanog algoritma je $O(N)$.


``` cpp title="04_jag.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 2000000
using namespace std;
int n;
vector<int> a[maxn];
int d[2][maxn];
stack<pair<int,int> > st;
void dfs(int u,int id) {
    st.push({u,-1});
    d[id][u]=0;
    while(st.size()>0) {
        u=st.top().first;
        int par=st.top().second;
        st.pop();
        for(auto v:a[u]) {
            if(v!=par) {
                d[id][v]=d[id][u]+1;
                st.push({v,u});
            }
        }
    }
}
int main() {
    int u,v;
    scanf("%d",&n);
    for(int i=0;i<n-1;i++) {
        scanf("%d %d",&u,&v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1,0);
    int x=1;
    for(int i=1;i<=n;i++) {
        if(d[0][i]>d[0][x]) x=i;
    }
    for(int i=1;i<=n;i++) d[0][i]=0;
    dfs(x,0);
    int y=1;
    for(int i=1;i<=n;i++) {
        if(d[0][i]>d[0][y]) y=i;
    }
    dfs(y,1);
    int diam = d[0][y];
    int p=0,q=0,r=0,p1=0,q1=0,r1=0;
    for(int i=1;i<=n;i++) {
        if(d[0][i]==diam && d[1][i]==diam) r++;
        else {
            if(d[0][i]==diam) p++;
            if(d[1][i]==diam) q++;
        }
        if(d[0][i]==diam-1 && d[1][i]==diam-1) r1++;
        else {
            if(d[0][i]==diam-1) p1++;
            if(d[1][i]==diam-1) q1++;
        }
    }
    if(n==2) {
        printf("0");
        return 0;
    }
    if(p>1 || q>1 || r>0) {
        if((p>=2 && q>=2) || (p+r>=2 && q>=2) || (p>=2 && q+r>=2) || r>=2) printf("%d",diam);
        else {
            if(n%2==0) printf("%d",diam-1);
            else printf("%d",diam);
        }
    }
    else {
        if((p1>=2 && q1>=2) || (p1+r1>=2 && q1>=2) || (p1>=2 && q1+r1>=2) || r1>=2) printf("%d",diam-1);
        else {
            if(n%2==0) printf("%d",diam-2);
            else printf("%d",diam-1);
        }
    }
    return 0;
}

```
