---
hide:
  - toc
---

# 3 - Zlatnici

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |


Kralj Mida je poznat po svom daru da sve što dotakne postane zlatno. Međutim, prekasno je shvatio da neopreznim korišćenjem svog dara može sebi ozbiljno da naškodi. Naime, on je celu svoju kolekciju novčića od bakra, srebra i gvožđa, pretvorio u beskorisne zlatnike! Izgubivši to što mu je nekada bilo najdraže, odlučio je da sve svoje vreme provodi na najbezbedniji mogući način, igrajući sledeću igru.

Pred sobom ima tablu sa $N$ kolona i $N$ vrsta, i na toj tabli stoje $N$ od njegovih mnogobrojnih zlatnika. Svaki zlatnik zauzima tačno jedno polje table, i nije moguće da dva zlatnika budu na istom polju. Mida u jednoj sekudni može da uzme jedan zlatnik i premesti ga na neko polje koje deli stranicu sa poljem na kome se taj zlatnik trenutno nalazi, pri čemu ne sme da premesti zlatnik na polje koje je već zauzeto. Midi je cilj da se u svakoj koloni i u svakoj vrsti nađe tačno jedan zlatnik.

Mida je već poprilično vešt u ovoj igri, ali ga interesuje da li uspeva da postigne svoj cilj u najmanjem mogućem vremenu. Međutim, kako ne želi da pozlati svoju tastaturu, on je vas zamolio da vi to izračunate. Od vas traži da, za dati početan raspored zlatnika, odredite najmanje moguće vreme za koje on može da pobedi.
## Opis ulaza
Prva linija standardnog ulaza sadrži jedan broj, $N$: broj vrsta, kolona i zlatnika.
Narednih $N$ linija sadrže po dva prirodna broja $r_i$ i $c_i$, koji označavaju da se na početku $i$-ti zlatnik nalazi u preseku vrste $r_i$ i kolone $c_i$.

## Opis izlaza
U prvu i jedinu liniju standardnog izlaza ispisati jedan broj: najmanji broj sekundi potreban Midi da pobedi za zadati raspored zlatnika.
## Primer 1

### Ulaz

```
3
2 1
2 2
2 3
```

### Izlaz

```
2
```

## Primer 2

### Ulaz

```
3
1 2
3 1
2 3
```

### Izlaz

```
0
```

## Objašnjenje primera
Za prvi primer, očito Midi treba bar dve sekunde da ne bi bilo dva zlatnika u drugoj vrsti, a može da pobedi u dva poteza tako što zlatnik na polju $(2,2)$ premesti na polje $(1,2)$, a zlatnik na polju $(2,1)$ premesti na polje $(3,1)$.

U drugom primeru Mida ne mora ništa da uradi da bi pobedio.


## Ograničenja
-   $1 \leq n \leq 2\cdot 10^5$
-   $1\leq r_i,c_i\leq N$

Test primeri su podeljeni u 4 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $n \leq 2$.
-   U test primerima vrednim $20$ poena: $n \leq 7$.
-   U test primerima vrednim $30$ poena: $n \leq 1000$.
-   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Milisavljević |



## Analiza

Posmatrajmo nizove $r_i$ i $c_i$, koji označavaju u kojoj se koloni i vrsti nalaze zlatnici. Vidimo da u jednom potezu uzimamo jedan zlatnik i menjamo mu redni broj vrste ili redni broj kolone za $\pm1$.  Ovo znači da mi u jednom potezu menjamo vrednost jednog člana niza $r_i$ za $\pm 1$, ili jedan član niza $c_i$ za $\pm 1$. Nama je cilj da na kraju oba niza $r_i$ i $c_i$ postanu permutacija skupa $\{1,2,3,\cdots,n\}$. Označimo sa $R$ minimalni broj poteza da se ovo učini sa nizom $r_i$ a sa $C$ minimalan broj poteza da se ovo uradi sa nizom $c_i$. Tada je traženo rešenje očito barem $R+C$.


Rešimo ovo za niz $r_i$.  Ako na kraju dobijemo niz $x_i$ onda nam je trebalo $S=|r_1-x_1|+|r_2-x_2|+\cdots+|r_n-x_n|$ poteza. Primetimo da ako $r_i<r_j$ i $x_i>x_j$, tada zamenom vrednosti $x_i$ i $x_j$ ne povećavamo (a potencijalno smanjujemo) rezultat. Ovo se dokazuje analizom slučaja za sve poretke ovih $4$ vrednosti. Ovime vidimo da je jedno od slučajeva kada se najbolje rešenje dostiže je kada su brojevi $x_i$ u istom poretku kao i brojevi $r_i$. Ovo znači da kada je niz $r_i$ sortiran, onda je $R=|r_1-1|+|r_2-2|+\cdots+|r_n-n|$.  Po istom principu važi ako je niz $c_i$ sortiran tada $C=|c_1-1|+|c_2-2|+\cdots+|c_n-n|$.


Prvo ćemo analizirati šta se dešava u slučaju da mogu postojati dva (ili više) novčića na istom polju u istom trenutku. Tada su koordinate zlatnike očigledno nezavisne, pa je odgovor upravo $R+C$.

Međutim, ispostavlja se da je ovo odgovor i u pravom zadatku. Ovo je tako jer je moguće izvršiti niz poteza tako da se dostigne jednakost i za $R$ i za $C$ a da pri tome nikad ne budu dva zlatnika na istom polju. Prvo ćemo rasporediti zlatnike u različitim redovima u optimalnom broju poteza, a posle toga je očito jasno da nema problema rasporediti ih po različitim kolonama jer to što su u različitim redovima garantuje da su na različitim poljima. Za taj prvi deo je očito dovoljno da za svaku kolonu dovedemo zlatnike na prava mesta bez preklopa, jer zlatnici koji kreću u različitim kolonama će ostati na različitim poljima dok samo menjamo u kojim se redovima menjaju. U svakoj koloni će postojati neki zlatnici koji idu "na gore" i oni koji idu "na dole". U svakom trenutku ćemo uzeti onaj najviši koji treba da ide na gore a nije u pravom redu i pomeriti ga na gore ili najniži koji treva da ide na dole a nije u pravom redu i pomeriti ga na dole. Jasno je da ovako neće biti nikad dva na istom polju jer ako neki zlatnik što ide na gore se poklopi sa nekim što ide na gore, to je u kontradikciji sa time da smo izabrali najviši takav zlatnik, a ako se poklopi sa nekim što ide na dole, to je u kontradikciji sa time da su početne vrednosti $r_i$ u istom poretku kao i konačne vrednosti $r_i$.

Ovaj algoritam se sada lako implementira u $O(n \log (n))$ sa običnim sortom ili $O(n)$ sa *counting* sortom.

``` cpp title="03_zlatnici.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 200007
using namespace std;
long long x[MAXN],y[MAXN];
int main()
{
	int n;
	long long res=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&x[i],&y[i]);
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for(int i=1;i<=n;i++) res+=abs(x[i]-i);
	for(int i=1;i<=n;i++) res+=abs(y[i]-i);
	printf("%lld",res);
}

```
