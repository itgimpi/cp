---
hide:
  - toc
---

# 3 - Pakovanje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1600ms | 64MB |


Dato vam je $M$ predmeta. Predmet $i$ ima vrednost $V_{i}$ i težinu $T_{i}$. Imate i $N$ kutija. Kutija $j$ ima nosivost $C_{j}$ i u svaku kutiju možemo da spakujemo najviše jedan predmet. Predmet $i$ može da stane u kutiju $j$ ukoliko je $T_{i} < C_{j}$. Interesuje vas kolika je najveća moguća suma vrednosti predmeta koje možete spakovati u kutije.

## Opis ulaza
U prvoj liniji nalaze se vrednosti $M$, broj predmeta i $N$, broj kutija. U drugoj liniji nalazi se $M$ prirodnih brojeva, koji predstavljaju težine predmeta. U trećoj liniji nalazi se $M$ prirodnih brojeva, koji predstavljaju vrednosti predmeta. U četvrtoj liniji nalazi se $N$ prirodnih brojeva, koji predstavljaju nosivosti kutija.

## Opis izlaza

Ispisati najveću moguću sumu vrednosti predmeta koji se mogu spakovati u kutije.

## Primer 1

### Ulaz

~~~
2 1
8 100
12 100
15
~~~

### Izlaz

~~~
12
~~~

## Primer 2

### Ulaz

~~~
4 3
1 8 4 9
1000000000 25 1000000000 1000000000
10 2 5
~~~

### Izlaz

~~~
3000000000
~~~

## Objašnjenje primera
U prvom primeru u jedinu kutiju, koja ima nosivost $15$, možemo da spakujemo samo prvi predmet, koji ima težinu $8$ i vrednost $12$.
U drugom primeru imamo tri kutije. U prvu, koja ima nosivost $10$ stavljamo četvrti predmet, koji ima težinu $9$ i vrednost $1000000000$, u drugu kutiju, koja ima nosivost $2$ stavljamo prvi predmet, koji ima težinu $1$ i vrednost $1000000000$, a u treću kutiju, koja ima nosivost $5$ stavljamo treći predmet, koji ima težinu $4$ i vrednost $1000000000$. Ukupna vrednost je  $1000000000+1000000000+1000000000=3000000000$

## Ograničenja
* $1 \leq M, N \leq 300.000$
* $1 \leq T_{i}, V_{i}, C_{j} \leq 10^9$

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 10 poena: $1 \leq M, N \leq 6$.
* U test primerima vrednim 20 poena: $1 \leq M, N \leq 1000$.
* U test primerima vrednim 10 poena: Nosivost svake kutije je veća od težine svakog predmeta, tj. važi $T_{i} < C_{j}$ za $1\leq i \leq M$, $1\leq j \leq N$.
* U test primerima vrednim 20 poena: Svi predmeti imaju istu vrednost.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

## Napomena
Primetite da rezultat može da prekorači 32-bitni tip podataka.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dragan Urošević | Aleksa Milisavljević | Vladimir Milovanović | Aleksa Plavšić |

## Analiza

Zadatkom je dato ukupno $N$ kutija i $M$ predmeta, pri čemu svaka kutija ima neku svoju nosivost, dok svaki predmet ima neku svoju težinu i određenu vrednost. Takođe, ključna stavka u postavci zadatka jeste ograničenje da je u jednu kutiju moguće smestiti tačno jedan predmet i to samo ako je nosivost kutije veća od težine predmeta.

Prethodnim je svaki predmet definisan jednim uređenim parom (težina, vrednost), dok je svaka kutija definisana svojom nosivošću. Najpre, radi efikasnijeg rešavanja zadatka sortirati i kutije i predmete u neopadajućem redosledu prema njihovoj nosivosti, odnosno težini, respektivno. Ove operacije lako se izvode u ukupnoj vremenskoj složenosti $\mathcal{O}(M\log M)+\mathcal{O}(N\log N)$ ukoliko se koristi neki napredniji algoritam sortiranja.

Zatim, polazeći od kutije sa najnižom nosivošću, proveriti koji sve predmeti su lakši od njene nosivosti i odabrati predmet sa najvišom vrednošću. Pri svakoj narednoj iteraciji takođe je neophodno proveravati koje je predmete moguće poneti određenom kutijom i birati uvek predmet čija je vrednost najveća. Kako su kutije sortirane po nosivosti, a predmeti po težini, svakom sledećom kutijom biće izvodljivo poneti svaki od predmeta koji bilo moguće poneti i onom niže nosivosti i eventualno još poneki.

Lako se dokazuje da se do najveće zbirne vrednosti predmeta prenosive zadatim kutijama dolazi tako što se u svakoj iteraciji bira najvredniji predmet koji je prema njegovoj težini u datu kutiju moguće smestiti, naravno krećući se od kutije sa najnižom ka kutiji sa najvišom nosivošću. Predmeti koji zadovoljavaju uslov da im je težina niža od nosivosti trenutne kutije potrebno je čuvati unutar neke strukture podataka iz koje se na efikasniji način od puke linearne pretrage može pronaći i izvući baš onaj član sa najvišom vrednošću.

Konkretno, jedna od takvih apstraktnih struktura podataka jeste prioritetni red (eng. priority queue), koji se obično implementira preko takozvane hrpe (eng. heap), a koji na račun logaritamske složenosti umetanja proizvoljnog elementa dozvoljava vađenje člana sa maksimalnom vrednošću takođe u logaritamskoj vremenskoj složenosti po broju elemenata.

## Smernice za algoritam

Nakon sortiranja kutija po nosivosti i predmeta po težini, inicijalizovati rezultat koji predstavlja ukupnu sumu vrednosti predmeta na nulu. U petlji prolaziti kroz kutije počevši od one sa najnižom ka onoj sa najvišom nosivošću i u svakom prolasku ispitivati koji sve predmeti imaju nižu težinu od nosivosti trenutne kutije i dodavati ih u prioritetni red prema njihovoj vrednosti. Na kraju iteracije izvaditi iz reda predmet sa najvišom vrednošću i njegovu vrednost sabrati s trenutnim rezultatom. Po izlasku iz petlje ispisati rezultat. Nije teško pokazati da je asimptotska vremenska složenost ovakvog algoritma loglinearna $\mathcal{O}(M\log M)+\mathcal{O}(N\log N)$, odnosno asimptotski jednaka sortiranju ulaznih vrednosti.

``` cpp title="03_pakovanje.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 400000
using namespace std;
int m,n;
long long result=0;
pair<int,int> p[maxn];
int c[maxn];
int t[maxn];
int v[maxn];
priority_queue<long long> pq;
int main()
{
	scanf("%d %d",&m,&n);
	for(int i=0;i<m;i++) scanf("%d",&t[i]);
	for(int i=0;i<m;i++) scanf("%d",&v[i]);
	for(int i=0;i<m;i++) p[i]=make_pair(t[i],v[i]);
	sort(p,p+m);
	for(int i=0;i<n;i++) scanf("%d",&c[i]);
	sort(c,c+n);
	int i=0;
	for(int j=0;j<n;j++) {
		while(i<m && p[i].first<c[j]) {
			pq.push(p[i].second);
			i++;
		}
		if(pq.size()>0) {
			result+=pq.top();
			pq.pop();
		}
	}
	printf("%lld",result);
	return 0;
}

```
