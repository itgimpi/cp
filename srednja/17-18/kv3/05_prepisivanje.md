---
hide:
  - toc
---

# 5 - Prepisivanje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2500ms | 512MB |

Godina je $3018$. Takmičenja iz programiranja u Srbiji su nikad veća, imamo stotine hiljada takmičara, i stotine hiljada rundi kvalifikacija, a takmičari još uvek prepisuju jedni od drugih, i ne poštuju pravilnik.

Komisija je spremna kao i uvek, i unajmila je stotine hiljada članova koji će nadgledati prepisivanje. Svaki član Komisije ima zaduženu rundu od koje će početi nadgledanje, i normu koju treba da ispuni - **tj. broj različitih takmičara koje treba da uhvati u prepisivanju.** Član komisije vrši nadgledanje u svim rundama počev od zadate početne runde, dok god ne ispuni zadatu normu.

Za svakog takmičara su date runde u kojima je prekršio pravilnik, a vas molimo da pomognete Komisiji i za svakog člana odgovorite koliko najmanje rundi zaredom treba da posmatra da bi ispunio normu (norma će uvek biti takva da se može ispuniti).

Svaki član komisije će uhvatiti sve takmičare koji su prepisivali u rundi koju nadgleda. Takođe, više članova komisije mogu uhvatiti istog takmičara u istoj rundi.

Komisija je odlučila i da vam oteža posao tako što će vam informaciju o zaduženju svakog člana dati u zavisnosti od rešenja (minimalnog broja posmatranih rundi) za prethodnog člana - obratite pažnju na opis ulaza i pojašnjenja primera u ovom zadatku.

## Opis ulaza
U prvoj liniji standardnog ulaza nalaze se dva broja $N$ i $R$ odvojena razmakom - broj takmičara i broj rundi kvalifikacija.
U svakoj od sledećih $N$ linija se nalazi prvo broj $P_i$ - broj rundi u kojima je $i$-ti takmičar prepisivao, pa zatim $P_i$ različitih brojeva odvojenih razmakom koji označavaju runde u kojima je $i$-ti takmičar prepisivao.
Zatim, u sledećem redu se nalazi broj $K$ - broj unajmljenih članova komisije.
U sledećih $K$ redova se nalaze po dva broja odvojena razmakom - $T_i$ i $S_i$ koji označavaju zaduženje $i$-tog člana komisije na sledeći način:

> Ako je $MP_i$ minimalan broj rundi koji $i$-ti član komisije treba da posmatra, onda će $Start_i = T_i + MP_{i-1}$ biti runda u kojoj $i$-ti član treba započeti nadgledanje. $S_i$ označava normu $i$-tog člana. Uzima se da je $MP_0 = 0$, dok indeksiranje za članove komisije počinje od 1. Obratite pažnju da $T_i$ može biti i negativan broj, ali će dobijeni $Start_i$ uvek biti od $1$ do $R$.

## Opis izlaza
Na standardni izlaz ispisati $K$ linija - u svakoj liniji redom brojeve $MP_i$ - koji označavaju minimalan broj rundi koje $i$-ti član komisije treba da posmatra.

## Primer 1
### Ulaz
```
6 12
3 1 2 5
2 3 4
3 1 2 7
2 3 6
0
3 3 11 12
3
1 2
0 5
1 5
```

### Izlaz
```
1
3
8
```

## Primer 2
### Ulaz
```
5 5
1 2
1 3
1 4
1 5
2 1 2
3
1 5
-2 3
-1 2
```

### Izlaz
```
5
3
1
```

## Objašnjenje primera
U prvom primeru, prvi član komisije započinje nadgledanje od prve runde, treba da ispuni normu $2$, i odmah u prvoj rundi hvata dva takmičara ($1$. i $3$.), što znači da nadgleda samo $1$ rundu. Drugi član komisije počinje nadgledanje takođe od prve runde $(Start_2 = T_2 + MP_1 \implies Start_2 = 0 + 1 = 1)$, i potrebno je da uhvati $5$ takmičara u prepisivanju. Za to je dovoljno da nadgleda $3$ runde (takmičari $1$ i $3$ prepisuju u prvoj, dok takmičari $2$, $4$ i $6$ prepisuju u trećoj rundi). Treći član komisije započinje nadgledanje od četvrte runde, i potrebno je da uhvati $5$ takmičara u prepisivanju. Za to je potrebno da nadgleda sve runde do jedanaeste.

