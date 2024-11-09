---
hide:
  - toc
---

# 5 - Zlatnici 3

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 800ms | 256MB |

Savez Čarobnjačkih Bankara (SČB) ima mrežu banaka povezanih portalima, tačnije minimalnim brojem portala potrebnih da se od svake banke može doći u svaku drugu banku (portali su skupi za održavanje, pa graf banaka predstavlja stablo), u kojima čuvaju zlatnike. Pomoću ovih portala mogu slati zlatnike iz jedne banke do druge, portalom koji ih povezuje, ali za jedno prebacivanje jednog zlatnika kroz jedan portal, potreban im je jedan kristal timpestina, retkog minerala, koji se koristi kao gorivo za ovaj proces. Savez želi u svakom trenutku da bude spreman za nepredviđene okolnosti, i to na sledeći način: plan je da se u slučaju uzbune svi zlatnici prebace u jednu banku, kako bi se svi čarobnjaci ujedinili u njihovoj zaštiti. Pri tome želimo da ovo uradimo tako da potrošimo najmanje kristala timpestina, sa obzirom da je on jako dragocen. Kako su ovi bankari čarobnjaci, a ne programeri, i kako ljudi stalno dolaze i stavljaju novac u banku, oni ne umeju dovoljno brzo da izračunaju u koju banku bi trebalo prebaciti sve zlatnike u slučaju uzbune. Pomozite im i odredite u koju banku je najbolje prebaciti sve resurse u bilo kom trenutku!

## Opis ulaza
U prvom redu standardnog ulaza nalazi broj $N$,  broj banaka. 
U narednih $N-1$ redova se nalaze po dva cela broja $x_i$ i $y_i$, u opsegu od $1$ do $N$, koji predstavljaju povezanost banke $x_i$ i $y_i$ portalom.
U sledećem redu nalazi se $N$ brojeva, početni broj zlatnika u svakoj banci.
U narednom redu se nalazi $Q$, broj upita.
U sledećih $Q$ redova nalaze se po dva broja $z_i$ i $b_i$, koji predstavljaju dolazak osobe koja stavlja $z_i$ zlatnika u banku $b_i$.

## Opis izlaza
Ispisati $Q+1$ brojeva. Prvi broj je optimalna banka u koju treba prebaciti  sve zlatnike ako dođe do uzbune pre dolaska prvog čoveka koji prilaže novac, dok su narednih $Q$ brojeva indeksi optimalnih banaka nakon dolazaka svakog od zalagača redom, to jest nakon svakog od upita. Ako ima više optimalnih banaka, ispisati onu sa najmanjim indeksom.

## Primer 1
### Ulaz
```
5
1 2
2 3
3 4
4 5
1 1 1 1 1
2
8 5
6 2
```

### Izlaz
```
3
5
4
```

## Primer 2
### Ulaz
```
4
1 2
1 3
1 4
1 1 1 100
0
```

### Izlaz
```
4
```

## Objašnjenje primera
Prvi primer:

- Pre dolaska prvog čoveka banka $3$ je optimalna i trebalo bi nam $6$ kristala da sve zlatnike prebacimo u nju.
- Nakon dolaska prvog čoveka banka $5$ postaje optimalna, i trebalo bi nam $10$ kristala da sve zlatnike prebacimo u nju.
- Nakon dolaska drugog čoveka banka $4$ postaje optimalna, i treba nam $15$ kristala ako želimo da prebacimo sve zlatnike u nju.

Drugi primer:

- Pošto u poslednjoj banci ima ubedljivo najviše zlatnika, jasno je da je neisplativo da ih premeštamo iz nje.

## Ograničenja

- $1 \leq N,Q \leq200.000$, početni broj zlatnika u svakoj banci je bar 1.

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 15 poena: $N \leq 1000, Q=0$.
- U testovima vrednim 15 poena: $Q=0$.
- U testovima vrednim 20 poena: Svaka banka je povezana sa najviše dve druge banke.
- U testovima vrednim 20 poena: Graf banaka predstavlja kompletno binarno stablo.
- U testovima vrednim 30 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Marko Šišović | Pavle Martinović | Pavle Martinović |

##  Rešenje u $O(QN^2)$
Pokušajmo da pronađemo za svaki čvor $u$ koliko treba poteza da bismo sve zlatnike preneli u njega. Ovo je suma $\sum_{i=1}^nd(u,i)\cdot w_i$, gde $w_i$ broj zlatnika u $i$, a $d(u,v)$ dužina puta između čvorova $u$ i $v$. Ovo se lako može izračunati puštanjem DFS iz svakog čvora.

