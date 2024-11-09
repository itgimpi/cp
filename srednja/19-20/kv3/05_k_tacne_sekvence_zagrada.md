---
hide:
  - toc
---

# 5 - K-tačne sekvence zagrada

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 5000ms | 64MB |


Tačnu sekvencu zagrada definišemo na sledeći način:
- Prazna sekvenca je tačna sekvenca zagrada.
- Ako je $A$ tačna sekvenca zagrada, onda je i `(`$A$`)` tačna sekvenca zagrada.
- Ako su $A$ i $B$ tačne sekvence zgrada, onda je i njihova konkatenacija, $AB$, tačna sekvenca zagrada.

$K$-tačna sekvenca zagrada je sekvenca zagrada takva da se može dobiti tačna sekvenca zagrada nakon što se obriše $K$ ili manje zagrada iz originalne sekvence.
Dato je $Q$ upita od kojih svaki ima sledeći oblik: Naći $T$-tu po redu leksikografski najmanju $K$-tačnu sekvencu zagrada dužine $N$, ako se uzima da je `(` leksikografski manje od `)`.

## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se broj $Q$. U narednih $Q$ linija, nalaze se po 3 cela broja $N, K, T$.

## Opis izlaza

Za svaki od $Q$ upita ispisati traženu sekvencu zagrada ili "Ne postoji" ako tražena sekvenca zagrada ne postoji.

## Primer 1

### Ulaz

```
6
1 1 1
1 1 2
1 1 3
3 1 1
4 4 9
8 0 2
```

### Izlaz

```
(
)
Ne postoji
(()
)(((
((()()))
```

## Ograničenja

- $1\leq Q,N\leq1000$
- $0\leq K\leq100$
- $1\leq T<2^{60}$

Test primeri su podeljeni u 5 disjunktnih grupa:

- U test primerima vrednim 10 poena: $N\leq 8$.
- U test primerima vrednim 10 poena: $K=N$.
- U test primerima vrednim 10 poena: $K=0$.
- U test primerima vrednim 20 poena: $N\leq100$.
- U test primerima vrednim 50 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Pešić | Nikola Pešić | Nikola Pešić | Ivan Stošić |

## Ideja za  dinamičko programiranje
Za rešavanje problema koristićemo dinamičko programiranje.
Neka $dp[i][v][k]$ prstavlja $dp$ stanje gde $i$ označava broj zagrada koje još moramo da postavimo, $v$ označava trenutnu prefiksnu sumu postavljenih zagrada (ako uzmemo da je `(` jednako 1 a `)` jednako -1) i $k$ predstavlja broj zagrada koje možemo još da obrišemo.
Za prelaze imamo 2 opcije: Postavi `(` kao sledeću zagradu ili postavi `)` kao sledeću zagradu.
Ako postavljamo `(`, iz stanja $dp[i][v][k]$ ćemo preći u stanje $dp[i-1][v+1][k]$.
Ako postavljamo `)` imamo 2 opcije: 
- $v=0$, iz stanja $dp[i][0][k]$ ćemo preći u stanje $dp[i-1][0][k-1]$.
- $v>0$, iz stanja $dp[i][v][k]$ ćemo preći u stanje $dp[i-1][v-1][k]$.

Na početku treba da inicijalizujemo $dp[0][v][k]$ na $1$ ako je $v<=k$, a na $0$ u ostalim slučajevima.
Takođe treba paziti na $overflow$, vrednosti u $dp$-u veoma brzo mogu da premaše $long~long$, tako da je potrebno ograničiti ih da ne mogu da budu veće od $2^{61}$ ili neke slične vrednosti. $2^{61}$ je dobra vrednost jer $2\cdot 2^{61}$ idalje staje u $long~long$, dok je $2^{61}$ veće od najveće moguće vrednosti za $t$.
Uz pomoć ovog $dp$-a, možemo da odgovorimo na upite. Za upit $n,k,t$ ćemo krenuti od stanja $dp[n][0][k]$ i nakon toga ćemo raditi sledeće dok $n$ ne postane $0$ :
- Ako je $dp[n-1][v+1][k]\geq t$, preći ćemo u to stanje i na odgovor dodati `(`.
- U suprotnom ćemo od $t$ oduzeti $dp[n-1][v+1][k]$, na odgovor dodati `)` i preći u stanje $dp[i-1][0][k-1]$ ako je $v=0$ ili $dp[i-1][v-1][k]$ ako je $v>0$.