U drugom primeru, obratite pažnju da $T_i$ može biti negativan broj na ulazu, ali uzimajući u obzir rešenja za prethodne članove komisije, drugi član komisije će nadgledanje početi od $3$. runde, dok će treći član komisije nadgledanje započeti od $2$. runde.

## Ograničenja

* $1 \leq N,R,K \leq 300 000$.
* $1 \leq \sum_{i=1}^n P_i \leq 300 000$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede $25$ poena važi $1 \leq N,R,K,\sum_{i=1}^n P_i \leq 10^4$.
* U test primerima koji vrede $25$ poena važi $1 \leq N,R,K,\sum_{i=1}^n P_i \leq 10^5$.
* U test primerima koji vrede $25$ poena važi $S_i = S_j,  \forall(i,j | 1 \leq i,j \leq K)$, tj. svi članovi komisije imaju istu normu.
* U test primerima koji vrede $25$ poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Tadija Šebez | Ivan Stošić |

## Podzadatak 1
Složenost $O(K\sum^{N}_{i=1} S_i)$. Za svaku rundu treba imati listu takmičara koji su na njoj prepisivali. Svaki upit rešavamo tako što krenemo od početne runde i brojimo one takmičare koje smo prvi put uhvatili.

## Offline rešenje
Potrebno nam je segmentno stablo. Da bi rešili sve upite kojima je početna runda $S$ za svakog takmičara koji je prepisivao na nekoj od rundi iѕ segmenta $[S,R]$ treba da na vrednost prve runde na kojoj će biti uhvaćen dodamo $1$. Da bi efikasno izgradili strukturu treba da rešavamo prvo sve upite sa $S=R$ pa $S=R-1$ itd. Kada je $S=R$ vrednost $R$ u stablu biće jednaka broju ljudi koji su prepisivali na toj rundi. Za ostale $S$ nije dovoljno samo postaviti vrednost na broj ljudi koji su prepisivali na toj rundi već moramo i da smanjimo vrednost nekih od sledećih rundi. Ako je takmičar $X$ prepisivao na trenutnoj rundi i na nekoj od sledećih treba da smanjimo vrednost sledeće runde na kojoj je prepisivao. Ovako u svakom koraku imamo opisano segmentno stablo. Upite rešavamo binarnom pretragom po rešenju uz pomoć segmentnog stabla. Složenost ovog algoritma je $O(K\log^2 R)$.

## Podzadatak 2
Ovaj podzadatak se rešava tako što umesto običnog segmentnog stabla koristimo *persistent segment tree*. Tako možemo pristupiti prethodnim verzijama segmentnog stabla i posle cele izgradnje. Vremenska složenost ostaje $O(K\log^2 R)$, a memorijska se povećava na $O((\sum^{N}_{i=1} S_i)\log R)$.

## Podzadatak 3

Ovaj podzadatak zahteva više razmišljanja. Potrebno je smanjiti složenost *Offline* rešenja sa $O(K\log^2 R)$ na $O(K\log R)$. Primetimo da segmentno stablo već ima izračunate vrednosti za neke segmente. To možemo koristiti umesto binarne pretrage. Započnimo rekurzivni algoritam u korenu stabla. Ako je vrednost levog segmenta veća ili jednaka broju takmičara koje član komisije treba da uhvati pomeramo se na levo podstablo, ako ne pomeramo se na desno podstablo i pamtimo da smo uhvatili onoliko takmičara kolika je bila vrednost levog segmenta. Na kraju ovog algoritma nalazimo se u listu koji predstavlja rešenje upita.

## Podzadatak 4

Ovaj podzadatak se rešava primenom podzadataka $2$ i $3$, odnosno koristimo *persistent segment tree* i opisani algoritam na njemu da bi smanjili vremensku složenost na $O(K\log R)$ dok memorijska složenost ostaje $O((\sum^{N}_{i=1} S_i)\log R)$.

## Zadaci za vežbu

