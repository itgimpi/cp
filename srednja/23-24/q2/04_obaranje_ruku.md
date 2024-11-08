

# 4 - Obaranje ruku


	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2400ms | 768MB |
	
Zmijko Reptil organizuje turnir u obaranju ruku. Kako je on zmija i nema ruke, on neće učestvovati. Učestvovaće njegovih $N$ najboljih drugova koji su svi ljudi, gde je $N$ **stepen dvojke**. Tačnije, moguće je napraviti perfektan turnir bez potrebe da neko izostane iz nekog kruga. Zmijko je već svakom od njih dodelio jedinstven broj od $1$ do $N$. Poznato je da $i$-ti drug ima snagu $P_i$, kao i da su sve snage različiti brojevi iz skupa $\{ 1,2,\ldots, N\}$.
	
	
	
Odvija se više krugova kako bi se izabrao pobednik. Neka u trenutnom krugu turnira učestvuje $K$ drugova. Ruke obaraju parovi drugova $(1,2),(3,4),\ldots (K-1,K)$. U naredni krug prolazi onaj sa većom snagom u paru. Dakle, ukupno $\frac{K}{2}$ drugova učestvuje u narednom krugu i dodeljuju im se novi brojevi na naredno naveden način. Neka su $B_1 < B_2 < \ldots < B_{K/2}$ brojevi pobednika trenutnog kruga. Njihovi novi brojevi su, redom, $1,2,\ldots \frac{K}{2}$. Napomenimo da oni prilikom renumeracije zadržavaju stare snage. U prvom krugu učestvuje $N$ drugova, u drugom $\frac{N}{2}$, u trećem $\frac{N}{4}$, $\ldots$ , u poslednjem $1$. Primetimo da, pošto je $N$ stepen dvojke, u svakom krugu učestvuje ceo broj drugova, tj. uvek je moguće pravilno izvršiti deljenje.
	
	
	
Zmijko je poznati prevarant i on želi da jedan njegov poseban drug osvoji što bolji rezultat. Pobednik je očito poznat - to je drug sa snagom $N$. Međutim, Zmijku je dovoljno da poslednji krug njegovog miljenika bude što viši. On ni sam ne zna šta želi i dvoumi se između $Q$ opcija.
	
	
	
U svakoj opciji poznati su mu miljenik $M_i$ i broj $J_i$. Zmijko ima pravo da zameni mesto bilo koja dva druga (koji nisu $M_i$ jer je to previše sumnjivo) i time promeni budući ishod turnira. Dozvoljeno mu je da to izvrši **najviše** $J_i$ puta pre početka turnira. Nakon što turnir počne nema pravo da vrši zamene. Pri takvim uslovima, zanima ga najveći broj kruga do kog miljenik $M_i$ može stići.
	
	
	
Pošto su ovo ipak teoretske opcije, one se neće zapravo izvršavati. Samim tim smatramo da se one nezavisno jedna od druge odvijaju.
	
	
	
## Opis ulaza
	
	
	
U prvom redu standardnog ulaza, dat je ceo broj $N$ - broj Zmijkovih drugova koji učestvuju u turniru obaranja ruku. Garantuje se da je $N$ **stepen dvojke**.
	
	
	
U drugom redu standardnog ulaza, dato je $N$ celih brojeva $P_1,P_2,\ldots,P_N$ - snage drugova.
	
	
	
U trećem redu standardnog ulaza, dat je ceo broj $Q$ - broj opcija koje Zmijko razmatra.
	
U $i$-tom od narednih $Q$ redova, data su dva cela broja $M_i$ i $J_i$.
	
	
	
## Opis izlaza
	
	
	
Ispisati $Q$ redova. U $i$-tom od njih ispisati najviši krug do koji miljenik može stići.
	
	
	 
## Ograničenja
	
	
	