Sa ovim rešenjem se moglo dobiti $40$ bodova, dok se sa malo modifikovanim rešenjem (za slučaj kada je $k=0$), moglo dobiti još  $10$ bodova.
Glavni problem ovog rešenja je memorija, tako da ćemo se u sledećem delu fokusirati na smanjenje memorije.
Biće opisana 3 rešenja, u redosledu od najlakšeg do najtežeg za implementaciju. Prvo rešenje je alternativno rešenje za problem, drugo koristi ideju koju je Tadija Šebez koristio da reši problem, i treće je zamišljeno rešenje.

U sva 3 rešenja se koristi klasična memorijska optimizacija gde se čuvaju samo poslednja 2 reda. Ovo je poprilično lako uraditi kada se računa u redosledu rastućih dužina, međutim, za odgovaranje na upite nama trebaju vrednosti u redosledu opadajućih dužina.
## Rešenje 1
Ovo rešenje koristi činjenicu da u našem $dp$-u ima malo vrednosti koje nisu $0$, a manje su od $2^{61}$. Štaviše, ima tačno $2,358,736$ takvih vrednosti. 
Postoje 2 slučaja kada je $dp[i][v][k]=0$:
- $i+k-v<0$
- $k=0$ i $i\not\equiv v\ (\textrm{mod}\ 2)$

Treba nam još dobar način da sačuvamo ove vrednosti. Možemo da napravimo matricu gde za sve vrednosti $i$ i $v$ čuvamo sve vrednosti $k$ (listu vrednosti) i vrednosti odgovarajućeg $dp$ stanja.
Međutim, kako vrednosti $i$ i $v$ mogu biti do $1000$, ova matrica će koristiti previše memorije. Da bi smanjili memoriju, možemo da primetimo da za neku vrednosti parametra $i$, vrednost parametra $v$ će biti u intervalu $[i-k,i+k]$ za sva polja čija je vrednost u traženom intervalu. Time možemo da smanjimo matricu na dimenzije $1000\times 200$.
Što se tiče, pronalaženja odgovarajuće vrednosti za $k$ iz liste, dovoljno je samo da prođemo kroz celu listu ako nam treba neka vrednost iz nje. Ovo je moguće uraditi i u $O(\log{k})$ ali nema potrebe kako složenost programa ostaje ista.
Složenost: Vreme: $O(n^2\cdot k)$, Memorija: $O($Broj polja čija je vrednost u intervalu $(0,2^{61})$ $)$.

## Rešenje 2
U ovom i sledećem rešenju rešavaćemo upite oflajn, tj. rešićemo ih sve jednim prolazom kroz $dp$ tabelu u redosledu opadajućih dužina. Za ovo rešenje definisaćemo konstantu $S$ i u odvojenu tabelu ćemo zapamtiti svaki $S$-ti red, tj. $dp[0][v][k]$, $dp[S][v][k]$, $dp[2\cdot S][v][k]$,...
Nakon toga, prolazimo kroz sve dužine u opadajućem redosledu, i za svaku dužinu $i$ ćemo da dobijemo red koji koji nam treba, tj. $dp[i][v][k]$ tako što ćemo krenuti od najbližeg zapamćenog reda, u ovom slučaju to je $dp[\lfloor\frac{i}{S}\rfloor\cdot S][v][k]$, i pomeriti se $i-\lfloor\frac{i}{S}\rfloor\cdot S$ koraka do $i$-tog reda.
Odabir konstante $S=20$ je dovoljno velik da rešenje prođe memorijsko ograničenje, a dovoljno mali da prođe vremensko ograničenje.
Složenost: Vreme: $O(n^2\cdot k\cdot S)$, Memorija: $O(\frac{n^2}{S}\cdot k)$.