Ovaj trik nije ništa novo u takmičarskom programiranju. Postoji dosta zadataka koji se rešavaju na sličan način. Korisni mogu biti [ovaj](http://codeforces.com/contest/899/problem/F) (radi se isto kao podzadatak $2$) i [ovaj](http://codeforces.com/problemset/problem/786/C) (zahteva *persistent segment tree* i trik za smanjenje složenosti). 

``` cpp title="05_prepisivanje.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;

#define MAXNODES 12555333
#define MAXN 755333

int n,len;
int p[MAXN],rnd[MAXN],niz[MAXN],tstart[MAXN],tkraj[MAXN];
vector<int> r[MAXN];

int zadnjiput[MAXN];

int num_nodes;
int levi_sin[MAXNODES], desni_sin[MAXNODES], uk_suma[MAXNODES];
int per_time[MAXNODES];

int new_node() {
    num_nodes++;
    levi_sin[num_nodes] = -1;
    desni_sin[num_nodes] = -1;
    uk_suma[num_nodes] = 0;

    return num_nodes;
}

void ubaci(int last_node, int curr_node, int left, int right, int pos, int value) {

    if (last_node != -1) {
        levi_sin[curr_node] = levi_sin[last_node];
        desni_sin[curr_node] = desni_sin[last_node];
    }

    if (left == right) {
        uk_suma[curr_node] = value;
        return;
    }

    int mid = (left+right)/2;
    if (pos <= mid) {
        int nd = new_node();
        ubaci(levi_sin[curr_node], nd, left, mid, pos, value);
        levi_sin[curr_node] = nd;
    } else {
        int nd = new_node();
        ubaci(desni_sin[curr_node], nd, mid+1, right, pos, value);
        desni_sin[curr_node] = nd;
    }

    uk_suma[curr_node] = (levi_sin[curr_node] != -1 ? uk_suma[levi_sin[curr_node]] : 0) +
                         (desni_sin[curr_node] != -1 ? uk_suma[desni_sin[curr_node]] : 0);
}

int query_sum(int curr_node, int left, int right, int sum) {
    if (left == right) return left;

    int mid = (left+right)/2;

    if (levi_sin[curr_node] == -1) return query_sum(desni_sin[curr_node], mid+1, right, sum);
    if (desni_sin[curr_node] == -1) return query_sum(levi_sin[curr_node], left, mid, sum);

    if (uk_suma[levi_sin[curr_node]] >= sum) {
        return query_sum(levi_sin[curr_node], left, mid, sum);
    } else {
        return query_sum(desni_sin[curr_node], mid+1, right, sum - uk_suma[levi_sin[curr_node]]);
    }
}

void init_tree() {

    int nd,tak,last_root;

    for(int i=1; i<=n; i++) {
        zadnjiput[i] = -1;
    }

    last_root = -1;
    for(int i=len; i>=1; i--) {
        tak = niz[i];
        if (zadnjiput[tak] != -1) {
            nd = new_node();
            ubaci(last_root, nd, 1, len, zadnjiput[tak], 0);
            last_root = nd;
        }

        zadnjiput[tak] = i;

        nd = new_node();
        ubaci(last_root, nd, 1, len, i, 1);
        last_root = nd;

        per_time[i] = last_root;
    }
}

int main() {

    //freopen("01.in", "r", stdin);
    //freopen("01.out", "w", stdout);

    int N,R,K,i,j,rj,ti,si,st,zd,tak,last_res;

    scanf("%d%d", &N, &R);

    n = N;

    for(i=1; i<=N; i++) {
        scanf("%d", &p[i]);
        for(j=0; j<p[i]; j++) {
            scanf("%d", &rj);
            r[rj].push_back(i);
        }
    }

    len = 0;

    for(i=1; i<=R; i++) {
        tstart[i] = len+1;
        for(j=0; j<r[i].size(); j++) {
            tak = r[i][j];
            len++;
            rnd[len] = i;
            niz[len] = tak;
        }
        tkraj[i] = len;
    }

    init_tree();

    scanf("%d", &K);

    last_res = 0;
    for(i=0; i<K; i++) {
        scanf("%d%d", &ti, &si);

        st = ti+last_res;

        zd = query_sum(per_time[tstart[st]], 1, len, si);

        last_res = rnd[zd]-st+1;
        printf("%d\n", last_res);
    }

    return 0;
}


```
