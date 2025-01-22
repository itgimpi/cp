---
hide:
  - toc
---

# 5 - Noćna vožnja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 4000ms | 256MB |


U zemlji Bajtoviji nalazi se $N$ naselja, označenih različitim celim brojevima od $1$ do $N$. Postoji $N-1$ puteva između nekih naselja, tako da je moguće stići od bilo kog naselja do bilo kog drugog koristeći te puteve (tj. Bajtovija je oblika *stabla*). Rastojanje dva naselja je dužina najkraćeg puta između ta dva naselja.

U bazi podataka Javnog Komunalnog Preduzeća *Putevi Bajtovije* sva naselja nalaze se poređano nekim redosledom $p_i$ (označava da je $i$-to naselje u redu naselje $p_i$).

U jednom trenutku krenule su da se dešavaju čudne stvari u dva oblika:

 - $1$ $a$ $b$, administratori baza podataka zamenili su u redosledu $p_a$ i $p_b$.
 - $2$ $l$ $r$ $x$, hakeri su upali u sistem i ucenjuju administratore. Traže im odgovor na pitanje: koliko je daleko naselje $x$ od najdaljeg od naselja $p_l, p_{l+1}, \ldots, p_r$. 

Administratori baza podataka Javnog Komunalnog Preduzeća *Putevi Bajtovije* vas mole za pomoć da odgovorite na pitanja hakera. 

## Opis ulaza
U prvom redu standardnog ulaza nalazi se prirodan broj $N$ - broj naselja. U drugom redu nalazi se $N$ celih brojeva, redosled naselja na spisku. Narednih $N-1$ redova sadrže dva broja $u$ i $v$, označavajući da postoji put između naselja numerisanih $u$ i $v$. 

Naredni red sadrži prirodni broj $Q$, broj događaja. Svaka od narednih $Q$ linija sadrži ili $1$ $a$ $b$ - označavajući događaj prvog tipa - ili $2$ $l$ $r$ $x$ - označavajući događaj drugog tipa. 

## Opis izlaza
Za svaki događaj drugog tipa potrebno je ispisati u zasebnom redu standardnog izlaza odgovor na pitanje ucenjivača.

## Primer

### Ulaz

```
5
5 4 1 2 3
1 2
2 3
1 4
2 5
5
2 3 4 5
1 3 5
2 3 4 5
1 2 4
2 3 4 5
```

### Izlaz

```
2
2
3
```
## Objašnjenja primera
Prvi događaj: najdalje naselje od naselja $5$ na datom intervalu je naselje $1$, na rastojanju $2$.

Drugi događaj: zamena pozicije naselja $1$ i $3$.

Treći događaj: najdalje naselje od naselja $5$ na datom intervalu je naselje $3$, na rastojanju $2$.

Četvrti događaj:  zamena pozicije naselja $4$ i $2$. 

Peti događaj: najdalje naselje od naselja $5$ na datom intervalu je naselje $4$, na rastojanju $3$.

## Ograničenja
-   $1 \leq N, Q \leq 80.000$
-   $1 \leq p_i \leq N$ i $p_i \neq p_j$ za $i \neq j$
- $1 \leq a, b, x, u, v \leq N$ i $a \neq b$
- $1 \leq l \leq r \leq N$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $N, Q \leq 4000$.
-   U test primerima vrednim $15$ poena: Svako naselje je susedno sa najviše dva druga naselja.
-   U test primerima vrednim $25$ poena: U svakom događaju važiće $x = 1$ i $p_a, p_b \neq 1$   
-   U test primerima vrednim $25$ poena: Nema događaja oblika $1$.
-   U test primerima vrednim $25$ poena: Bez dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić i Pavle Martinović | Tadija Šebez | Tadija Šebez |

## Podzadatak kada je $N, Q \leq 4000$

Možemo da održavamo trenutni redosled naselja u nizu. Operacija zamene se svodi na jednostavno zamenjivanje dva člana niza, dok je odgovaranje na drugi tip događaja malo komplikovanije. Možemo da pustimo **DFS** ili **BFS** algoritam iz naselja $x$ kako bismo našli udaljenosti od istog do svakog drugog naselja. Nakon što smo našli i sačuvali udaljenosti možemo da prođemo kroz deo niza od $l$ do $r$ i nađemo najveću udaljenost. Vremenska složenost ovog rešenja je $O(QN)$.

## Podzadatak kada je svako naselje susedno sa najviše dva druga naselja

U ovom slučaju naselja zapravo formiraju lanac i možemo da ih poređamo u niz počevši od jednog kraja. Za svako naselje zapamtimo njegovu poziciju u ovom nizu. Kada tražimo najveću udaljenost od naselja $x$ do skupa naselja od $l$ do $r$ bitna su nam samo dva naselja iz tog skupa, naselje sa najmanjom i naselje sa najvećom pozicijom (udaljenošću od kraja lanca). Ovo možemo efikasno da implementiramo korišćenjem neke strukture podataka koja podržava upite za minimum/maksimum na podnizu i promenu člana niza. Na primer možemo da koristimo **segmentno stablo** i dobijemo vremensku složenost $O(N + QlogN)$.

## Podzadatak kada je u svakom događaju $x = 1$ i $p_a, p_b \neq 1$

Kako se u svakom pitanju traži najveća udaljenost od naselja 1, na početku pustimo **DFS** ili **BFS** algoritam iz ovog naselja i nađimo uzaljenosti do svakog drugog naselja. Čuvajmo niz gde je $i$-ti član udaljenost od naselja 1 do naselja $p_i$. Pitanja se svode na traženje maksimuma na podnizu ovog niza. Možemo i ovde da iskoristimo **segmentno stablo** za efikasne operacije traženja maksimuma i promene u nizu nakon događaja prvog tipa. Vremensa složenost je $O(N + QlogN)$.

