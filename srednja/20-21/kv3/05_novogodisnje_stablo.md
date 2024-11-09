---
hide:
  - toc
---

# 5 - Novogodišnje stablo

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Jovan je odlučio da okiti stablo koje mu raste u dvorištu za novu godinu. Jovanovo stablo ima $N$ čvorova i $N-1$ granu, tako da se od svakog čvora može doći do svakog drugog na jedinstven način korišćenjem nekog skupa grana. Od tih $N$ čvorova, čvor numerisan brojem $1$ je poseban, i njega nazivamo koren stabla. Podstablo čvora $u$ je skup svih čvorova $v$, takvih da $u$ pripada skupu čvorova koji su na putu između čvora $v$ i korena stabla. Specijalno, čvor $u$ pripada podstablu čvora $u$.

Na čvoru $i$ visi ukras boje $b_i$. *Raznobojnost* stabla definišemo kao broj različitih komponenti iste boje. Dva čvora pripadaju istoj komponenti ukoliko je moguće doći od jednog do drugog tako da svi čvorovi na tom putu imaju istu boju (uključujući i početni i krajnji). 

Jovan još uvek nije siguran kako da okiti stablo. On će na stablu izvršiti $Q$ promena oblika:

$u$ $c$ - Jovan će zameniti sve ukrase na čvorovima koji pripadaju podstablu čvora $u$ sa ukrasima boje $c$.

Pomozite Jovanu da okiti stablo i ispišite *raznobojnost* stabla posle svake izmene.

## Opis ulaza
U prvom redu nalaze se brojevi $N$ i $Q$. U narednih $N-1$ linija, nalaze se po dva broja $u$ i $v$, koji predstavljaju grane stabla. U narednoj liniji, nalazi se $N$ brojeva, od kojih je $i$-ti broj $b_i$ - boja ukrasa koji visi na čvoru $i$. U poslednjih $Q$ linija nalaze se po dva broja $u$ i $c$, koji predstavljaju izmene na stablu.

## Opis izlaza
Za svaku od $Q$ izmena ispisati *raznobojnost* stabla posle te izmene.