- $4 \leq N \leq 2^{20}$, $N$ je stepen dvojke
- $1 \leq Q \leq 5\cdot 10^5$
- $1 \leq P_i \leq N$, navedeni brojevi su međusobno različiti.
- $1 \leq M_i \leq N$
- $0 \leq J_i \leq N$
	
	
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
- U testovima vrednim 8 poena: $N = 4$
- U testovima vrednim 16 poena: Važi $P_i = i$ za svakog druga.
- U testovima vrednim 16 poena: Važi $M_i = M_j$ za svaka dva cela broja $1 \leq i,j \leq Q$. Tačnije, miljenik je isti u svakoj opciji.
- U testovima vrednim 44 poena: $N \leq 2^{17}$, $Q \leq 10^5$
- U testovima vrednim 16 poena: Bez dodatnih ograničenja.
	
	
	
## Primer 1
	
	
	
### Ulaz
	
	
	
```
	8
	1 8 2 7 4 6 3 5
	4
	1 8
	3 1
	5 2
	5 1
```
	
	
	
### Izlaz
	
	
```
	1
	2
	3
	2
```
	
	
	
### Objašnjenje
	
	
	
U prvoj opciji, drug broj $1$ ima snagu $1$. On ne može pobediti nikoga drugog jer ima najmanju snagu, te igru završava u prvom krugu.
	
	
	
U drugoj opciji, drug broj $3$ ima snagu $2$. Sprečavamo obaranje ruku sa drugom $4$ koji ima snagu $7$ tako što njega menjamo sa drugom $1$ snage $1$. Prilikom obaranja ruku, miljenik pobeđuje i time se plasira u drugi krug. Dokazuje se da je to i najviši krug do kog može stići.
	
	
	
U trećoj opciji, menjamo drugove $6$ i $8$ sa, redom, drugovima $1$ i $3$. Time drug $5$, miljenik, stiže do trećeg kruga.
	
	
	
## Primer 2
	
	
	
### Ulaz
	
	
	
```
	4
	1 2 3 4
	4
	1 1
	2 1
	3 1
	4 1
```
	
	
	
### Izlaz
	
	
	
```
	1
	2
	2
	3
```
	
	
	
### Objašnjenje
	
	
	
U četvrtoj opciji, drug $4$ ima snagu $4$ i on zasigurno pobeđuje turnir. U prvom krugu učestvuje $4$ druga, u drgom $2$, a za treći krug možemo reći da učestvuje samo $1$ (iako se taj krug ne nastavlja). Zato kažemo da je $3$ odgovor za četvrtu opciju.
	
	
Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Aleksandar Višnjić | Pavle Martinović | Pavle Martinović |
	
## Rešenje kada $N=4$
	
Ovaj zadatak je moguće uraditi grubom silom, ali i ručno s obzirom da postoje samo četiri međusobno ne-ekvivalentna žreba, a to su $(1,2,3,4)$, $(1,3,2,4)$ i $(1,4,2,3)$, gde svakom treba najviše jedna razmena da bi stigao do finala, osim najslabijem koji svakako ispada u prvoj rudni.
	
## Rešenje kada $P_i=i$
	
U ovom zadatku, kao i u svakom nadalje, je ključno opisati uslov za jednu osobu da li može da stigne do neke runde. Podturnir definišemo kao skup svih ljudi koji igraju da bi jedan od njih prošao u $k$-to kolo. Da li osoba $x$ može stići do $k$-runde zavisi da li ima $2^{k-1}-1$ igrača koje može da pobedi, (jer da bi stigao do $k$-te runde, mora biti najjači u njegovom podturniru), i da li ima dovoljno razmena na raspolaganju da izbacimo sve jače ljude iz tog podturnira. Ukoliko imamo dovoljno razmena na raspolaganju, onda samo sve te jače ljude unutar podturnira zamenimo sa slabijim ljudima van podturnira, kojih ima dovoljno zbog prvog uslova. Tako da sada znamo da odgovorimo na pitanje da li učesnik može da stigne do runde $k$ ako znamo broj razmena i broj jačih od njega u tom podturniru. Znamo da postoji ukupno $N-1$ podturnira, i svaki učestvuje u $\log_2N$ podturnira. Kada dobijemo novo pitanje, možemo za svaki podturnir u kome taj čovek učestuje da odredimo da li može da bude pobednik tu (broj razmena nam je dat, a broj jačih u podturniru možemo lako odrediti zbog specifičnosti permutacije) i odgovorimo na sva pitanja u $O(Q\log N)$.
	
