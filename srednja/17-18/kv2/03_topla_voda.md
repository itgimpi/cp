---
hide:
  - toc
---

# 3 - Topla voda

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Džarko se upravo vratio kući sa zimovanja na Alpima, i, kako to običaji nalažu, rešio je da sa nekoliko mesta u svojoj kući ispusti nagomilanu ledenu vodu. Džarkova kućna vodovodna mreža se može modelirati kao kolekcija $N$ vodovodnih čvorova, koji su označeni brojevima od $1$ do $N$, i koji su povezani sa $N-1$ cevi. U čvoru $1$ nalazi se bojler (uređaj iz kojeg izlazi topla voda). Na svim ostalim čvorovima nalazi se slavina (uređaj iz kojeg teče voda).

Dodatno važi da je svaki vodovodni čvor povezan sa bojlerom cevima, bilo direktno, bilo preko nekih drugih čvorova. Kada Džarko odvrne slavinu na nekom čvoru, on čeka dok iz te slavine ne poteče topla voda. Ovo vreme čekanja, izraženo u minutima, jednako je broju cevi koje su sadržale ledenu vodu među cevima sa jedinstvenog puta od bojlera do te slavine. Nakon što zatvori slavinu sve ove cevi do daljnjeg više ne sadrže ledenu već toplu vodu. Džarko je smislio i vama rekao plan, odnosno redosled slavina na kojima planira da ispušta vodu. Pomozite Džarku tako što ćete mu za dati niz slavina reći, za svaku, koliko dugo će čekati dok iz nje ne poteče topla voda.

## Opis ulaza
U prvoj liniji standardnog ulaza nalazi se ceo broj $N$ koji predstavlja broj čvorova vodovodne mreže. U čvoru $1$ se nalazi bojler. U narednih $N-1$ linija standardnog ulaza nalaze se po dva cela broja $u_i, v_i$, redni brojevi vodovodnih čvorova koji su direktno povezani jednom cevi. U narednom redu nalazi se $M$, broj slavina koje interesuju Džarka. U narednih $M$ linija nalazi se po jedan broj $x_i$ - redni broj slavine.

## Opis izlaza
U $M$ redova ispisati po jedan broj, gore definisano vreme čekanja izraženo u minutima.

## Primer 1
### Ulaz

```
4
1 2
2 3
1 4
3
2
3
4
```

### Izlaz
```
1
1
1
```

## Primer 2
### Ulaz
```
4
1 4
4 3
2 4
2
3
2
```

### Izlaz
```
2
1
```

## Objašnjenje primera
U $1$. primeru, nakon što Džarko pusti vodu sa slavine broj $2$, topla voda će se nalaziti u cevi koja spaja bojler i slavinu broj $2$ pa će kad odvrne slavinu $3$ čekati samo jedan minut. Iz istog razloga će čekati samo jedan minut kada odvrne slavinu $4$.

U $2$. primeru, nakon što Džarko odvrne slavinu broj $3$, topla voda će se nalaziti u cevima $(1, 4)$ i $(4, 3)$ pa će kad odvrne slavinu $2$ čekati samo jedan minut, odnosno čekaće samo da topla voda prođe kroz cev $(2, 4)$.

## Ograničenja

* $2 \leq N, M \leq 300000$.
* Garantuje se da će vodovodna mreža biti povezana.
* Za brojeve slavine $x_i$ važi $2 \leq x_i \leq N$.

Test primeri su podeljeni u tri disjunktne grupe:

* U 35% primera važi $N, M \leq 1000$.
* U 35% primera važi $N, M \leq 75000$.
* U 30% primera važi $N, M \leq 300000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Nikola Jovanović | Aleksa Plavšić |

Vodovodnu mrežu možemo posmatrati kao stablo sa korenom u čvoru u kom se nalazi bojler (čvor $1$).  Na samom početku, voda u svim cevima (tj. svim granama stabla) je ledena. U toku izvršavanja upita markiraćemo one grane u kojima voda postane topla. Sada svaki upit možemo formulisati kao odgovor na pitanje *Koliko ima nemarkiranih grana na putu od korena do čvora $x_i$?* Naravno, na početku nijedna grana nije markirana.

Najjednostavniji način da odgovorimo na upit je da obiđemo sve grane od $x_i$ do korena, izbrojimo nemarkirane, a zatim ih markiramo. Ovaj pristup u najnepovoljnijem slučaju obilazi celo stablo pri svakom upitu pa je vremenska složenost $O(MN)$. 

Ključna opservacija koja nas dovodi do boljeg rešenja je da se svaki put od korena do nekog čvora deli na niz ($0$ ili više) markiranih grana, a zatim niz ($0$ ili više) nemarkiranih grana. Drugim rečima, svi markirani čvorovi na nekom takvom putu čine prefiks tog puta. Ovo se lako dokazuje tako što primetimo da je svaka markirana grana postala markirana pri traženju odgovara na neki upit. Samim tim, sve grane od nje do korena su takođe markirane u istom upitu. Imajući ovo svojstvo u vidu, dovoljno je pri svakom upitu obilaziti samo grane od $x_i$ do prve markirane grane na putu do korena. Sve grane na ostatku puta su sigurno već markirane. 

Ovo rešenje, iako za neke *nezgodne* upite može obići mnogo grana, u toku celog izvršavanja programa obiđe svaku granu najviše jednom (u trenutku kada biva markirana), pa je ukupna vremenska složenost $O(N+M)$, što je u ovom slučaju optimalno.

## Smernice za algoritam

Sa strane implementacije, rešenje se deli na dva dela: pripremu stabla i odgovaranje na upite. Priprema stabla se svodi na čuvanje roditeljskog čvora za svaki čvor, što nakon učitavanja grana možemo uraditi prostom grafovskom pretragom (*DFS*/*BFS*). Pri svakom upitu dolazimo do odgovora praćenjem niza roditeljskih čvorova počevši od čvora $x_i$, pritom vršeći markiranje svih posećenih čvorova.

``` cpp title="03_topla_voda.cpp" linenums="1"
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<int> e[300005];
int p[300005];
bool topla[300005];

int main() {
	scanf("%d", &n);
	for (int i=1; i<n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	queue<int> q;
	p[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int y : e[x]) {
			if (!p[y]) {
				p[y] = x;
				q.push(y);
			}
		}
	}

	topla[1] = true;

	int m;
	scanf("%d", &m);
	while (m--) {
		int x, y = 0;
		scanf("%d", &x);
		while (!topla[x]) {
			topla[x] = true;
			x = p[x];
			y++;
		}
		printf("%d\n", y);
	}
}
```