## Ograničenja
* $1 \leq N, Q \leq 2 \cdot 10^{5}$.
* $1 \leq b_i, u, c \leq N$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 5 poena: $N, Q \leq 10^3$.
* U test primerima vrednim 15 poena: $c = 1$, tj. svaka izmena ima istu boju.
* U test primerima vrednim 15 poena: Postoji grana između $i$ i $i-1$ za svako $2 \leq i \leq N$.
* U test primerima vrednim 20 poena: Postoji grana između $i$ i $\lfloor \frac{i}{2} \rfloor$ za svako $2 \leq i \leq N$.
* U test primerima vrednim 45 poena: Nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
6 4
1 2
1 3
2 4
2 5
3 6
1 2 1 1 3 3
4 3
4 2
1 1
2 2
```

#### Izlaz
```
5
4
1
2
```

#### Objašnjenje
Nakon prve izmene, istobojne komponente se sastoje od čvorova: $\{1,3\},\{2\},\{4\},\{5\},\{6\}$.

Nakon druge izmene, istobojne komponente se sastoje od čvorova: $\{1,3\},\{2,4\},\{5\},\{6\}$.

Nakon treće izmene, istobojne komponente se sastoje od čvorova: $\{1,2,3,4,5,6\}$.

Nakon četvrte izmene, istobojne komponente se sastoje od čvorova: $\{1,3,6\},\{2,4,5\}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Milisavljević | Aleksa Milisavljević | Mladen Puzić | Tadija Šebez |

Nazovimo roditeljem čvora $x$ (koji nije koren) prvi čvor na koji naiđemo kada od $x$ krenemo ka korenu (čvoru $1$). Najbitniji zaključak je onda da je broj komponenti iste boje jednak broju čvorova koji su drugačije obojeni od svog roditelja, plus jedan. Ovakve čvorove ćemo od sad zvati *lepi čvorovi*. Ovo važi, jer ako za svaku komponentu uzmemo čvor koji je najbliže korenu, znamo da je njegov roditelj druge boje. Samim tim postoji bijekcija između broja komponenti i lepih čvorova (plus jedan dodajemo zbog komponente u kojoj se nalazi sam koren).

Na početku, potrebno je da jednim prolaskom kroz stablo nađemo roditelja svakom čvoru (DFS obilaskom iz korena) i izbrojimo koliko na početku ima lepih čvorova. Sada posmatrajmo šta se desi kada podstablo čvora $u$ obojimo bojom $c$. Svi lepi čvorovi unutar strogog podstabla $u$ (podstabla ne računajući čvor $u$) nestaju (jer svi čvorovi u tom podstablu sad imaju istu boju), a sam čvor $u$ je lep čvor ukoliko je $c$ različito od boje njegovog roditelja. 

Skup lepih čvorova možemo održavati na primer koristeći binarno pretraživo stablo (odnosno *set* u C++). Takođe se može koristiti segmentno stablo sa lenjom propagacijom. Za čuvanje podataka o tome koji čvor je koje boje moramo koristiti segmentno stablo sa lenjom propagacijom (ili sličnu strukturu). Ovo ćemo raditi nad DFS obilaskom stabla, odnosno *spljoštenim* stablom. Krajnja vremenska složenost je $O(N+QlogN)$ ili $O((N+Q)logN))$, u zavisnosti od implementacije.

``` cpp title="05_novogodisnje_stablo.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,q;
int col[4*maxn];
int c[maxn];
int par[maxn];
int lb[maxn];
int rb[maxn];
vector<int> a[maxn];
int ord[maxn];
int pos[maxn];
int seg[4*maxn];
int laz[4*maxn];
int cv=1;
void dfs(int u,int p) {
    pos[u]=cv;
    ord[cv]=u;
    lb[u]=rb[u]=cv;
    cv++;
    for(int v:a[u]) {
        if(v!=p) {
            par[v]=u;
            dfs(v,u);
            lb[u]=min(lb[u],lb[v]);
            rb[u]=max(rb[u],rb[v]);
        }
    }
}
void propagate_color(int id,int l,int r) {
    if(col[id]!=0 && l!=r) {
        col[id*2+1]=col[id*2+2]=col[id];
        col[id]=0;
    }
}
int get_color(int id,int l,int r,int x) {
    propagate_color(id,l,r);
    if(l==r) return col[id];
    int m=(l+r)/2;
    if(x<=m) return get_color(id*2+1,l,m,x);
    else return get_color(id*2+2,m+1,r,x);
}
void set_color(int id,int l,int r,int x,int y,int v) {
    propagate_color(id,l,r);
    if(y<l || r<x) return;
    if(x<=l && r<=y) {
        col[id]=v;
        propagate_color(id,l,r);
        return;
    }
    int m=(l+r)/2;
    set_color(id*2+1,l,m,x,y,v);
    set_color(id*2+2,m+1,r,x,y,v);
}
void propagate_val(int id,int l,int r) {
    if(laz[id]==-1) return;
    if(l!=r) {
        laz[id*2+1]=laz[id*2+2]=laz[id];
    }
    seg[id]=laz[id]*(r-l+1);
    laz[id]=-1;
}
void set_val(int id,int l,int r,int x,int y,int v) {
    propagate_val(id,l,r);
    if(y<l || r<x) return;
    if(x<=l && r<=y) {
        laz[id]=v;
        propagate_val(id,l,r);
        return;
    }
    int m=(l+r)/2;
    set_val(id*2+1,l,m,x,y,v);
    set_val(id*2+2,m+1,r,x,y,v);
    seg[id]=seg[id*2+1]+seg[id*2+2];
}
void init_seg(int id,int l,int r) {
    laz[id]=-1;
    if(l==r) {
        col[id]=c[ord[l]];
        if(ord[l]!=1) {
            //cout<<l<<" "<<ord[l]<<" "<<c[par[ord[l]]]<<" "<<c[ord[l]]<<endl;
            if(c[par[ord[l]]]!=c[ord[l]]) seg[id]=1;
        }
        return;
    }
    int m=(l+r)/2;
    init_seg(id*2+1,l,m);
    init_seg(id*2+2,m+1,r);
    seg[id]=seg[id*2+1]+seg[id*2+2];
}
int main() {
    scanf("%d %d",&n,&q);
    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int u=1;u<=n;u++) {
        scanf("%d",&c[u]);
    }
    dfs(1,-1);
    init_seg(0,1,n);
    while(q--) {
        int u,c;
        scanf("%d %d",&u,&c);
        set_color(0,1,n,lb[u],rb[u],c);
        set_val(0,1,n,lb[u],rb[u],0);
        if(u!=1) {
            int v=par[u];
            if(get_color(0,1,n,pos[u])!=get_color(0,1,n,pos[v])) {
                set_val(0,1,n,pos[u],pos[u],1);
            }
        }
        printf("%d\n",seg[0]+1);
    }
    return 0;
}

```
