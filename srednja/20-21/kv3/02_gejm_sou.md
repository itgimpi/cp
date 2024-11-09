---
hide:
  - toc
---

# 2 - Gejm šou

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Upravo je završen treći krug večerašnje epizode poznate emisije *Nokskru Gejm Šou*, i vaš omiljeni tročlani tim, "Sanjive Zanatlije", gubi rezultatom 2-1, i time je pred ispadanjem. Zbog toga, moraju odneti pobedu u sledećoj igri: *Sprint 4*.

Igra *Sprint 4* je trka koja se sastoji iz $N-1$ delova, u kojima dva igrača trče po brojevnoj pravoj, brzinom najviše $1$. Na početku trke, igrači se nalaze na pozicijama $a_0$ i $b_0$. U $i$-tom delu trke, trkači treba da stignu od svoje trenutne pozicije, do pozicija $a_i$ i $b_i$. Računa se da su prešli $i$-ti deo kada se nađu na pozicijama $a_i$ i $b_i$ u nekom rasporedu (nije bitno koji igrač stoji na kojoj od dve pozicije). Kada se trenutni deo završi, sledeći odmah otpočinje i takmičari kreću sa trenutnih pozicija ka novim ciljevima. Trka se završava kada se završi $N-1$-vi deo trke.

Kako je trka jako neizvesna, Zanatlijama je potrebna vaša pomoć. Na vama je da odredite najmanje moguće vreme da bi završili trku.

## Opis ulaza
U prvom redu ulaza se nalazi prirodan broj $N$, dužina nizova $a$ i $b$.<br>
U svakom narednom redu se nalaze po dva prirodna broja $a_i$ i $b_i$, koji opisuju pozicije ciljeva za $i$-ti deo trke.

## Opis izlaza
Na izlaz ispisati jedan broj: najmanje vreme potrebno da bi završili trku.

## Ograničenja
-   $1 \leq N \leq 10^{5}$
-   $-10^9\le a_i,b_i \le10^9$

Test primeri su podeljeni u 4 disjunktnih grupa:

-   U test primerima vrednim $20$ poena: $N \leq 20$
-   U test primerima vrednim $20$ poena: $a_i=b_i$ važi za svako $0\le i\le N-1$.
-   U test primerima vrednim $15$ poena: $N \leq 1000$
-   U test primerima vrednim $45$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz
```
5
1 5
6 2
3 7
8 4
5 8
```

#### Izlaz
```
4
```

#### Objašnjenje
Za prva $3$ dela trke, svaki igrač treba da se pomeri jedno mesto udesno. U poslednjem delu, prvi igrač treba da se pomeri jedno mesto udesno ($4\rightarrow5$), dok drugi treba da ostane na svojoj poziciji $8$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Milisavljević |

## $N\leq 20$
Možemo da fiksiramo po svih $2^n$ kombinacija, na koji cilj ide koji trkač. Zatim za svaku fazu vidimo vreme koje je potrebno kao maksimum od dve distance koji trkači treba da pređu.

## $a_i=b_i$
U ovom slučaju oboje pra
te istu jedinstvenu putanju i mi nemamo nikakvu odluku da pravimo. Samo prođemo kroz niz destinacija i sumiramo distance susednih.

## Kompletno rešenje
Ono što je ključno primetiti u ovom zadatku je da su nama trkači sasvim simetrični u svakoj fazi. U prevodu nije bitno koji je igrač na $a_i$, a koji na $b_i$,  samo da treba da stignu na pozicije $a_{i+1}$ i $b_{i+1}$ u nekom poretku. To znači zapravo da u svakoj fazi trke imamo $2$ mogućnosti: onog na poziciji $a_i$ šaljemo na ili poziciju $a_{i+1}$ ili poziciju $b_{i+1}$. Za obe ove mogućnosti možemo izračunati vreme potrebno i samo prosumirati minimume po svim fazama.

``` cpp title="02_gejm_sou.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 100007
using namespace std;
long long a[MAXN],b[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld%lld",&a[i],&b[i]);
	long long sol=0;
	for(int i=1;i<n;i++) sol+=min(max(abs(a[i]-a[i-1]),abs(b[i]-b[i-1])),max(abs(a[i]-b[i-1]),abs(b[i]-a[i-1])));
	printf("%lld",sol);
}

```