## Rešenje bez dodatnih ograničenja

Slično kao kod rešenja za lanac za svako pitanje možemo da nađemo dva naselja od kojih će uvek jedno biti najdalje bez obzira na odabir naselja $x$. Za ovo rešenje treba nam malo teorije vezane za stabla. Prečnik stabla je najveća udaljenost između dva čvora, a krajevi prečnika su čvorovi koji su na toj najvećoj udaljenosti. Korisna osobina prečnika stabla je to da je najdalji čvor od proizvoljnog čvora uvek jedan od krajeva prečnika. Naselja koja ćemo tražiti su krajevi prečnika podstabla koje obuhvata naselja $p_l, p_{l+1}, \dots, p_r$. I u ovom rešenju možemo koristiti segmentno stablo. Za svaki segment čuvajmo krajeve prečnika, a prečnik za dva spojena segmenta tražimo tako što nađemo najveću udaljenost između 2 od 4 čvora koji su krajevi prečnika levog i desnog segmenta. Ostaje još da nađemo način kako efikasno da nađemo udaljenost između dva čvora. Možemo da postavimo čvor 1 kao koren i izračunamo dubinu svakog čvora $depth(x)$. Distanca između dva čvora $x$ i $y$ je $depth(x) + depth(y) - 2 depth(LCA(x, y))$, gde je $LCA(x, y)$ najmanji zajednički predak čvorova $x$ i $y$, odnosno čvor na kom se put od $x$ do korena i put od $y$ do korena sreću. Najmanji zajednički predak može se naći u $O(logN)$ sa **binary lifting** tehnikom ili u $O(1)$ sa **sparse tabelom** nad Ojlerovim putem. Preprocesiranje za obe opcije je vremenske i memorijeske složenosti $O(NlogN)$, a celo rešenje vermenske složenosti $O(NlogN + Q log^2 N)$ ili $O(NlogN + QlogN)$ u zavisnosti od odabrane tehnike.

``` cpp title="05_nocna_voznja.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 80007
#define MAXL 17
using namespace std;
int d[MAXN],p[MAXL][MAXN],t,in[MAXN],out[MAXN],n,per[MAXN];
vector<int> g[MAXN];
void dfs(int s,int f,int dub)
{
    d[s]=dub;
    p[0][s]=f;
    in[s]=t++;
    for(int i=0;i<g[s].size();i++) if(g[s][i]!=f) dfs(g[s][i],s,dub+1);
    out[s]=t++;
}
void lcainit()
{
    dfs(1,1,0);
    for(int j=1;j<MAXL;j++) for(int i=1;i<=n;i++) p[j][i]=p[j-1][p[j-1][i]];
}
bool insub(int u,int v) {return in[u]<=in[v] && out[u]>=out[v];}
int lca(int u,int v)
{
    if(insub(u,v)) return u;
    if(insub(v,u)) return v;
    for(int i=MAXL-1;i>=0;i--) if(!insub(p[i][u],v)) u=p[i][u];
    return p[0][u];
}
int dist(int u,int v) {return d[u]+d[v]-2*d[lca(u,v)];}
pair<int,int> mojmax(pair<int,int> a, pair<int,int> b)
{
    if(dist(a.first,a.second)<dist(b.first,b.second)) return b;
    return a;
}
pair<int,int> sga(int a,int b,int c,int d)
{
    if(a==-1) return {c,d};
    if(c==-1) return {a,b};
    pair<int,int> res={a,b};
    res=mojmax(res,{a,c});
    res=mojmax(res,{a,d});
    res=mojmax(res,{b,c});
    res=mojmax(res,{b,d});
    res=mojmax(res,{c,d});
    return res;
}
pair<int,int> seg[4*MAXN];
void upd(int l,int r,int v,int w,int ind)
{
    if(l==r) {seg[ind]={v,v}; return;}
    int s=(l+r)/2;
    if(w<=s) upd(l,s,v,w,2*ind);
    else upd(s+1,r,v,w,2*ind+1);
    pair<int,int> lv=seg[2*ind],ds=seg[2*ind+1];
    seg[ind]=sga(lv.first,lv.second,ds.first,ds.second);
}
pair<int,int> mp(int l,int r,int lt,int rt,int ind)
{
    if(l>=lt && r<=rt) return seg[ind];
    if(r<lt || l>rt) return {-1,-1};
    int s=(l+r)/2;
    pair<int,int> lv=mp(l,s,lt,rt,2*ind),ds=mp(s+1,r,lt,rt,2*ind+1);
    return sga(lv.first,lv.second,ds.first,ds.second);
}
int main()
{
    int q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&per[i]);
    for(int i=1;i<n;i++)
    {
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        g[t1].push_back(t2);
        g[t2].push_back(t1);
    }
    lcainit();
    for(int i=1;i<=n;i++) upd(1,n,per[i],i,1);
    scanf("%d",&q);
    while(q--)
    {
        int type;
        scanf("%d",&type);
        if(type==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            swap(per[x],per[y]);
            upd(1,n,per[x],x,1);
            upd(1,n,per[y],y,1);
        }
        else
        {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);
            pair<int,int> p=mp(1,n,l,r,1);
            printf("%d\n",max(dist(x,p.first),dist(x,p.second)));
        }
    }
}

```
