

# 2 - Manja je matrica od matrice


	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |
	
```
	Manja je matrica od matrice,
	Najmanja "Mala Matrica" matrica;
	U njoj je reda dva, a kolone tri
	U njoj su nule i stotke
	Na svakom krugu kvalifikacija;
	...
```
Vama su data $4$ pozitivna cela broja $N,M,K,L$, kao i niz $A$ od  $N\cdot M$ nenegativnih celih brojeva. Računamo lepotu $N\times M$ matrice tako što za svaku njegovu podmatricu dimenzije $K\times L$ zapišemo na papiru sumu elemenata te podmatrice, a zatim saberemo sve brojeve koje smo zapisali na našem papiru. Vaš zadatak je da odredite najveću moguću lepotu $N\times M$ matrice ako u nju upišemo elemente niza $A$.
	
## Opis ulaza
U prvoj liniji standardnog ulaza se nalaze četiri broja $N,M,K,L$, koji opisuju dimenzije matrice i dimezije posmatranih podmatrica. U drugoj liniji standardnog ulaza se nalazi $N\cdot M$ brojeva koji predstavljaju elemente $A$.
	
## Opis izlaza
Potrbeno je ispisati jedan broj - najveću moguću lepotu matrice. 
	 
## Ograničenja
 - $1\leq N,M \leq 1.000$
 - $1\leq K \leq N$
 - $1\leq L \leq M$
 - $0\leq A_i \leq 10^6$
	 
Test primeri su podeljeni u $5$ disjunktnih grupa
	
 - U test primerima vrednim 20 poena: $K=L=1$.
 - U test primerima vrednim 20 poena: $N=M=3$, $K=L=2$.
 - U test primerima vrednim 20 poena: $0\leq A_i\leq 1$
 - U test primerima vrednim 20 poena: $K,L\leq 5$.
 - U test primerima vrednim 20 poena: Nema dodatnih ograničenja.
	
## Primer 1
	
### Ulaz
	
```
	2 3 2 2
	1 5 6 0 5 2
```
	
### Izlaz
	
```
	30
```
### Objašnjenje
Optimalno je rasporediti brojeve na sledeći način
```
	0 6 2
	1 5 5
```
Ova $3\times2$ matrica ima dve $2\times2$ podmatrice, levu i desnu. U levoj je suma $12$, a u desnoj $18$ pa je ukupna suma $30$.
	
## Primer 2
	
### Ulaz
	
```
	3 3 2 2
	1 0 0 0 0 0 0 0 0 
```
	
### Izlaz
	
```
	4
```
### Objašnjenje
Ova matrica ima četiri $2\times2$ podmatrice, i ako se jedinica postavi u cetnralno polje, suma u svakoj od tih podmatrica će biti $1$, pa je tada ukupna suma $4$.
	
## Napomena
Primetite da rešenje na zadatak može biti značajno veće od $2\cdot 10^9$, tako da ne treba raditi sa 32-bitnim tipovima podataka kao `int` već 64-bitnim kao `long long`. 
	
Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Mladen Puzić | Aleksandar Višnjić |
	
U analizi rešenje smatraće se da prvi red od gore ima indeks $1$, poslednji red indeks $N$, prva kolona sleva ima indeks $1$, a poslednja $M$.
	
## Rešenje kada $K = L = 1$
Lepota matrice je suma svih podmatrica dimenzija $1 \times 1$, što je u stvari zbir svih elemenata matrice. Dakle, kako god rasporedili elemente, lepota matrice biće ista i to zbir svih elemenata niza $A$.
	
Vremenska i memorijska složenost je $O(NM)$.
	
## Rešenje kada $N = M = 3, K = L = 2$
Pošto matrica ima samo $9$ polja, postoji $9! = 362.880$ mogućnosti za raspoređivanje niza $A$ u matricu. Nazovimo matricu $m$ - lepota matrice nakon fiksiranog niza jeste (može se videti ako se ispišu zajedno sume svih podmatrica dimenzije $2\times 2$):
	
$$
	m_{1, 1} + 2\cdot m_{1, 2} + m_{1, 3} + 2\cdot m_{2, 1} + 4\cdot m_{2, 2} + 2\cdot m_{2, 3} + m_{3, 1} + 2\cdot m_{3, 2} + m_{3, 3}
$$
	
