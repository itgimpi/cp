---
hide:
  - toc
---

# A2 - Bezbedna podmatrica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Paša je nedavno kupio kuću u Rzanju. Međutim, nakon kupovine je shvatio da ova kuća ima jednu strašnu manu: ona nema ogradu! Sada Paša ne može mirno da spava jer strahuje od ruskih mafijaša i programera koji u svakom trenutku mogu da napadnu na njegovu nezaštićenu kuću. Stoga, Paša je preuzeo pravljenje ograde u sopstvene ruke.

Pašin plac se može zamisliti kao matrica dimenzija $N\times M$, gde $(i,j)$ predstavlja polje u preseku $i$-te vrste (od vrha) i $j$-te kolone (od leva) i svako polje predstavlja jedan kvadratni metar. Njegova kuća se nalazi kompletno u polju $(A,B)$ (niko nikad nije rekao da je Pašina kuća nešto velika, kuće u Rzanju su skupe). Svako polje $(i,j)$ ima neku bezbednost $C_{ij}$. Paša hoće da izgradi ogradu u obliku pravougaonika tako da ograda prati linije matrice (u prevodu, Paša će ograditi jednu podmatricu početne matrice) i da u svojoj unutrašnjosti sadrži njegovu kuću. U Rusiji imaju malo nestandardnu definiciju bezbednosti pa se smatra da je bezbednost ograde čije je gornje levo polje $(x,y)$, donje desno polje $(z,t)$ i obim $O$ metara upravo $C_{xy}+C_{zt}+O$.

Paša ne želi ništa da rizikuje, stoga želi da izgradi što je moguće bezbedniju ogradu, ali se previše plaši ruskih programera da bi njima zatražio pomoć. Zato je pitao vas da mu kažete kolika je najveća moguća bezbednost ograde koju on može da izgradi.

## Opis ulaza

Prva linija standardnog ulaza sadrži četiri broja, broj vrsta $N$, broj kolona $M$ i vrednosti $A,B$ koje opisuju lokaciju njegove kuće. Narednih $N$ linija sadrže po $M$ prirodnih brojeva: gde $j$-ti broj u $(i+1)$-voj liniji predstavlja broj $C_{ij}$, koji označava bezbednost polja $(i,j)$.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati jedan broj: najveću moguću bezbednost ograde koju Paša može da izgradi.

## Primer 1

### Ulaz

```
3 3 2 2
8 8 1
7 9 5
3 4 7

```

### Izlaz

```
27

```

## Primer 2

### Ulaz

```
3 3 2 2
1 1 1
1 9 1
1 1 1

```

### Izlaz

```
22

```

## Objašnjenje primera

Za prvi primer, najveća vrednost bezbednosti ograde je u slučaju da postavi ogradu oko celog placa koji ima obim $12$ i stoga je bezbednost $8+7+12=27$.

U drugom primeru je optimalno da se izgradi ograda samo oko Pašine kuće koja se nalazi u polju $(2,2)$, tada ograda ima obim $4$ i njena bezbednost je $9+9+4$ (polje $(2,2)$ se računa i kao gornje levo i kao donje desno polje).

## Ograničenja

-   $1 \leq N,M \leq 1000$
-   $1 \leq A \leq N$
-   $1 \leq B \leq M$
-   $1 \leq C_{ij} \leq 1000$

Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $20$ poena: $N,M \leq 50$.
-   U test primerima vrednim $20$ poena: $C_{ij} \leq 50$.
-   U test primerima vrednim $20$ poena: $N,M \leq 400$.
-   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja.

## Napomena

Ivan Pavlov je rođen u Rzanju.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Pavle Martinović | Pavle Martinović | Aleksa Plavšić |



## Analiza
Primetimo da ako smo izgradili ogradu čije je gornje levo polje $(x,y)$, a donje desno je $(z,t)$ mora da važi $x\leq a\leq z$ i $y\leq b\leq t$ da bi sadržalo polje koje sadrži kuću. Takođe vidimo da je u tom slučaju obim podmatrice upravo $2\cdot(z+t-x-y)+4$. Sada vidimo da treba da maksmiziramo vrednost $C_{xy}+C_{zt}+2\cdot(z+t-x-y)+4$, za $x\leq a\leq z$ i $y\leq b\leq t$. Prostom proverom po svim četvorkama daje lako $O((NM)^2)$.
Da bi se ovo dalje optimizovalo, izvršićemo zamenu redosleda sabiraka: treba da maksimiziziramo izraz $(C_{xy}-2\cdot x-2\cdot y)+(C_{zt}+2\cdot z+2\cdot t)+4$. Označimo $G_{xy}=C_{xy}-2\cdot x-2\cdot y$ i $H_{zt}=C_{zt}+2\cdot z+2\cdot t$. Sada vidimo da tražimo maksimum $G_{xy}+H_{zt}+4$, pri čemu važi $x\leq a\leq z$, $y\leq b \leq t$ i sabirci $G_{xy}$ i $H_{zt}$ su potpuno nezavisni. Stoga možemo da nađemo maksimum $G_{xy}$ pod uslovom $x\leq a, y\leq b$ (neka je ovaj maksimum $M_1$) i maksimum $H_{zt}$ po uslovom $z\geq a, t\geq b$ (neka je ovaj maksimum $M_2$), i zatim ispišemo rešenje $M_1+M_2+4$. Računanje matrica $G$ i $H$, kao i traženje $M_1$ i $M_2$ se rade lakom pretragom u $O(NM)$.


``` cpp title="05_bezbedna_podmatrica.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 1007
using namespace std;
int a[MAXN][MAXN];
int main()
{
	int n,m,x,y;
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {if(a[i][j]>1000 || a[i][j]<=0) printf("%d %d %d\n",i,j,a[i][j]); assert(a[i][j]>0 && a[i][j]<1001);}
	int mx1=-2000000000,mx2=-2000000000;
	for(int i=1;i<=x;i++) for(int j=1;j<=y;j++) mx1=max(mx1,a[i][j]-2*i-2*j);
	for(int i=x;i<=n;i++) for(int j=y;j<=m;j++) mx2=max(mx2,a[i][j]+2*i+2*j);
	printf("%d",mx1+mx2+4);
}

```
