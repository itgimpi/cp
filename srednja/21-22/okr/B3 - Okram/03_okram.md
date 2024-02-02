---
hide:
  - toc
---

# B3 - Okram

=== "Zadatak"
	
	| Vremensko ograničenje | Memorijsko ograničenje |
	|:-:|:-:|
	| 3000ms | 512MB |
	
	
	Prethodnih godina, duologija o velikom šefu mafije ekskluzivne disjunkcije *Okram Ćivas* postali su neki od najpopularnijih i najvoljenijih filmova na tržištu. Duologija se sastoji od, kao što ime kaže, dva filma, koji se zovu *Okram* i *Ćivas*. U ovom zadatku bavićemo se prvim delom duologije - *Okramom*.
	
	U prvoj avanturi našeg heroja, on se zatekao u misterioznoj matrici, dimenzija $M\times N$. Ova matrica je po mnogo tome misteriozna, a jedan od glavnih razloga je što se smatra da su u njoj dva polja susedna ako dele stranicu. Još misterioznije, dva polja u istoj koloni, od kojih je jedan u prvom redu, a drugi u poslednjem redu, kao i dva polja u istom redu od kojih je jedan u prvoj koloni, a drugi u poslednjoj koloni se takođe smatraju susednim! **Ovo znači da je svako polje susedno sa tačno $4$ polja.**  Na početku, svako polje ima svoju vrednost, koja je Okramu Ćivasu poznata. Svake sekunde, iz nepoznatih razloga, svako polje promeni vrednost u ekskluzivnu disjunkciju (poznatu i kao `xor`) vrednosti svojih suseda u prethodnoj sekundi.
	
	Kako je Okram Ćivas poznat po svojoj majstoriji sa ekskluzivnom disjunkcijom, on je sebi postavio $Q$ pitanja sledeće sadržine: koju vrednost ima polje u preseku reda $x$ i kolone $y$, posle $2^k$ sekundi (svaki čovek koji voli bitovske operacije voli i stepene dvojke)?
	
	## Opis ulaza
	Prva linija standardnog ulaza sadrži tri broja, broj redova $N$, broj kolona $M$ i broj upita $Q$. Narednih $N$ linija sadrže po $M$ prirodnih brojeva: gde $j$-ti broj u $(i+1)$-voj liniji predstavlja broj $A_{ij}$, koji označava početnu vrednost (u $0$-toj sekundi) polja u $i$-tom redu i $j$-toj koloni. Narednih $Q$ linija sadrži po $3$ broja: $x,y,k$, koji predstavljaju pitanja iz teksta.
	
	## Opis izlaza
	Na standardni izlaz je postrebno ispisati $Q$ linija: u $i$-toj liniji treba odgovoriti na $i$-to pitanje.
	
	## Primer
	
	### Ulaz
	
	```
	3 3 2
	1 2 3
	4 5 6
	7 8 9
	1 1 0
	2 2 1
	```
	
	### Izlaz
	
	```
	2
	8
	```
	## Objašnjenja primera
	Posle prve sekunde matrica će izgledati ovako:
	```
	2 15 12
	5 8 11
	4 9 10
	```
	Vrednost u sredini posle druge sekunde će biti jednaka $15\text{ xor }11\text{ xor }9\text{ xor }5=8$.
	
	## Ograničenja
	-   $2 \leq N,M \leq 1500$
	-   $1\leq Q\leq 200.000$
	-   $0\leq A_{ij}\leq 1.000.000$
	-  $1\leq x\leq N$
	-  $1\leq y\leq M$
	-  $0\leq k\leq 1.000.000$
	
	Test primeri su podeljeni u 5 disjunktnih grupa:
	
	-   U test primerima vrednim $10$ poena: $N,M\leq5$ i $A_{ij}\leq 1$
	-   U test primerima vrednim $10$ poena: $K\leq5$
	-   U test primerima vrednim $20$ poena: $K\leq200$
	-   U test primerima vrednim $30$ poena: Sve početne vrednosti su $0$ osim jedne koja je $1$.
	-   U test primerima vrednim $30$ poena: Bez dodatnih ograničenja
	## Napomena
	
	Operator ekskluzivne disjunkcije u Pascal-u je označen sa  `xor`, dok u C++ ga zapisujemo pomoću simbola  `^`. Ova operacija $x\ \text{xor} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način. Prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in {1, \ldots, k }$ računa $c_i$ pomoću sledećih pravila:
	
	-   Za $a_{i} = 0, b_{i} = 0$ važi $c_{i} = 0$
	-   Za $a_{i} = 0, b_{i} = 1$ važi $c_{i} = 1$
	-   Za $a_{i} = 1, b_{i} = 0$ važi $c_{i} = 1$
	-   Za $a_{i} = 1, b_{i} = 1$ važi $c_{i} = 0$
	
	Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{xor} \ y$.
	
	Ako želite da saznate šta se desi u nastavku, pogledajte drugi zadatak za $A$ kategoriju: *Ćivas*
	