## Rešenje kada je uvek isti miljenik
	
Za svaki podturnir koji sadrži miljenika je moguće proći kroz sve ljude i sračunati koliko ih ima jačih od njega u $O(N)$, a zatim odgovaramo na pitanja isto ko u prethodnom podzadatku.
	
## Rešenje kada $N\leq 17$, $Q\leq 100.000$
	
U svakom podturniru možemo držati sortiran niz svih učesnika tog turnira, a zatim kada hoćemo da vidimo da li miljenik može stići do nekog kola, binarnom pretragom po tom nizu sačuvanom za taj podturnir, možemo brzo naći tačno koliko njih je jačih u tom podturniru, i onda videti jel moguće stići do tog kola isto kao u drugom podzadatku. Složenost $O(N\log^2N+Q\log^2N)$.
	
## Glavno rešenje
	
Radimo upite u tzv. `offline` načinu. Sortiramo upite po tome kolika je jačina čoveka koji je miljenik, a zatim po tome koliko razmena imamo na raspolaganju. Kada rešimo sve upite za nekog miljenika, prođemo kroz sve podturnire u kojima on učestvuje i dodamo $1$ na neki brojač. Kada sad rešavamo upite za nekog sledećeg miljenika, u brojaču za svaki podturnir će stajati broj učesnika tog podturnira koji su slabiji od trenutno posmatranog (iz čega, naravno, odmah možemo da nađemo i broj jačih od posmatranog). Dalje, pošto je broj razmena potreban da stigne do $k$-tog kola rastuća funckija, tako da sada, preko informacija u brojačima možemo naći u $O(1)$ koliko najmanje razmena treba da bi stigao do tog kola. Pošto je niz upita sortiran, metodom `2 pointers`, možemo odgovoriti na svaki upit za trenutnog miljenika. Složenost $O(N\log N+Q\log Q)$.
	
``` cpp title="04_obaranje_ruku.cpp" linenums="1"
	#include <bits/stdc++.h>
	#define MAXN (1<<20)+7
	using namespace std;
	pair<int,int> p[MAXN];
	vector<pair<int,int> > queries[MAXN];
	int br[2*MAXN],ans[MAXN];
	int main()
	{
	    ios_base::sync_with_stdio(false);
	    cin.tie(0);
	    int n,q;
	    cin>>n;
	    for(int i=0;i<n;i++) cin>>p[i].first;
	    for(int i=0;i<n;i++) p[i].second=i;
	    sort(p,p+n,greater<pair<int,int>>());
	    cin>>q;
	    for(int i=0;i<q;i++)
	    {
	        int t1,t2;
	        cin>>t1>>t2;
	        queries[t1-1].push_back({t2,i});
	    }
	    for(int i=0;i<n;i++)
	    {
	        int poz=n+p[i].second,t=0;
	        sort(queries[p[i].second].begin(),queries[p[i].second].end());
	        int k=1;
	        while(poz!=1)
	        {
	            poz/=2;
	            int treba=(n-i<(1<<k))?MAXN:br[poz];
	            while(t<queries[p[i].second].size() && queries[p[i].second][t].first<treba) {ans[queries[p[i].second][t].second]=k; t++;}
	            br[poz]++;
	            k++;
	        }
	    }
	    int log=0;
	    while((1<<log)!=n) log++;
	    for(int i=0;i<queries[p[0].second].size();i++)  ans[queries[p[0].second][i].second]=log+1;
	    for(int i=0;i<q;i++) cout<<ans[i]<<endl;
	}
```