##  Rešenje u $O(QN)$
Potrebno je da malo dublje analiziramo koji čvor će biti odgovor. Neka sa $V_v$ označavamo broj poteza koji je potreban da bi svi zlatnici stigli u čvor $v$. Potrebno je naći čvor tako da je $V_u=\sum_{i=1}^nd(u,i)\cdot w_i$ minimalno. Posmatrajmo vrednost $V_u-V_v$ za neku granu $uv$. Iz gorenavedene formule vidimo da je ovo zapravo jednako razlici suma težina u dva stabla koja dobijemo kada isečemo granu $uv$ (uverite se!). Kada smo u optimalnom čvoru, ova vrednost treba da bude negativna za sve grane, što je ekvivalentno sa tim da kad isečemo taj čvor, u svakom od dobijenih stabala je najviše pola od ukupne težine (ovakav čvor se zove centroidom stabla). Sada lako se vidi da je ovakav čvor jedinstven, ili ih je dva koja su spojena granom sa razlikom renjenja od $0$ (a u tom slulaju su oba validno rešenje). Stoga, sveli smo zadatak na traženje šta je centroid u ovom stablu, što može da se uradi DFS i čuvaju se veličine svih podstabala, a zatim se uradi jednostavna provera.

## Rešenje kada je stablo put
U ovom slučaju je rešenje ternarno pretraživo po putu, i sve dist funkcije se mogu izračunati lako. Moguće je uraditi tad u zadatak $O(N\log N + Q\log^2 N)$, za jednu tačku pretrage u ternarnoj nam treba samo sume po prefiksima i sufiksima, a promeni tih možemo da pratimo u segmentnom stablu. 

## Rešenje kada je stablo kompletno binarno
Nastavljamo na rešenje iz drugog podzadatka. Ono što treba primetiti je da je vrednost $V_v-V_u$ moguće izračunati brzo za neku granu. Zaista ako smestimo čvorove u niz po ulaznom ili izlaznom poretku DFS, i imamo segmentno stablo nad tim nizom, pošto će svi čvorovi u nekom stablu formirati interval. Nama je potrebna samo težina u dva stabla koja dobihemo kad isečemo ovu granu, a jedno od tih stabala će morati da bude podtablo ukorenjenog stabla. Težinu u drugom možemo izračunati kao ukupna težina minus to što smo izračunali. Stoga, promenu rezultata prolaskom iz jednog čvora u drugi, (to jest da li je bolje ako pređemo) možemo izračunati u $O(\log N)$.

Sada kad dodamo novi čvor, novo rešenje će se nalaziti na putu od trenutnog rešenja do tog novog na koji smo dodali zlatnike. Stoga, na tom putu će promene rezultata biti pozitivne, pa negativne. Da bismo rešili zadatak potrebno je samo iterirati kroz put i naći sve grane kroz koje kad prođemo poboljšavamo rezultat. Pošto su na ovom stablu svi putevi kratki, nalazimo rešenje u $O(N\log N + Q\log^2 N)$.

## Glavno rešenje
Konačno rešenje je mala nadogradnja prethodnog. Naime, umesto da idemo redom po putu između starog i novog čvora, uraidmo binarnu pretragu na tom putu da bismo pronašli poslednju granu koja nam daje pozitivan skor na rezultat. Po svemu opisanom u prethodnom podzadatku, ovo će zaista biti binarno pretraživo i stoga će ovo rešenje raditi u $O(N\log N + Q\log^2 N)$.