=== "Rešenje"
	
	| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
	|:-:|:-:|:-:|:-:|
	| Pavle Martinović | Pavle Martinović | Mladen Puzić | Momčilo Tošić |
	
	## Rešenje kada $N, M \leq 5, A_i \leq 1$
	Pošto su dimenzije matrice male, a jedine moguće vrednosti u matrici $0$ i $1$, postoji dosta malo stanja u kojima se može naći matrica. Simuliramo proces sekundu po sekundu, dok se ne desi da smo već videli dato stanje. Pošto znamo da ćemo na dalje da se vrtimo u krug, znamo da će rešenje biti jedno od datih stanja. Koje tačno stanje će to biti možemo dobiti koristećenjem formula.
	
	## Rešenje kada $K \leq 5$
	Pošto je $K \leq 5$, znači da nam je bitno samo ponašanje matrice u prvih $2^5 = 32$ sekundi. Pre svih pitanja, izračunaćemo sve matrice, i onda za svako pitanje možemo samo ispisati traženo polje odgovarajuće matrice.
	
	Vremenska složenost je $O(2^KNM + Q)$, a memorijska $O(2^KNM)$. 
	
	## Rešenje kada $K \leq 200$ 
	Ponovo ćemo čuvati matrice za svako $K$, ali ovaj put ćemo ih računati na način koji će biti opisan u sledeća dva rešenja. 
	
	## Rešenje kada su sve početne vrednosti $0$, sem jedne koja je $1$
	Posmatranjem kako se ova jedinica ponaša kroz vreme u beskonačnoj matrici možemo zaključiti da će nakon $2^K$ sekundi da se nalazi na pozicijama $(x+2^K, y)$, $(x-2^K, y)$, $(x, y+2^K)$ i $(x, y-2^K)$. Ovo možemo i jednostavno dokazati indukcijom. Za bazu $K = 0$ ovo je očigledno tačno. Ako pretpostavimo da je tačno za neko $K$, i primenimo induktivnu hipotezu na $4$ tako dobijene tačke, videćemo da se dešava nešto zanimljivo - sva polja sem ona $4$ koja su nam potrebna se skrate (xor je inverz sam sebi), pa smo dokazali tvrđenje. 
	
	Sada, za svako pitanje je dovoljno proveriti da li je u pitanju jedno od najviše četiri polja koji sadrže jedinicu. Pošto ova matrica nije beskonačna, moramo koristeći formule da dobijemo tačne koordinate jedinica u njoj. 
	
	Vremenska složenost je $O(NM+M+K)$, a memorijska $O(NM+K)$. 
	
	## Glavno rešenje
	Primetimo da će sva polja u matrici biti xor nekih polja početne matrice. Koristeći prethodno rešenje, za svako polje početne matrice možemo pronaći u xor-u kojih polja matrice će se nalaziti nakon $2^K$ sekundi. Tako možemo zaključiti da će vrednost polja $(x, y)$ nakon $2^K$ sekundi biti xor vrednosti polja $(x+2^K, y)$, $(x-2^K, y)$, $(x, y+2^K)$ i $(x, y-2^K)$ u početnoj matrici. 
	
	Vremenska složenost je $O(NM+M+K)$, a memorijska $O(NM+K)$. matrici. 
	
	
	``` cpp title="03_okram.cpp" linenums="1"
	#include <bits/stdc++.h>
	using namespace std;
	int a[1500][1500],stn[1000007],stm[1000007];
	int main()
	{
	    int n,m,q;
	    scanf("%d%d%d",&n,&m,&q);
	    for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",&a[i][j]);
	    stn[0]=stm[0]=1;
	    for(int i=1;i<1000007;i++) stn[i]=(stn[i-1]*2)%n;
	    for(int i=1;i<1000007;i++) stm[i]=(stm[i-1]*2)%m;
	    while(q--)
	    {
	        int x,y,k;
	        scanf("%d%d%d",&x,&y,&k); x--; y--;
	        printf("%d\n",a[(x+stn[k])%n][y]^a[(x+n-stn[k])%n][y]^a[x][(y+stm[k])%m]^a[x][(y+m-stm[k])%m]);
	    }
	}

	```