## Rešenje 3
Ovo rešenje se svodi na memorijsku optimizaciju prve dimenzije $dp$ tabele. Ako znamo sve vrednosti za dužinu $i+1$ i prva 2 reda za trenutnu dužinu tj. $dp[i][0][k]$ i $dp[i][1][k]$, možemo da izračunamo sve vrednosti za dužinu $i$. Ovo je moguće uraditi tako što konstruišemo graf svih prelaza i ako znamo neku vrednost u redu $i$, oduzećemo tu vrednost od svih stanja (iz reda $i+1$) sa kojima je to stanje povezano, a ako imamo neko stanje u redu $i+1$ koje je povezano sa tačno jednim stanjem (iz reda $i$) za koje ne znamo vrednost, možemo da zaključimo koja je vrednost tog stanja.
Kako bi ovo radilo, moramo da računamo vrednosti po modulu, moduo $2^{61}$ radi iz istih razloga kao u rešenju 1. Sad nam još treba način da kažemo da li je vrednost u nekom polju zapravo veća od modula ili ne. Za ovo ćemo definisati vrednost $p=i+k-v$, polje $kada[p][k]$ će nam čuvati najmanje $i$ za koje je neko stanje $dp[i][v][k]$ čija je vrednost parametra $p$ odgovarajuća, postalo veće od modula. Primetimo da kad jednom postane veće od modula za neko $i$, vrednost za svako veće $i$ i istom vrednošću parametra $p$ će takođe biti veća od modula.
Ovo je sve što nam treba da rešimo problem, rešavaćemo uptite oflajn, prvo izračunamo vrednosti u predosledu rastućih dužina, popunimo tabelu $kada$ i sačuvamo $dp$ vrednosti za $v=0$ i $v=1$, i odgovorimo na upite za koje je rešenje "Ne postoji". Nakon toga ćemo da izračunamo vrednosti u redosledu opadajućih dužina i odgovorimo na ostale upite.
Složenost: Vreme: $O(n^2\cdot k)$, Memorija: $O(n\cdot k)$.