``` cpp title="05_zlatnici3.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define MAXQ 200005
#define MAXLOGN 20

int n,q;
vector<int> graph[MAXN];
bool visited[MAXN];
int dfsInd1[MAXN], dfsInd2[MAXN], parent[MAXN];
long long totalSum;

long long bitArr[MAXN];
long long nodeCoins[MAXN];

long long bitGetSum(int idx){
    long long sum=0;
    for(int i=idx;i>0;i-=(i&-i)){
        sum+=bitArr[i];
    }
    return sum;
}

void bitUpdate(int idx, int val){
    for(int i=idx;i<=MAXN;i+=(i&-i)){
        bitArr[i]+=val;
    }
}

long long getSubtrSum(int node){
    return bitGetSum(dfsInd2[node]-1) - bitGetSum(dfsInd1[node]-1);
}
void updateNode(int node, int val){
    bitUpdate(dfsInd1[node], val);
    nodeCoins[node]+=val;
    totalSum+=val;
}

int lg[2*MAXN];
pair<int,int> sparseTable[MAXLOGN][2*MAXN];
int first[MAXN];
vector<int> euler;
vector<pair<int,int>> heights;
int height[MAXN];
int par[MAXLOGN][MAXN];

int findLCA(int a, int b){
    int l=first[a], r=first[b];
    if(r<l){
        swap(l,r);
    }
    int i = lg[r - l + 1];
    pair<int,int> minimum = min(sparseTable[i][l], sparseTable[i][r - (1 << i) + 1]);
    return euler[minimum.first];
}

int dfsCnt;
void dfs(int cur, int hg, int parent){
    par[0][cur] = parent;
    height[cur]=hg;
    euler.push_back(cur);
    heights.push_back({hg, euler.size()-1});
    first[cur]=euler.size()-1;
    dfsInd1[cur]=dfsCnt++;
    visited[cur]=true;
    for(auto i:graph[cur]){
        if(!visited[i]){
            dfs(i, hg+1, cur);
            euler.push_back(cur);
            heights.push_back({hg, euler.size()-1});
        }
    }
    dfsInd2[cur]=dfsCnt;
}

int findCentroid(int cur, int last){
    long long curSum = getSubtrSum(cur);
    long long curVal = nodeCoins[cur];
    int maxNode=-1;
    long long maxVal = 0;
    for(auto i:graph[cur]){
        if(i==last){
            continue;
        }
        long long potentialVal = getSubtrSum(i);
        if(maxNode==-1 || maxVal<potentialVal){
            maxVal = potentialVal;
            maxNode = i;
        }
    }
    if(maxVal<=totalSum/2){
        if(totalSum%2==0 && maxVal==totalSum/2){
            return min(cur, maxNode);
        }
        return cur;
    }
    return findCentroid(maxNode, cur);
}

int bsNode;

bool bsCondition(int curCentroid, int changedNode, int lca, int leftPathLen, int rightPathLen, int m){
    if(m==0){
        return true;
    }
    long long vertexVal, potNode;
    if(m<=leftPathLen){
        m--;
        potNode = curCentroid;
        while(m>0){
            potNode = par[lg[m]][potNode];
            m-=(1<<lg[m]);
        }
        vertexVal = totalSum - 2*getSubtrSum(potNode);
        if(vertexVal==0 && par[0][potNode]<potNode){
            vertexVal++;
        }
        potNode = par[0][potNode];
    }
    else{
        m -= leftPathLen;
        m = rightPathLen - m;
        potNode = changedNode;
        while(m>0){
            potNode = par[lg[m]][potNode];
            m-=(1<<lg[m]);
        }
        vertexVal = 2*getSubtrSum(potNode)-totalSum;
        if(vertexVal==0 && par[0][potNode]>potNode){
            vertexVal++;
        }
    }
    if(vertexVal>0){
        bsNode = potNode;
    }
    return (vertexVal>0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n-1;i++){
        int in1,in2;
        cin>>in1>>in2;
        graph[in1].push_back(in2);
        graph[in2].push_back(in1);
    }

    dfsCnt=1;
    dfs(1,0,1);

    for (int i = 2; i < 2*MAXN; i++){
        lg[i] = lg[i/2] + 1;
    }
    for (int j = 0; j < heights.size(); j++){
        sparseTable[0][j]=heights[j];
    }
    for (int i = 1; i < MAXLOGN; i++){
        for (int j = 0; j + (1 << i) < heights.size(); j++){
            sparseTable[i][j] = min(sparseTable[i - 1][j], sparseTable[i - 1][j + (1 << (i - 1))]);
        }
    }
    for(int i=1;i<MAXLOGN;i++){
        for(int j=1;j<=n;j++){
            par[i][j]=par[i-1][par[i-1][j]];
        }
    }

    for(int i=1;i<=n;i++){
        int in;
        cin>>in;
        updateNode(i,in);
    }

    totalSum = getSubtrSum(1);
    int curCentroid = findCentroid(1,0);
    cout<<findCentroid(1,0)<<"\n";

    cin>>q;
    for(int i=0;i<q;i++){
        int in1, in2;
        cin>>in2>>in1;
        updateNode(in1,in2);
        int changedNode = in1;
        int lca = findLCA(curCentroid, changedNode);
        int pathLen = height[curCentroid] + height[changedNode] - 2*height[lca];
        int leftPathLen = height[curCentroid] - height[lca];
        int rightPathLen = height[changedNode] - height[lca];
        bsNode = curCentroid;
        int l=-1, r = pathLen+1;
        while(r - l > 1){
             int m = (l + r) / 2;
             if(bsCondition(curCentroid, changedNode, lca, leftPathLen, rightPathLen, m)){
                l = m;
             }
             else{
                r = m;
             }
        }
        curCentroid = bsNode;
        cout<<curCentroid<<"\n";
    }
}

```
