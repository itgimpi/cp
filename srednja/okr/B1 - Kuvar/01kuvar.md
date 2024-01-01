# B1 - Kuvar

	| Vremensko ograničenje | Memorijsko ograničenje |
	| 1000ms                | 64MB |
	
	Poznati TV kuvar Epirka planira sledeću sezonu svoje emisije, u kojoj će snimiti **N** emisija o jelima X~1~, X~2~, \dots, X_N$ (ne neophodno različitim -- moguće je da snima više emisija o istom jelu). Radi jednostavnosti, predstavićemo ova jela brojevima (isto od $1$ do **N**): ako je $X_i = x$, $i$-ta emisija će biti o jelu **x**.
	
	Na raspolaganju mu je **N** recepata $Y_1, Y_2, \dots, Y_N$, isto predstavljeni brojevima. Pošto emisija mora biti zanimljiva, nisu dovoljni recepti, već i scenario: smislio je (isto) **N** scenarija $Z_1, Z_2, \dots, Z_K$, gde $Z_i = z$ znači da se $i$-ti scenario može koristiti za emisiju u kojoj će praviti jelo $Y_{z}$.
	
	Nakon što je popisao emisije, jela i recepte, interesuje ga na koliko načina može da počne snimanje, odnosno na koliko načina može da izabere emisiju **i** i scenario **j** o receptu za odgovarajuće jelo. Drugim rečima, interesuje ga broj uređenih parova **(i, j)**, za koje važi $X_i = Y_{Z_j}$.
	
	## Opis ulaza
	Prvi red standardnog ulaza sadrži jedan prirodan broj $N$: broj emisija, recepata i scenarija.
	
	Drugi red sadrži $N$ prirodnih brojeva $X_1, X_2, \dots, X_N$, gde je $X_i$ jelo o kom će snimiti $i$-tu emisiju.
	
	Treći red sadrži $N$ prirodnih brojeva $Y_1, Y_2, \dots, Y_N$, gde je $Y_j$ jelo koje se pravi po $j$-tom receptu.
	
	Četvrti red sadrži $N$ prirodnih brojeva $Z_1, Z_2, \dots, Z_N$, gde je $Z_k$ recept koji se koristi u $k$-tom scenariju. Scenariji su indeksirani počev od 1.
	
	## Opis izlaza
	Na standardni izlaz je potrebno ispisati jedan ceo broj: broj načina na koje je moguće izabrati emisiju i scenario, tako da recept koji odgovara tom scenariju pravi jelo o kom će emisija biti.
	
	## Primer 1
	### Ulaz
	```
	4
	1 1 4 3
	3 1 3 4
	1 3 2 2
	```
	
	### Izlaz
	```
	6
	```
	
	## Primer 2
	### Ulaz
	```
	5
	1 1 1 1 1
	2 1 5 5 5
	2 1 2 3 3
	```
	
	### Izlaz
	```
	10
	```
	
	## Objašnjenje primera
	Ako se u prvom primeru odluči za prvu epizodu, praviće jelo $1$, koje se pravi samo po drugom receptu. Za taj recept postoje dva moguća scenarija: treći i četvrti.
	
	Slično, drugoj epizodi odgovaraju treći i četvrti scenario.
	
	Treća epizoda je o jelu **4**, za koje nema na raspolaganju nijedan scenario.
	
	Četvrta epizoda je o jelu **3**, koje se pravi po prvom i trećem receptu. Za prvi recept ima spreman scenario $1$, a za drugi scenario $2$, tako da i za ovu epizodu ima na raspolaganju dva scenarija.
	
	Dakle, ukupno ima **2 + 2 + 0 + 2 = 6** opcija.
	
	## Ograničenja
	
	- $1 \leq N \leq 10^5$.
	- $1 \leq X_i, Y_i, Z_i \leq N$.
	
	Test primeri su podeljeni u pet disjunktnih grupa:
	
	- U testovima vrednim 20 poena: $N \leq 1000$ i $Z_i = i$ za sve $1 \leq i \leq N$.
	- U testovima vrednim 20 poena: $N \leq 1000$.
	- U testovima vrednim 10 poena: svi $Z_i$ su isti.
	- U testovima vrednim 20 poena: $Z_i = i$ za sve $1 \leq i \leq N$.
	- U testovima vrednim 30 poena: nema dodatnih ograničenja.
	
=== "Rešenje"
	
	| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
	|:-:|:-:|:-:|:-:|
	| Vladimir Milovanović | Dimitrije Erdeljan | Dimitrije Erdeljan | Marko Šišović |
	
	## Glavno rešenje
	Prva dva podzadatka možemo jednostavno rešiti sa dve ugnježdene petlje koje isprobavaju svaki par $(i, j)$ i broje za koliko takvih parova je $X_i = Z_{Y_j}$. Vremenska složenost ovog algoritma je $\mathcal{O}(N^2)$, što neće biti dovoljno za preostale podzadatke.
	
	Algoritam možemo poboljšati tako što razdvojimo ove dve petlje: prvo ćemo prebrojati koliko postoji epizoda za svako moguće jelo, odnosno izračunati niz $C$, gde je $C_i$ broj indeksa $j$ gde $X_j = i$. Pošto su sve vrednosti $X_i$ najviše $N$, ovaj niz staje u memoriju i možemo ga popuniti jednim prolazom kroz $X$.
	
	Sada je dovoljno da prođemo kroz $Z$, i za svako $Z_i$ ukupnom broju dodamo $C_{Z_i}$ (broj elemenata u $X$ koji bi bili odgovarajući par). Vremenska složenost je sada $\mathcal{O}(N)$, sasvim dovoljno za $N \leq 10^5$.
	
	``` cpp title="01_kuvar.cpp" linenums="1"
	#include <cstdio>
	#include <algorithm>
	
	const int N = 100005;
	int x[N], y[N], z[N];
	int cnt[N];
	
	int main() {
	    int n;
	    scanf("%d", &n);
	    for(int i = 0; i < n; i++) scanf("%d", &x[i]);
	    for(int i = 0; i < n; i++) scanf("%d", &y[i]);
	    for(int i = 0; i < n; i++) scanf("%d", &z[i]);
	
	    long long res = 0;
	    for(int i = 0; i < n; i++) cnt[x[i]]++;
	    for(int i = 0; i < n; i++) res += cnt[y[z[i] - 1]];
	
	    printf("%lld\n", res);
	    return 0;
	}