``` cpp title="05_k_tacne_sekvence_zagrada.cpp" linenums="1"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int K=101,N=1003;
const ll mod=1LL<<61;
bool prebacio;
ll add(ll a,ll b){a+=b;if(a>=mod)a-=mod,prebacio=1;return a;}
ll sub(ll a,ll b){a-=b;if(a<0)a+=mod;return a;}
ll dp[N][K][2],vals[N][2][K]; ///val,k
int kada[N+K][K],degree[N*K],resetin[N*K];
int znam[N*K],jedan[N*K],zn,jed;
bool visited[N*K];
vector<vector<int> > graf(N*K*2);
int getInd(int i,int val,int k){return i*N*K+val*K+k;}
pair<int,int> getState(int val){
    pair<int,int> p;
    if(val>=N*K)
        val-=N*K;
    p.f=val/K;
    p.s=val-p.f*K;
    return p;
}
vector<vector<pair<pair<int,int>,pair<int,ll> > > > events(N);
void init()
{
    for(int i=0;i<N+K;i++)for(int j=0;j<K;j++)kada[i][j]=N;
    for(int i=0;i<K;i++)for(int k=0;k<=i;k++)dp[k][i][0]=1;
    for(int val=0;val<N;val++)
    {
        for(int k=0;k<K;k++)
        {
            if(val<N-1){
                graf[getInd(1,val,k)].pb(getInd(0,val+1,k));
                graf[getInd(0,val+1,k)].pb(getInd(1,val,k));
                degree[getInd(0,val,k)]++;
            }
            if(val!=0)
                graf[getInd(1,val,k)].pb(getInd(0,val-1,k)),graf[getInd(0,val-1,k)].pb(getInd(1,val,k)),degree[getInd(0,val,k)]++;
            else if(k)
                graf[getInd(0,val,k-1)].pb(getInd(1,val,k)),graf[getInd(1,val,k)].pb(getInd(0,val,k-1)),degree[getInd(0,val,k)]++;
        }
    }
    for(int val=0;val<2;val++)
        for(int k=0;k<K;k++)
            vals[0][val][k]=dp[val][k][0];
    for(int i=0;i<N*K;i++)
        resetin[i]=degree[i];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    int t;
    cin >> t;
    vector<string> ans(t);
    vector<pair<pair<int,int>,pair<int,ll> > > qu(t); ///n,i,k,s;
    for(int i=0;i<t;i++)
        cin >> qu[i].f.f >> qu[i].s.f >> qu[i].s.s,qu[i].f.s=i;
    sort(all(qu));
    int j=0;
    for(int i=1;i<N;i++) ///Izracunaj DP na gore, popuni vals i kada, odgovori na querije koji su "Ne postoji"
    {
        for(int val=0;val<N;val++)
            for(int k=0;k<K;k++)
            {
                int pos=i+k-val;
                if(pos<0)
                    continue;
                if(val<N-1)
                    dp[val][k][i&1]=dp[val+1][k][i&1^1];
                else
                    dp[val][k][i&1]=0;
                if(pos>1)
                    kada[pos][k]=min(kada[pos][k],kada[pos-2][k]);
                prebacio=0;
                if(val!=0)
                    dp[val][k][i&1]=add(dp[val][k][i&1],dp[val-1][k][i&1^1]);
                else if(k){
                    dp[val][k][i&1]=add(dp[val][k][i&1],dp[val][k-1][i&1^1]);
                    if(pos>1)
                        kada[pos][k]=min(kada[pos][k],kada[pos-2][k-1]);
                }
                if(prebacio&&kada[pos][k]==N)
                    kada[pos][k]=i;
                if(val<2)
                    vals[i][val][k]=dp[val][k][i&1];
            }
        while(j<t&&qu[j].f.f==i)
        {
            int pos=i+qu[j].s.f;
            if(kada[pos][qu[j].s.f]==N&&dp[0][qu[j].s.f][i&1]<qu[j].s.s)
                ans[qu[j].f.s]="Ne postoji";
            else
                events[qu[j].f.f].pb({{0,qu[j].s.f},{qu[j].f.s,qu[j].s.s}});
            j++;
        }
    }
    for(int i=N-3;i>=0;i--) ///Izracunaj DP na dole, odgovori na ostale upite
    {
        for(int j=0;j<N*K;j++)
            degree[j]=resetin[j];
        memset(visited,0,sizeof(visited));
        for(int val=0;val<2;val++)
            for(int k=0;k<K;k++)
            {
                int pos=i+k-val;
                if(pos<0)
                    continue;
                dp[val][k][i&1]=vals[i][val][k];
                znam[zn++]=getInd(0,val,k);
            }
        while(zn||jed)
        {
            while(zn)
            {
                int val,k,tr=znam[--zn];
                visited[tr]=1;
                auto p=getState(tr);
                val=p.f;
                k=p.s;
                for(auto p:graf[tr])
                {
                    degree[p-N*K]--;
                    auto d=getState(p);
                    dp[d.f][d.s][i&1^1]=sub(dp[d.f][d.s][i&1^1],dp[val][k][i&1]);
                    if(degree[p-N*K]==1)
                        jedan[jed++]=p;
                }
            }
            while(jed)
            {
                int val,k,tr=jedan[--jed];
                auto p=getState(tr);
                val=p.f;
                k=p.s;
                for(auto p:graf[tr])
                    if(!visited[p])
                    {
                        auto d=getState(p);
                        dp[d.f][d.s][i&1]=dp[val][k][i&1^1];
                        znam[zn++]=p;
                    }
            }
        }
        for(auto p:events[i+1])
        {
            int val=p.f.f,k=p.f.s,in=p.s.f;
            ll s=p.s.s;
            val++;
            int pos=i+k-val;
            if(pos>=0&&(kada[pos][k]<=i||dp[val][k][i&1]>=s))
            {
                events[i].pb({{val,k},{in,s}});
                ans[in]+='(';
                continue;
            }
            s-=dp[val][k][i&1];
            ans[in]+=')';
            val--;
            if(val==0)
                k--;
            else
                val--;
            events[i].pb({{val,k},{in,s}});
        }
    }
    for(int i=0;i<t;i++)
        cout << ans[i] << endl;
    return 0;
}

```
