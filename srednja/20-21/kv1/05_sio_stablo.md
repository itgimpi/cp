---
hide:
  - toc
---

# 5 - SIO stablo

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 3000ms | 256MB |

Kao što svi znamo, vračare mogu da predvide neke nepredvidive događaje kao što je prolazak nekog takmičara na Srpsku informatičku olimpijadu (SIO). Za tu namenu koristi se SIO stablo.

SIO stablo je drvo u dvorištu vračare Miljane (niko nije siguran zašto se ova čudna biljka ne zove SIO drvo). Ovo drvo se sastoji iz $N$ mesta grananja, koje ćemo zvati čvorovima, i $N-1$ grana. Čvorovi su numerisani brojevima od $1$ do $N$. Naravno, moguće je doći od svakog čvora do svih drugih čvorova krećući se samo po granama. Na svakoj grani urezano je po jedno slovo iz skupa $\{\text{"S", "I", "O"}\}$.

Par čvorova $(U, V)$ je SIO par ako je na granama na najkraćem putu (putu koji ne prelazi preko iste grane više puta) između čvorova $U$ i $V$ svako od slova $\text{"S"}$, $\text{"I"}$ i $\text{"O"}$ urezano isti broj puta.

Vračara Miljana tvrdi da će na SIO proći osoba koja uspe da izračuna broj SIO parova čvorova $(U, V)$ za koje važi $1 \leq U < V \leq N$. Napišite program koji izračunava ovaj broj kako biste proverili da li je vračara Miljana u pravu.

## Opis ulaza
U prvom redu ulaza nalazi se jedan ceo broj $N$. U narednih $N-1$ redova nalaze se opisi grana. U svakom redu po dva cela broja $U$ i $V$, i po jedno slovo iz skupa $\{\text{"S", "I", "O"}\}$, razdvojeni razmacima.

## Opis izlaza
Na izlaz ispišite broj SIO parova čvorova $(U, V)$ za koje važi $1 \leq U < V \leq N$.

## Ograničenja
- $1 \leq N \leq 3 \times 10^5$

Test primeri su podeljeni u 5 disjunktnih grupa:

- U test primerima vrednim $8$ poena: slovo $\text{"S"}$ je urezano na tačno jednoj grani.
- U test primerima vrednim $12$ poena: $N \leq 1000$.
- U test primerima vrednim $20$ poena: za svako $1 \leq k < N$ postoji grana između $k$ i $k+1$.
- U test primerima vrednim $20$ poena: za svaki $2 \leq k \leq N$ postoji grana između $k$ i $\lfloor \frac{k}{2} \rfloor$.
- U test primerima vrednim $40$ poena: nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
6
4 1 S
5 6 O
1 5 I
1 2 S
3 1 S
```

#### Izlaz
```
3
```

#### Objašnjenje
Parovi $(2, 6)$, $(3, 6)$, $(4, 6)$ su SIO par.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Tadija Šebez | Tadija Šebez | Igor Pavlović |

## Rešenje kada je $n \leq 1000$
**Vremenska složenost:** $O(N^2)$

Pokrenimo algoritam pretrage u dubinu (**DFS**) od svakog čvora. Čuvajmo koliko se puta koje slovo pojavljuje na trenutnom putu i sa tim informacijama lako možemo da povećamo rešenje za svaki SIO par.

## Rešenje kada je slovo $\text{"S"}$ urezano na tačno jednoj grani
**Vremenska složenost:** $O(N)$

Rešenje je broj puteva dužine 3 na kojima se svako od tri slova pojavljuje po jednom. Pronađimo granu na kojoj je urezano slovo $\text{"S"}$ i zapamtimo njene krajeve. Neka su to čvorovi $U$ i $V$. Prebrojimo koliko ima puteva dužine $2$, čiji je jadan kraj neki od čvorova $U$ i $V$, takve da je na njima urezano po jedno slovo $\text{"I"}$ i $\text{"O"}$. Na rešenje još dodajmo broj parova grana tako da jedna kreće iz $U$, a druga iz $V$ i na jednoj je urezano slovo $\text{"I"}$, a na drugoj slovo $\text{"O"}$.

## Rešenje kada je SIO stablo lanac
**Vremenska složenost:** $O(N log N)$

Napravimo string od svih slova koja se pojavljuju na granama od jednog do drugog kraja lanca, u tom poretku. Rešenje se svodi na broj podstringova u kojima se svako od 3 slova pojavljuje jednak broj puta. Neka je $\text{X(i)}$ broj pojavljivanja slova $X$ u prvih $i$ slova. Za svaki prefiks od dužine $0$ do $N-1$ (imamo $N-1$ grana pa samim tim isto toliko slova), zapamtimo par $P(i) = (\text{S(i)}-\text{I(i)}, \text{S(i)}-\text{O(i)})$. Posmatrajmo podstring od $L$-tog do $R$-tog slova. Ako se slova $\text{S}$ i $\text{I}$ pojavljuju isti broj puta onda mora da važi $(\text{S(R)}-\text{S(L-1)}) - (\text{I(R)}-\text{I(L-1)}) = (\text{S(R)}-\text{I(R)}) - (\text{S(L-1)}-\text{I(L-1)}) = 0$ odnosno prve vrednosti iz parova $P(R)$ i $P(L-1)$ moraju biti jednake. Slično se dobija i da druge vrednosti iz ovih parova moraju biti jednake, odnosno parovi $P(R)$ i $P(L-1)$ moraju biti jednaki. Sada ostaje još da prebrojimo koliko imamo parova prefiksa sa jednakim $P$. Ovo možemo uraditi sortiranjem niza parova ili pomoću $\text{std::map}$. 

## Rešenje kada je SIO stablo kompletno binarno stablo
**Vremenska složenost:** $O(N log^2 N)$

Nađimo prvo za koliko SIO parova se koren stabla nalazi na putu između njih. To moraju biti čvorovi iz različitih podstabala. Slično kao u rešenju za lanac nađimo vrednosti $X(i)$ koliko se puta pojavljuje slovo $X$ na putu od korena do čvora $i$. Takođe za svaki čvor zapamtimo par $P(i) = (\text{S(i)}-\text{I(i)}, \text{S(i)}-\text{O(i)})$. U $\text{std::map}$ zapamtimo koliko se puta koji par pojavljuje u levom podstablu. Za čvor $i$ u desnom podstablu ako ga uparimo sa čvorom $j$ u levom podstablu tako da važi $P(j) = (\text{I(i)}-\text{S(i)}, \text{O(i)}-\text{S(i)})$, svako od tri slova će se pojavljivati isti broj puta na putu između $i$ i $j$. Za svaki čvor $i$ u desnom podstablu pomoću $\text{std::map}$ nađimo koliko ima takvih čvorova $j$ u levom podstablu i to dodajmo na rešenje. Sada kada smo u obzir uzeli sve puteve koji prelaze preko korena stabla, znamo da su svi ostali putevi između čvorova iz istog podstabla pa možemo rekurzivno da rešimo problem za levo i desno podstablo. Podstablo veličine $M$ rešavamo u vremenskoj složenosti $O(M log M)$. Kako je visina stabla $O(log N)$ zbir veličina podstabala je $O(N log N)$ pa je vremenska složenost celog algoritma $O(N log^2 N)$.

## Rešenje za 100 poena
**Vremenska složenost:** $O(N log^2 N)$

Rešenje je slično kao za kompletno binarno stablo. U svakom stablu postoji čvor takav da kada izbrišemo njega i sve njegove grane, svaka povezana komponenta koja ostane mora imati barem dva puta manji broj čvorova nego stablo pre brisanja.  Ovaj čvor se naziva **centroid** i moguće ga je naći pomoću algoritma pretrage u dubinu (**DFS**). Nađimo za koliko SIO parova se centroid nalazi na putu između njih, na sličan način kao u prethodnom rešenju, zatim obrišimo centroid i sve njegove grane. Rekurzivno rešimo problem za povezane komponente koje su nam ostale. Zbog osobina centroida dubina ove rekurzije je $O(log N)$ pa je vremenska složenost celog algoritma $O(N log^2 N)$.

## Alternativno rešenje za 100 poena
**Vremenska složenost:** $O(N log^2 N)$

Kao u rešenju za kompletno binarno stablo, nađimo vrednosti $P(i)$ za svaki čvor. Ovaj put prvo rekurzivno rešavamo podstabla, a zatim tražimo broj SIO parova tako da se koren nalazi na putu između njih. Svaki rekurzivni poziv će napraviti $\text{std::map}$-u u kojoj su prebrojane vrednosti $P(i)$ za sve čvorove $i$ u trenutnom podstablu. Kako bismo napravili $\text{std::map}$ za trenutno podstablo potrebno je da spojimo $\text{std::map}$-e za podstabla koja ostanu kada se izbaci koren ovog podstabla, a zatim da ubacimo $P(koren)$. Kako bismo dobili dobru vremensku složenost, kada spajamo $\text{std::map}$-e uvek prolazimo kroz manju i prebacujemo sve iz nje u veću. Prilikom spajanja prebrojavamo SIO parove. Posmatrajmo put od čvora $U$ do $V$. Neka je $W$ čvor na najmanjem rastojanju od korena koji se nalazi na putu između $U$ i $V$. Par $(U, V)$ je SIO par ako i samo ako važi $P(U) + P(V) - 2 P(W) = (0, 0)$. Ako se $U$ nalazi u manjoj $\text{std::map}$-i, na rešenje dodajemo broj čvorova u većoj, takvih da je $P(V) = 2 P(W) - P(U)$. Ostaje još da analiziramo vremensku složenost ovog algoritma. Posmatrajmo za neki čvor koliko puta je bio prebačen iz jedne u drugu $\text{std::map}$-u. Svaki put kada je prebačen, veličina $\text{std::map}$-e u kojoj je povećala se bar dva puta jer je veličina nove $\text{std::map}$-e zbir veličina $\text{std::map}$-e u kojoj je bio i veće $\text{std::map}$-e. Zbog toga jedan čvor nije mogao biti prebačen više od $log N$ puta. Sledi da je ukupan broj prebacivanja $O(N log N)$, pa kako je za svaku operaciju nad $\text{std::map}$-om potrebno $O(log N)$ vremena, ukupna vremenska složenost ovog algoritma je $O(N log^2 N)$


``` cpp title="05_sio_stablo.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
const int N=300050;
vector<pair<int,char>> E[N];
bool was[N];
int sz[N];
void DFS(int u,int p){sz[u]=1;for(auto e:E[u])if(e.first!=p&&!was[e.first])DFS(e.first,u),sz[u]+=sz[e.first];}
int Find(int u,int p,int n){for(auto e:E[u])if(e.first!=p&&!was[e.first]&&sz[e.first]*2>n)return Find(e.first,u,n);return u;}
int FindCentroid(int u){DFS(u,u);return Find(u,u,sz[u]);}
vector<pair<int,int>> push;
map<pair<int,int>,int> cnt;
ll ans=0;
void Solve(int u,int p,int S,int I,int O){
	push.pb({S-I,S-O});
	ans+=cnt[{I-S,O-S}];
	for(auto e:E[u])if(e.first!=p&&!was[e.first]){
		Solve(e.first,u,S+(e.second=='S'),I+(e.second=='I'),O+(e.second=='O'));
	}
}
void Decompose(int u){
	u=FindCentroid(u);
	was[u]=1;
	cnt.clear();
	cnt[{0,0}]++;
	for(auto e:E[u])if(!was[e.first]){
		Solve(e.first,u,e.second=='S',e.second=='I',e.second=='O');
		for(auto p:push)cnt[p]++;
		push.clear();
	}
	for(auto e:E[u])if(!was[e.first]){
		Decompose(e.first);
	}
}
int main(){
	int n;scanf("%i",&n);
	for(int i=1;i<n;i++){
		int u,v;char c;
		scanf("%i %i %c",&u,&v,&c);
		E[u].pb({v,c});
		E[v].pb({u,c});
	}
	Decompose(1);
	printf("%lld\n",ans);
	return 0;
}

```