Od svih mogućih opcija, biramo onu koja maksimizira gorenavedenu formulu.
	
Vremenska složenost je $O((NM)!)$, a memorijska $O(NM)$.
	
## Rešenje kada $K, L \leq 5$
Pošto su dimenzije posmatranih podmatrica male, mi možemo grubom silom izračunati za svako polje u koliko podmatrica dimenzije $K \times L$ se nalazi, sledećim algoritmom:
	
* Inicijalizujemo matricu $cnt_{i, j} = 0$, za svako $1 \leq i \leq N$ i $1 \leq j \leq M$;
* Za svako moguće gornje levo polje $(x, y)$ (ovo su sva polja za koja važi $1 \leq x \leq N-K+1$ i $1 \leq y \leq M-L+1$):
* Za svako polje $(i, j)$ za koje važi $x \leq i < x+K$ i $y \leq j < y+L$ uvećati $cnt_{i, j}$ za jedan.
	
Nakon toga, sve vrednosti iz matrice $cnt$ prebacimo u niz koji sortiramo. Najveću vrednost niza $A$ potrebno je staviti na polje koje se pojavljuje u najviše posmatranih podmatrica, drugu najveću vrednost u polje koje se pojavljuje u drugom najvećem broju podmatrica, itd.
	
Vremenska složenost je $O(NMKL + NM\log(NM))$, a memorijska $O(NM)$.
	
## Rešenje kada $0 \leq A_i \leq 1$
Pošto imamo samo dve moguće vrednosti, želimo jedinice staviti u polja koja se nalaze u najvećem broju podmatrica dimenzije $K\times L$, dok nule stavljamo u polja koja se ređe pojavljuju. Dakle, želimo da za svako polje efikasno pronađemo u koliko posmatranih podmatrica se nalazi (ovo ne zavisi od raspodele elemenata u matrici).
	
Kada bismo imali beskonačnu tablu, polje $(i, j)$ bi sadržao svaki pravougaonik dimenzije $K\times L$ čiji je gornje levo polje $(x, y)$, gde važi $i-K+1 \leq x \leq i$ i $j-L+1 \leq y \leq j$. Ukoliko uračunamo da ivice matrice mogu da smanje naš broj opcija, dobijamo da mora da važi: 
	
$$
	\max(i-K+1, 1) \leq x \leq \min(N-K+1, i)
$$
	
$$
	\max(j-L+1, 1) \leq y \leq \min(M-L+1, j)
$$
	
Iz ovoga se može zaključiti da se broj podmatrica koje sadrže polje $(i, j)$, dakle, $cnt_{i, j}$, može izračunati formulom:
	
$$
	cnt_{i, j} = (\min(N-K+1, i) - \max(i-K+1, 1) + 1) \cdot (\min(M-L+1, j) - \max(j-L+1, 1) + 1)
$$
	
Dalje, izbrojimo broj jedinica u nizu $A$ i rešenje je zbir toliko najvećih elemenata iz matrice $cnt$.
	
Vremenska složenost je $O(NM\log(NM))$, a memorijska $O(NM)$.
	
## Glavno rešenje
Poput rešenja kada $0 \leq A_i \leq 1$ za svako polje pronalazimo u koliko posmatranih podmatrica se nalazi, a poput rešenja kada $K, L \leq 5$ uparujemo najveći element niza $A$ sa onom pozicijom koja se pojavljuje u najviše posmatranih podmatrica.
	
Vremenska složenost je $O(NM\log(NM))$, a memorijska $O(NM)$.
	
``` cpp title="02_manja_je_matrica_od_matrice.cpp" linenums="1"
	#include <bits/stdc++.h>
	#define MAXN 1007
	using namespace std;
	long long a[MAXN*MAXN],b[MAXN*MAXN];
	int main()
	{
	    int n,m,k,l;
	    cin>>n>>m>>k>>l;
	    for(int i=0;i<m*n;i++) cin>>a[i];
	    sort(a,a+m*n);
	    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	    {
	        long long kx=min(n,i+k-1)-max(k,i)+1,ky=min(m,j+l-1)-max(l,j)+1;
	        b[(i-1)*m+j-1]=kx*ky;
	    }
	    sort(b,b+m*n);
	    long long ans=0;
	    for(int i=0;i<n*m;i++) ans+=a[i]*b[i];
	    cout<<ans;
	}

```
