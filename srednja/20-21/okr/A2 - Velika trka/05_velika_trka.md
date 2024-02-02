---
hide:
  - toc
---

# A2 - Velika trka

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 3000ms | 256MB |

U Republici Izometriji najveći godišnji spekatkl je velika trka koja se održava u srcu države - Centralgradu. Tu dolaze najbolji trkači i najspremniji rekreativci iz svih većih gradova države i bore se za titulu Visokog Velemajstora Metrika.

Centralgrad ima oblik dvodimenzionog koordinatnog sistema. Traka trke je određena startnom tačkom i sa $k$ stubova na sledeći način: u $i$-tom delu trke trkači trče od trenutne pozicije do $i$-tog stuba, ali kad stignu do njega nastave da trče u istom pravcu i smeru tako da pređu još toliku distancu koliko su prešli do tad u tom delu trke, to jest **$i$-ti stub treba da bude središte duži koja spaja početak i kraj $i$-tog dela trke.** Drugim rečima, završetak $i$-tog dela trke (i početak $i+1$-vog dela) je tačka centralno simetrična u odnosu na $i$-ti stub.   

Organizatori su postavili $N$ stubova numerisanih sa $1,2,\ldots,N$, ali nisu još odredili koje će koristiti u trci. Zbog toga žele da razrade $Q$ scenarija, gde je $i$-ti scenario određen sa četiri vrednosti: $x$ i $y$ koje predstavljaju koordinate početka trke i  $L$ i $R$ koje predstavljaju da će za trku biti iskorišćeni redom stubovi numerisani sa $L,L+1,\ldots,R$. Organizatori su malo smotani, pa traže od vas da odredite za svaki scenario gde bi se nalazio kraj trke.

## Opis ulaza
U prvom redu ulaza se nalazi prirodan broj $N$-broj stubova. U narednih $N$ redova se nalaze po $2$ prirodna brojeva $x_i$ i $y_i$ koje predstavljaju lokacije postavljenih stubova. U narednom redu se nalazi prirodan broj $Q$-broj scenarija. U narednih $Q$ linija se nalazi po četiri broja $x,y,L,R$ kojim su opisani scenariji.

## Opis izlaza
Na izlaz ispisati $Q$ redova sa po $2$ broja, gde brojevi u $i$-tom redu predstavljaju koordinate cilja u $i$-tom scenariju.

## Ograničenja
-   $1 \leq N,Q \leq 200.000$
-   $0\le x_i,y_i\le10^9$
-   $0\le x ,y\le10^9$ za svaki upit
-   $1\le L\le R\le N$ za svaki upit

Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $10$ poena:  $N,Q\leq 1000$,  $x_i,y_i\le 1.000.000$ i $x,y\le 1.000.000$ za svaki upit.
-   U test primerima vrednim $10$ poena: Koordinate svih stubova su iste.
-   U test primerima vrednim $30$ poena: $y$ koordinate svih stubova i startova su jednake $0$
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
2
1 1
3 3
2
0 0 1 1
0 0 1 2
```

#### Izlaz
```
2 2
4 4
```

#### Objašnjenje
U prvom scenariju, trka ima samo jedan deo koji vodi od $(0,0)$ do $(2,2)$, jer je $(1,1)$ središte te duži. U drugom scenariju, trka ima dva dela, prvi vodi od $(0,0)$ do $(2,2)$, kao u prvom scenariju, a drugi vodi od $(2,2)$ do $(4,4)$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Milisavljević |

## $N,Q\leq 1000$
U ovom podzadatku možemo lako simulirati svaki deo trke, ako deo trke kreće u $(x,y)$ i ide preko stuba $(x',y')$, onda se završava u tački $(2x'-x,2y'-y)$ , i nađemo gde se završava u složenosti $O(NQ)$.

## Svi stubovi su na istom mestu
Ono što treba primetiti u ovom podzadatku da će posle svaka dva dela trke da se trkači vrate na startnu poziciju, pa je jedino zapravo bitna parnost broja $r-l$, i u zavisnosti od njega možemo da odredimo da li se trka završava tamo gde i počinje ili centralno simetrično tome u odnosu na stubove.

## Sve $y$ koordinate su $0$
Rešavamo slučaj na brojevnoj pravoj. Ako je početak trke na poziciji $x_0$, a stubovi na $x_1,x_2\cdots,x_n$. Onda je kraj prvog dela trke na $2x_1-x_0$, drugog dela trke na $2x_2-(2x_1-x_0)=2x_2-2x_1+x_0$, $\cdots$, $n$-tog dela trke na $2x_n-2x_{n-1}+2x_{n-2}-\cdots+2\cdot(-1)^{n-1}x_{1}+(-1)^{n}x_0$. Ovo znači da ako pamtimo parcijalne sume oblika $x_1-x_2+x_3-x_4+\cdots$, oduzimanjem dve parcijalne sume i obraćanjem pažnje na parnost možemo da nađemo konačnu poziciju trke u složenosti $O(N+Q)$

## Kompletno rešenje
U ovom slučaju je dovoljno primetiti da možemo razdvojiti problem ko koordinatama i obe koordinate nezavisno rešimo kao u prethodnom podzadatku u složenosti $O(N+Q)$.

``` cpp title="05_velika_trka.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 200007
using namespace std;
long long x[MAXN],y[MAXN],px[MAXN],py[MAXN];
int main()
{
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++) px[i]=px[i-1]+x[i]*((i&1)?1:-1);
	for(int i=1;i<=n;i++) py[i]=py[i-1]+y[i]*((i&1)?1:-1);
	scanf("%d",&q);
	while(q--)
	{
		long long xt,yt;
		int l,r;
		scanf("%lld%lld%d%d",&xt,&yt,&l,&r);
		printf("%lld %lld\n",2*(px[r]-px[l-1])*((r&1)?1:-1)+xt*(((r-l)&1)?1:-1),2*(py[r]-py[l-1])*((r&1)?1:-1)+yt*(((r-l)&1)?1:-1));
	}
}

```
